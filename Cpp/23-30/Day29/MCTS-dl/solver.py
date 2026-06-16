"""
Path finding algorithms and decision strategies for Block Sequence Grand Master.
"""

from __future__ import annotations
import math
import random
import time
from typing import List, Tuple, Callable, Optional
from engine import Board, validate_path, score_path, DR, DC

# ============================================================
# Connected Component Analysis (foundation for all strategies)
# ============================================================


def find_color_components(
    board: Board, target_color: int
) -> List[List[Tuple[int, int]]]:
    """
    Find connected components of cells that can be connected (same |color| or wildcard).
    target_color = 0 means wildcard-only component.
    """
    N = board.N
    visited = [[False] * N for _ in range(N)]
    components = []

    for r in range(N):
        for c in range(N):
            v = board.grid[r][c]
            av = abs(v)
            if target_color == 0:
                match = v == 0
            else:
                match = av == target_color or v == 0

            if match and not visited[r][c]:
                # BFS to find component
                comp = []
                stack = [(r, c)]
                visited[r][c] = True
                while stack:
                    cr, cc = stack.pop()
                    comp.append((cr, cc))
                    for d in range(4):
                        nr, nc = cr + DR[d], cc + DC[d]
                        if 0 <= nr < N and 0 <= nc < N and not visited[nr][nc]:
                            nv = board.grid[nr][nc]
                            nav = abs(nv)
                            if target_color == 0:
                                nmatch = nv == 0
                            else:
                                nmatch = nav == target_color or nv == 0
                            if nmatch:
                                visited[nr][nc] = True
                                stack.append((nr, nc))
                components.append(comp)
    return components


# ============================================================
# DFS Longest Path (exhaustive within component)
# ============================================================


def _dfs_longest(
    grid: List[List[int]],
    N: int,
    pos: Tuple[int, int],
    visited: int,  # bitmask for N*N grid (max 144 cells)
    path: List[Tuple[int, int]],
    best_path: List[List[Tuple[int, int]]],
    target_color: int,
    depth_limit: int,
):
    """Internal DFS for longest path search."""
    if len(path) >= depth_limit:
        return

    r, c = pos
    for d in range(4):
        nr, nc = r + DR[d], c + DC[d]
        if 0 <= nr < N and 0 <= nc < N:
            bit = nr * N + nc
            if visited & (1 << bit):
                continue
            nv = grid[nr][nc]
            nav = abs(nv)
            if target_color == 0:
                match = nv == 0
            else:
                match = nav == target_color or nv == 0
            if match:
                visited |= 1 << bit
                path.append((nr, nc))

                if len(path) > len(best_path[0]):
                    best_path[0] = path[:]

                _dfs_longest(
                    grid,
                    N,
                    (nr, nc),
                    visited,
                    path,
                    best_path,
                    target_color,
                    depth_limit,
                )
                path.pop()
                visited &= ~(1 << bit)


def find_longest_path_dfs(
    board: Board, depth_limit: int = 100, time_limit_ms: float = 500
) -> Optional[List[Tuple[int, int]]]:
    """
    Find the longest valid path using DFS, with depth/time limits.
    Returns the longest path found, or None if none exists.
    """
    N = board.N
    best_path = [[]]
    colors = set()
    has_wildcard = False
    for r in range(N):
        for c in range(N):
            v = board.grid[r][c]
            av = abs(v)
            if v == 0:
                has_wildcard = True
            if av >= 1:
                colors.add(av)

    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # For each color + wildcard, search for longest path
    for color in sorted(colors):
        if time.time() > deadline:
            break
        for r in range(N):
            for c in range(N):
                if time.time() > deadline:
                    break
                v = board.grid[r][c]
                av = abs(v)
                if av == color or v == 0:
                    visited = 1 << (r * N + c)
                    path = [(r, c)]
                    _dfs_longest(
                        board.grid,
                        N,
                        (r, c),
                        visited,
                        path,
                        best_path,
                        color,
                        depth_limit,
                    )

    if len(best_path[0]) < 2:
        return None
    return best_path[0]


# ============================================================
# Iterative Deepening DFS (IDDFS) - better for time-constrained search
# ============================================================


def find_paths_iddfs(
    board: Board, time_limit_ms: float = 500, max_paths: int = 20
) -> List[List[Tuple[int, int]]]:
    """
    Iterative deepening DFS to find multiple candidate paths.
    Starts with short paths and progressively searches deeper.
    Returns top paths by score.
    """
    N = board.N
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    all_paths = []  # list of (path, score)

    # First, find all viable start cells
    colors = set()
    for r in range(N):
        for c in range(N):
            av = abs(board.grid[r][c])
            if av >= 1:
                colors.add(av)

    for color in sorted(colors):
        if time.time() > deadline:
            break
        # Find connected component for this color
        comps = find_color_components(board, color)
        for comp in comps:
            if time.time() > deadline:
                break
            if len(comp) < 2:
                continue
            # DFS from each cell in the component
            for start_cell in comp:
                if time.time() > deadline:
                    break
                visited = 1 << (start_cell[0] * N + start_cell[1])
                path = [start_cell]
                _collect_paths_dfs(
                    board.grid,
                    N,
                    start_cell,
                    visited,
                    path,
                    color,
                    all_paths,
                    deadline,
                    max_paths * 3,
                )

    # Sort by score descending, keep unique
    all_paths.sort(key=lambda x: -x[1])
    seen = set()
    unique = []
    for p, s in all_paths:
        key = tuple(p)
        if key not in seen:
            seen.add(key)
            unique.append(p)
        if len(unique) >= max_paths:
            break

    if not unique:
        # Fallback: return adjacent pair
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [[(r1, c1), (r2, c2)]]
        return [[(0, 0), (0, 1)]]

    return unique


def _collect_paths_dfs(
    grid, N, pos, visited, path, target_color, collected, deadline, max_collect
):
    """DFS that collects paths into collected list with pruning."""
    if time.time() > deadline or len(collected) >= max_collect:
        return

    if len(path) >= 2:
        s = score_path(grid, path)
        # Keep if it's better than the worst in our collection
        if len(collected) < max_collect or s > collected[-1][1]:
            collected.append((path[:], s))
            collected.sort(key=lambda x: -x[1])
            if len(collected) > max_collect:
                collected.pop()

    if len(path) >= 30:  # Don't go too deep in collection mode
        return

    r, c = pos
    # Order neighbors by heuristic: prefer cells that have more free neighbors
    neighbors = []
    for d in range(4):
        nr, nc = r + DR[d], c + DC[d]
        if 0 <= nr < N and 0 <= nc < N:
            bit = nr * N + nc
            if visited & (1 << bit):
                continue
            nv = grid[nr][nc]
            nav = abs(nv)
            if target_color == 0:
                match = nv == 0
            else:
                match = nav == target_color or nv == 0
            if match:
                # Count free neighbors for heuristic ordering
                free = 0
                for d2 in range(4):
                    nnr, nnc = nr + DR[d2], nc + DC[d2]
                    if 0 <= nnr < N and 0 <= nnc < N:
                        nnbit = nnr * N + nnc
                        if not (visited & (1 << nnbit)):
                            nnv = grid[nnr][nnc]
                            nnav = abs(nnv)
                            if target_color == 0:
                                nm = nnv == 0
                            else:
                                nm = nnav == target_color or nnv == 0
                            if nm:
                                free += 1
                neighbors.append((free, nr, nc))

    neighbors.sort(reverse=True)  # Visit cells with more options first

    for free, nr, nc in neighbors:
        visited |= 1 << (nr * N + nc)
        path.append((nr, nc))
        _collect_paths_dfs(
            grid,
            N,
            (nr, nc),
            visited,
            path,
            target_color,
            collected,
            deadline,
            max_collect,
        )
        path.pop()
        visited &= ~(1 << (nr * N + nc))


# ============================================================
# Lookahead evaluation
# ============================================================


def evaluate_state_heuristic(board: Board) -> float:
    """
    Heuristic evaluation of a board state.
    Higher = better future potential.
    Considers: connectivity, bomb density, component sizes.
    """
    N = board.N
    score = 0.0

    # Count blocks by color
    color_counts = {i: 0 for i in range(1, 6)}
    bomb_counts = {i: 0 for i in range(1, 6)}
    wildcard_count = 0

    for r in range(N):
        for c in range(N):
            v = board.grid[r][c]
            if v == 0:
                wildcard_count += 1
            elif v > 0:
                color_counts[v] += 1
            else:
                bomb_counts[abs(v)] += 1

    # Score: potential for long paths = well-distributed colors
    for color in range(1, 6):
        total = color_counts[color] + bomb_counts[color]
        if total >= 2:
            # Component analysis would be better but is expensive
            # Use simple adjacency count as proxy
            adj_count = 0
            for r in range(N):
                for c in range(N):
                    av = abs(board.grid[r][c])
                    if av == color or board.grid[r][c] == 0:
                        # Check neighbors
                        for d in range(4):
                            nr, nc = r + DR[d], c + DC[d]
                            if 0 <= nr < N and 0 <= nc < N:
                                nav = abs(board.grid[nr][nc])
                                if nav == color or board.grid[nr][nc] == 0:
                                    adj_count += 0.5  # 0.5 to avoid double counting

            # Long path potential grows quadratically
            score += adj_count * adj_count * 2

            # Bomb bonus potential
            if bomb_counts[color] > 0:
                score += bomb_counts[color] * 20  # Estimated bomb value

    # Wildcards are very valuable
    score += wildcard_count * 15

    # Penalty for nearly deadlocked states
    pairs = board.find_adjacent_pairs()
    if len(pairs) < 3:
        score -= 100

    return score


def lookahead_score(
    board: Board, path: List[Tuple[int, int]], depth: int = 2, beam_width: int = 3
) -> float:
    """
    Evaluate a path by looking ahead `depth` steps.
    Returns expected future score contribution.
    """
    current_score = score_path(board.grid, path)
    if depth <= 1:
        return current_score

    # Simulate the path
    future = board.preview(path)
    if future.is_deadlocked():
        return current_score - 50  # Penalty for causing deadlock

    # Find candidate paths from future state
    candidates = find_paths_iddfs(future, time_limit_ms=200, max_paths=beam_width)

    if not candidates:
        return current_score

    # Recursively evaluate best candidate(s)
    best_future = 0.0
    for candidate in candidates[:beam_width]:
        future_score = lookahead_score(future, candidate, depth - 1, beam_width)
        if future_score > best_future:
            best_future = future_score

    return current_score + 0.7 * best_future  # Discount factor


# ============================================================
# STRATEGY 1: Baseline Greedy (original strategy)
# ============================================================


def strategy_greedy_baseline(board: Board) -> List[Tuple[int, int]]:
    """Original strategy: find first adjacent same-color pair."""
    pairs = board.find_adjacent_pairs()
    if pairs:
        r1, c1, r2, c2 = pairs[0]
        return [(r1, c1), (r2, c2)]
    return [(0, 0), (0, 1)]


# ============================================================
# STRATEGY 2: Greedy Longest Path
# ============================================================


def strategy_greedy_longest(
    board: Board, time_limit_ms: float = 500
) -> List[Tuple[int, int]]:
    """Pick the longest single path found by DFS."""
    path = find_longest_path_dfs(board, depth_limit=100, time_limit_ms=time_limit_ms)
    if path is None or len(path) < 2:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]
    return path


def _dfs_best_scoring(
    grid: List[List[int]],
    N: int,
    pos: Tuple[int, int],
    visited: int,
    path: List[Tuple[int, int]],
    best_result: List,  # [best_path, best_score]
    target_color: int,
    deadline: float,
):
    """DFS that tracks the highest-SCORING path (not just longest)."""
    if time.time() > deadline:
        return

    r, c = pos
    neighbors = []
    for d in range(4):
        nr, nc = r + DR[d], c + DC[d]
        if 0 <= nr < N and 0 <= nc < N:
            bit = nr * N + nc
            if visited & (1 << bit):
                continue
            nv = grid[nr][nc]
            nav = abs(nv)
            if target_color == 0:
                match = nv == 0
            else:
                match = nav == target_color or nv == 0
            if match:
                neighbors.append((nr, nc))

    if not neighbors:
        # Leaf node - evaluate this path
        if len(path) >= 2:
            s = score_path(grid, path)
            if s > best_result[1]:
                best_result[0] = path[:]
                best_result[1] = s
        return

    for nr, nc in neighbors:
        visited |= 1 << (nr * N + nc)
        path.append((nr, nc))
        _dfs_best_scoring(
            grid, N, (nr, nc), visited, path, best_result, target_color, deadline
        )
        path.pop()
        visited &= ~(1 << (nr * N + nc))


def strategy_greedy_best_score(
    board: Board, time_limit_ms: float = 800
) -> List[Tuple[int, int]]:
    """
    Advanced greedy: find the path with the highest TOTAL score
    (base + bomb bonus), not just the longest.
    This is crucial for levels 4-5 where bomb placement matters.
    """
    N = board.N
    best_path = None
    best_score_val = -1

    colors = set()
    has_bomb = False
    for r in range(N):
        for c in range(N):
            v = board.grid[r][c]
            av = abs(v)
            if av >= 1:
                colors.add(av)
            if v < 0:
                has_bomb = True

    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # For bomb levels, also search for best-scoring paths
    for color in sorted(colors):
        if time.time() > deadline:
            break
        for r in range(N):
            for c in range(N):
                if time.time() > deadline:
                    break
                v = board.grid[r][c]
                av = abs(v)
                if av == color or v == 0:
                    visited = 1 << (r * N + c)
                    path = [(r, c)]
                    best_result = [[(r, c)], 0]
                    _dfs_best_scoring(
                        board.grid,
                        N,
                        (r, c),
                        visited,
                        path,
                        best_result,
                        color,
                        deadline,
                    )
                    if best_result[1] > best_score_val:
                        best_score_val = best_result[1]
                        best_path = best_result[0]

    if best_path is None or len(best_path) < 2:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]
    return best_path


def strategy_deterministic_lookahead(
    board: Board,
    pool_size: int = 10,
    time_limit_ms: float = 1500,
) -> List[Tuple[int, int]]:
    """
    DETERMINISTIC 2-step lookahead using exhaustive DFS + preview().

    Unlike Poisson rollouts (random, high variance), this uses:
    1. Exhaustive DFS to find top-K candidate paths on current board
    2. For each candidate, preview() the exact future board
    3. On the future board, compute the best possible single-step score
       (using fast heuristic: score of best adjacent pair + bomb bonus)
    4. Score = current_score + beta * future_best_estimate

    This is deterministic and much more reliable than random rollouts.
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # Phase 1: Exhaustive candidate generation
    candidates = collect_exhaustive_candidates(
        board,
        topk_per_component=3,
        global_max=pool_size,
        time_limit_ms=time_limit_ms * 0.5,
    )

    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    # Phase 2: Deterministic future evaluation
    best_path = candidates[0][0]
    best_total = -1e9

    for idx, (path, imm_score, heuristic) in enumerate(candidates):
        if time.time() > deadline:
            break

        future = board.preview(path)
        if future.is_deadlocked():
            total = imm_score - 150
            if total > best_total:
                best_total = total
                best_path = path
            continue

        # Fast estimate of best next-step score on the future board
        # Find best adjacent pair + estimate bomb bonus
        future_best = _estimate_best_next_score(future)

        # Weighted combination
        total = imm_score + 0.7 * future_best + 0.1 * (heuristic / 100.0)

        if total > best_total:
            best_total = total
            best_path = path

    # Phase 3: For top-2 candidates, compute exact 2nd step via exhaustive DFS
    # Sort by current estimate
    scored = []
    for path, imm_score, heuristic in candidates:
        future = board.preview(path)
        if future.is_deadlocked():
            scored.append((path, imm_score - 200))
            continue
        future_best = _estimate_best_next_score(future)
        scored.append((path, imm_score + 0.7 * future_best))

    scored.sort(key=lambda x: -x[1])

    for idx in range(min(2, len(scored))):
        if time.time() > deadline:
            break
        path, _ = scored[idx]
        future = board.preview(path)
        if future.is_deadlocked():
            continue

        imm_score = score_path(board.grid, path)

        # Actual exhaustive DFS on the future board (expensive but precise)
        next_path = strategy_greedy_best_score(future, time_limit_ms=300)
        if next_path and len(next_path) >= 2:
            next_score = score_path(future.grid, next_path)
            total = imm_score + 0.7 * next_score
            if total > best_total:
                best_total = total
                best_path = path

    return best_path


def _estimate_best_next_score(board: Board) -> float:
    """
    Fast estimate of the best possible single-step score on this board.
    Uses component size heuristics + bomb potential.
    """
    N = board.N
    best_estimate = 0.0

    # Find connected components per color
    for color in range(1, 6):
        comps = find_color_components(board, color)
        for comp in comps:
            if len(comp) < 2:
                continue
            # Best possible score from this component
            k = len(comp)
            est = (
                SCORE_TABLE[k]
                if k < len(SCORE_TABLE)
                else 10 * k + 18 * int((math.sqrt(k) - 1.0) ** 2)
            )
            # Add bomb bonus estimate
            if board.level >= 4:
                bomb_count = sum(1 for r, c in comp if board.grid[r][c] < 0)
                est += bomb_count * 60  # Rough bomb bonus
            if est > best_estimate:
                best_estimate = est

    return best_estimate


# ============================================================
# ============================================================


def _dfs_collect_topk(
    grid: List[List[int]],
    N: int,
    pos: Tuple[int, int],
    visited: int,
    path: List[Tuple[int, int]],
    topk: List[Tuple[List[Tuple[int, int]], int]],  # [(path, score)], sorted desc
    target_color: int,
    max_k: int,
    deadline: float,
):
    """DFS that collects top-K best-scoring paths."""
    if time.time() > deadline:
        return

    r, c = pos
    neighbors = []
    for d in range(4):
        nr, nc = r + DR[d], c + DC[d]
        if 0 <= nr < N and 0 <= nc < N:
            bit = nr * N + nc
            if visited & (1 << bit):
                continue
            nv = grid[nr][nc]
            nav = abs(nv)
            if target_color == 0:
                match = nv == 0
            else:
                match = nav == target_color or nv == 0
            if match:
                neighbors.append((nr, nc))

    if not neighbors:
        if len(path) >= 2:
            s = score_path(grid, path)
            _insert_topk(topk, path[:], s, max_k)
        return

    # Order neighbors by degree for better pruning
    ordered = []
    for nr, nc in neighbors:
        free = sum(
            1
            for d2 in range(4)
            if 0 <= nr + DR[d2] < N
            and 0 <= nc + DC[d2] < N
            and not (visited & (1 << ((nr + DR[d2]) * N + (nc + DC[d2]))))
            and (
                abs(grid[nr + DR[d2]][nc + DC[d2]]) == target_color
                or grid[nr + DR[d2]][nc + DC[d2]] == 0
            )
        )
        ordered.append((free, nr, nc))
    ordered.sort(reverse=True)

    for _, nr, nc in ordered:
        visited |= 1 << (nr * N + nc)
        path.append((nr, nc))
        _dfs_collect_topk(
            grid, N, (nr, nc), visited, path, topk, target_color, max_k, deadline
        )
        path.pop()
        visited &= ~(1 << (nr * N + nc))


def _insert_topk(
    topk: List[Tuple[List[Tuple[int, int]], int]],
    path: List[Tuple[int, int]],
    score: int,
    max_k: int,
):
    """Insert path into sorted top-k list if score qualifies."""
    # Check if already present
    path_key = tuple(path)
    for i, (p, s) in enumerate(topk):
        if tuple(p) == path_key:
            if score > s:
                topk[i] = (path, score)
                topk.sort(key=lambda x: -x[1])
            return

    if len(topk) < max_k or score > topk[-1][1]:
        topk.append((path, score))
        topk.sort(key=lambda x: -x[1])
        if len(topk) > max_k:
            topk.pop()


def collect_exhaustive_candidates(
    board: Board,
    topk_per_component: int = 3,
    global_max: int = 15,
    time_limit_ms: float = 1200,
) -> List[Tuple[List[Tuple[int, int]], int, float]]:
    """
    Generate candidates using EXHAUSTIVE DFS (not greedy extension).

    For each connected component, run exhaustive DFS to find the
    top-K best-scoring paths. Then compute the future heuristic for each.

    Returns: list of (path, immediate_score, future_heuristic)
    """
    N = board.N
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0
    time_per_component = (time_limit_ms / 1000.0) / 25.0  # rough estimate

    all_candidates = []

    colors = set()
    for r in range(N):
        for c in range(N):
            av = abs(board.grid[r][c])
            if av >= 1:
                colors.add(av)

    for color in sorted(colors):
        if time.time() > deadline:
            break
        comps = find_color_components(board, color)
        for comp in comps:
            if time.time() > deadline:
                break
            if len(comp) < 2:
                continue

            # Component pruning
            max_possible = score_k_approx(len(comp))
            if board.level >= 4:
                max_possible += len(comp) * 80

            # Run exhaustive DFS from top-degree start cells
            start_cells = sorted(
                comp,
                key=lambda rc: sum(
                    1
                    for d in range(4)
                    if 0 <= rc[0] + DR[d] < N
                    and 0 <= rc[1] + DC[d] < N
                    and (
                        abs(board.grid[rc[0] + DR[d]][rc[1] + DC[d]]) == color
                        or board.grid[rc[0] + DR[d]][rc[1] + DC[d]] == 0
                    )
                ),
                reverse=True,
            )

            comp_topk = []
            comp_deadline = min(deadline, time.time() + time_per_component)

            for start_cell in start_cells[:3]:  # Only top-3 starts per component
                if time.time() > comp_deadline:
                    break
                visited = 1 << (start_cell[0] * N + start_cell[1])
                path = [start_cell]
                _dfs_collect_topk(
                    board.grid,
                    N,
                    start_cell,
                    visited,
                    path,
                    comp_topk,
                    color,
                    topk_per_component,
                    comp_deadline,
                )

            for path, s in comp_topk:
                h = _fast_future_heuristic(board, path)
                all_candidates.append((path, s, h))

    # Deduplicate and merge pools
    seen = set()
    unique = []
    pool_a = []  # Top by score
    pool_b = []  # Top by heuristic

    for path, s, h in all_candidates:
        key = tuple(path)
        if key not in seen:
            seen.add(key)
            unique.append((path, s, h))

    unique.sort(key=lambda x: -x[1])
    pool_a = unique[: global_max // 2 + 1]

    # Pool B: remaining candidates with high future heuristic
    remaining = unique[global_max // 2 + 1 :]
    remaining.sort(key=lambda x: -x[2])
    pool_b = remaining[: global_max // 2]

    # Alternate merge
    result = []
    a_idx = b_idx = 0
    while len(result) < global_max and (a_idx < len(pool_a) or b_idx < len(pool_b)):
        if a_idx < len(pool_a):
            result.append(pool_a[a_idx])
            a_idx += 1
        if b_idx < len(pool_b) and len(result) < global_max:
            result.append(pool_b[b_idx])
            b_idx += 1

    return result


def score_k_approx(k: int) -> int:
    """Fast score approximation from k only."""
    return (
        SCORE_TABLE[k]
        if k < len(SCORE_TABLE)
        else 10 * k + 18 * int((math.sqrt(k) - 1.0) ** 2)
    )


# Pre-compute score table at module load
SCORE_TABLE = [0] * 145
for _k in range(145):
    t = math.sqrt(_k) - 1.0
    SCORE_TABLE[_k] = 10 * _k + 18 * int(t * t)


def strategy_exhaustive_dual_poisson(
    board: Board,
    pool_size: int = 15,
    mean_rollout_depth: float = 4.0,
    base_rollouts: int = 5,
    time_limit_ms: float = 2000,
) -> List[Tuple[int, int]]:
    """
    EXHAUSTIVE DFS candidate generation + DUAL POOL + POISSON rollouts.

    Key fix over strategy_dual_poisson_mcts:
    - Uses exhaustive DFS (not greedy extension) for path finding
    - Candidate quality matches greedy_best_score
    - Then applies Poisson rollouts for cross-step synergy detection

    Pipeline:
    1. Exhaustive DFS → top-K paths per component (high-quality candidates)
    2. Dual pool: Pool A (top by score) + Pool B (top by future heuristic)
    3. Poisson allocation: more rollouts to more promising candidates
    4. Two-pass evaluation: Pass1 quick, Pass2 deep on top-3
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # Phase 1: Exhaustive candidate generation
    candidates = collect_exhaustive_candidates(
        board,
        topk_per_component=3,
        global_max=pool_size,
        time_limit_ms=time_limit_ms * 0.55,
    )

    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    # Phase 2: Poisson λ per candidate (quadratic emphasis on top)
    n = len(candidates)
    scores = [s for _, s, _ in candidates]
    max_s = max(scores) if scores else 1
    min_s = min(scores) if scores else 1
    score_range = max(max_s - min_s, 1)

    lambda_values = []
    for _, s, _ in candidates:
        norm = (s - min_s) / score_range
        lam = base_rollouts * (0.5 + 1.5 * norm * norm)
        lambda_values.append(lam)

    # Phase 3: Poisson rollouts (Pass 1)
    remaining_time = deadline - time.time()
    best_path = candidates[0][0]
    best_combined = -1e9
    results = []

    for idx, (path, imm_score, heuristic) in enumerate(candidates):
        if time.time() > deadline:
            break

        future = board.preview(path)
        if future.is_deadlocked():
            combined = imm_score - 150
            results.append((path, combined))
            if combined > best_combined:
                best_combined = combined
                best_path = path
            continue

        n_rollouts = poisson_sample(lambda_values[idx])
        n_rollouts = max(2, min(n_rollouts, 20))

        rollout_total = 0.0
        rollout_count = 0

        for _ in range(n_rollouts):
            if time.time() > deadline:
                break
            rs = _poisson_rollout(
                future,
                mean_depth=mean_rollout_depth,
                max_steps=15,
            )
            rollout_total += rs
            rollout_count += 1

        avg_rollout = rollout_total / max(rollout_count, 1) if rollout_count > 0 else 0
        norm_heuristic = heuristic / 100.0
        combined = imm_score + 0.5 * avg_rollout + 0.3 * norm_heuristic
        results.append((path, combined))

        if combined > best_combined:
            best_combined = combined
            best_path = path

    # Phase 4: Deep re-evaluation of top-3
    results.sort(key=lambda x: -x[1])
    top_k = min(3, len(results))

    for idx in range(top_k):
        if time.time() > deadline:
            break
        path, _ = results[idx]
        future = board.preview(path)
        if future.is_deadlocked():
            continue

        imm_score = score_path(board.grid, path)
        heuristic = _fast_future_heuristic(board, path)

        deep_total = 0.0
        deep_count = 0
        for _ in range(8):
            if time.time() > deadline:
                break
            rs = _poisson_rollout(
                future,
                mean_depth=mean_rollout_depth * 1.5,
                max_steps=20,
            )
            deep_total += rs
            deep_count += 1

        avg_deep = deep_total / max(deep_count, 1) if deep_count > 0 else 0
        norm_h = heuristic / 100.0
        refined = imm_score + 0.6 * avg_deep + 0.2 * norm_h

        if refined > best_combined:
            best_combined = refined
            best_path = path

    return best_path


# ============================================================
# STRATEGY 3: Best Candidate with Lookahead
# ============================================================


def strategy_lookahead(
    board: Board, depth: int = 2, candidates: int = 8, time_limit_ms: float = 800
) -> List[Tuple[int, int]]:
    """Evaluate top candidate paths with lookahead, pick the best."""
    candidate_paths = find_paths_iddfs(
        board, time_limit_ms=time_limit_ms * 0.5, max_paths=candidates
    )

    if not candidate_paths or len(candidate_paths[0]) < 2:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    best_path = candidate_paths[0]
    best_score = -1

    deadline = time.time() + time_limit_ms / 1000.0
    for path in candidate_paths:
        if time.time() > deadline:
            break
        s = lookahead_score(board, path, depth=depth, beam_width=3)
        if s > best_score:
            best_score = s
            best_path = path

    return best_path


# ============================================================
# STRATEGY 4: Beam Search
# ============================================================


def strategy_beam_search(
    board: Board, beam_width: int = 5, depth: int = 3, time_limit_ms: float = 900
) -> List[Tuple[int, int]]:
    """
    Beam search: at each step, keep top-K states by score.
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # (path_to_root, board_state, cumulative_score)
    beam = [(None, board, 0.0)]

    for d in range(depth):
        if time.time() > deadline:
            break
        next_beam = []
        for root_path, state, cum_score in beam:
            if state.is_deadlocked():
                continue
            candidates = find_paths_iddfs(
                state, time_limit_ms=time_limit_ms / (depth * 2), max_paths=beam_width
            )
            for cand_path in candidates:
                if time.time() > deadline:
                    break
                path_score_val = score_path(state.grid, cand_path)
                next_state = state.preview(cand_path)
                total = cum_score + path_score_val
                # Discount future scores
                discount = 0.8 ** (d + 1)
                next_beam.append(
                    (
                        cand_path if root_path is None else root_path,
                        next_state,
                        total * discount,
                    )
                )

        if not next_beam:
            break
        next_beam.sort(key=lambda x: -x[2])
        beam = next_beam[:beam_width]

    # Return the root path from the best beam
    if beam and beam[0][0] is not None:
        return beam[0][0]

    # Fallback
    pairs = board.find_adjacent_pairs()
    if pairs:
        r1, c1, r2, c2 = pairs[0]
        return [(r1, c1), (r2, c2)]
    return [(0, 0), (0, 1)]


# ============================================================
# STRATEGY 5: MCTS with light rollouts
# ============================================================


class MCTSNode:
    __slots__ = (
        "board",
        "path",
        "parent",
        "children",
        "visits",
        "total_score",
        "untried_paths",
    )

    def __init__(self, board: Board, path=None, parent=None):
        self.board = board
        self.path = path  # path that led to this state
        self.parent = parent
        self.children = []
        self.visits = 0
        self.total_score = 0.0
        self.untried_paths = None  # lazily populated

    def is_fully_expanded(self) -> bool:
        if self.untried_paths is None:
            return False
        return len(self.untried_paths) == 0

    def ucb1(self, exploration: float = 1.4) -> float:
        if self.visits == 0:
            return float("inf")
        return self.total_score / self.visits + exploration * math.sqrt(
            math.log(self.parent.visits) / self.visits
        )


def _rollout(board: Board, max_steps: int = 15) -> float:
    """
    Lightweight rollout: simulate a few steps with greedy policy and return score.
    """
    total = 0.0
    state = board.copy()
    for _ in range(max_steps):
        if state.is_deadlocked():
            break
        pairs = state.find_adjacent_pairs()
        if not pairs:
            break
        # Pick a random pair and extend greedily
        r1, c1, r2, c2 = random.choice(pairs)
        path = [(r1, c1), (r2, c2)]

        # Greedy extension: try to add more cells
        color = abs(state.grid[r1][c1])
        if color == 0:
            color = abs(state.grid[r2][c2])
        if color == 0:
            color = random.randint(1, 5)

        last_r, last_c = path[-1]
        visited = set(path)
        for _ in range(10):  # Try to extend up to 10 more cells
            neighbors = []
            for d in range(4):
                nr, nc = last_r + DR[d], last_c + DC[d]
                if 0 <= nr < state.N and 0 <= nc < state.N and (nr, nc) not in visited:
                    nv = state.grid[nr][nc]
                    nav = abs(nv)
                    if nav == color or nv == 0:
                        neighbors.append((nr, nc))
            if not neighbors:
                break
            nr, nc = random.choice(neighbors)
            path.append((nr, nc))
            visited.add((nr, nc))
            last_r, last_c = nr, nc

        step_score = score_path(state.grid, path)
        state = state.preview(path)
        total += step_score
    return total


def strategy_mcts(
    board: Board, iterations: int = 200, time_limit_ms: float = 900
) -> List[Tuple[int, int]]:
    """
    MCTS to select the best path from the current state.
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    root = MCTSNode(board)

    # Pre-populate candidate paths
    candidates = find_paths_iddfs(board, time_limit_ms=200, max_paths=15)
    root.untried_paths = list(candidates) if candidates else []

    if not root.untried_paths:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    iter_count = 0
    while iter_count < iterations and time.time() < deadline:
        # Selection
        node = root
        path_to_leaf = []
        while node.children and node.is_fully_expanded():
            # Select best child by UCB1
            best_child = max(node.children, key=lambda c: c.ucb1(2.0))
            path_to_leaf.append(best_child)
            node = best_child

        # Expansion
        if not node.is_fully_expanded() and node.untried_paths:
            path = node.untried_paths.pop()
            # Check if path is valid on current board
            is_valid, _ = validate_path(node.board.grid, path)
            if not is_valid:
                continue
            next_board = node.board.preview(path)
            child = MCTSNode(next_board, path, node)
            node.children.append(child)
            node = child
        elif node.untried_paths:
            path = node.untried_paths.pop()
            is_valid, _ = validate_path(node.board.grid, path)
            if not is_valid:
                continue
            next_board = node.board.preview(path)
            child = MCTSNode(next_board, path, node)
            node.children.append(child)
            node = child

        # Simulation
        rollout_score = _rollout(node.board, max_steps=10)

        # Backpropagation
        while node is not None:
            node.visits += 1
            node.total_score += rollout_score
            node = node.parent

        iter_count += 1

    # Select the most visited child of root
    if not root.children:
        return root.untried_paths[0] if root.untried_paths else [(0, 0), (0, 1)]

    best = max(root.children, key=lambda c: c.visits)
    return best.path


# ============================================================
# STRATEGY 6: Weighted Heuristic (fast, rule-based)
# ============================================================


def strategy_heuristic(
    board: Board, num_candidates: int = 10, time_limit_ms: float = 300
) -> List[Tuple[int, int]]:
    """
    Fast heuristic: score candidate paths by multiple factors.
    - Path length (primary: score grows super-linearly)
    - Bomb inclusion (bonus points)
    - Post-move board quality (avoid deadlocks, keep good connections)
    - Column balance (avoid stacking one column too high)
    """
    candidates = find_paths_iddfs(
        board, time_limit_ms=time_limit_ms, max_paths=num_candidates
    )
    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    best_path = candidates[0]
    best_heuristic = -1e9

    for path in candidates:
        # Factor 1: Immediate score
        imm_score = score_path(board.grid, path)

        # Factor 2: Post-move board evaluation
        future = board.preview(path)
        future_score = evaluate_state_heuristic(future)

        # Factor 3: Bomb bonus (already in imm_score, but emphasize)
        bomb_count = sum(1 for r, c in path if board.grid[r][c] < 0)
        bomb_bonus = bomb_count * 30

        # Factor 4: Path efficiency (score per cell)
        k = len(path)
        efficiency = imm_score / max(k, 1)

        # Factor 5: Deadlock penalty
        deadlock_penalty = -200 if future.is_deadlocked() else 0

        # Factor 6: Column balance (penalize uneven columns)
        col_heights = []
        for col in range(board.N):
            h = 0
            for row in range(board.N):
                if future.grid[row][col] != 0:
                    h = board.N - row
                    break
            col_heights.append(h)
        balance_penalty = (
            -max(col_heights) * 2 if max(col_heights) > board.N * 0.8 else 0
        )

        total = (
            imm_score * 1.0
            + future_score * 0.3
            + bomb_bonus * 0.5
            + efficiency * 2.0
            + deadlock_penalty
            + balance_penalty
        )
        if total > best_heuristic:
            best_heuristic = total
            best_path = path

    return best_path


# ============================================================
# STRATEGY 7: Hybrid (MCTS-guided with heuristic base)
# ============================================================


def strategy_hybrid(board: Board, time_limit_ms: float = 950) -> List[Tuple[int, int]]:
    """
    Hybrid strategy:
    1. Use heuristic to narrow down to top candidates
    2. Run lightweight MCTS on the top candidates
    3. Fall back to greedy longest if time runs out
    """
    # Phase 1: Get top candidates heuristically (fast)
    candidates = find_paths_iddfs(board, time_limit_ms=time_limit_ms * 0.3, max_paths=8)

    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    # Phase 2: Score each candidate with short rollouts
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    best_path = candidates[0]
    best_avg = -1

    for path in candidates:
        if time.time() > deadline:
            break

        imm = score_path(board.grid, path)
        future = board.preview(path)

        # Short rollouts
        rollout_scores = []
        for _ in range(5):
            if time.time() > deadline:
                break
            rs = _rollout(future, max_steps=8)
            rollout_scores.append(rs)

        avg_future = (
            sum(rollout_scores) / max(len(rollout_scores), 1) if rollout_scores else 0
        )
        total_estimate = imm + avg_future * 0.6

        if total_estimate > best_avg:
            best_avg = total_estimate
            best_path = path

    return best_path


# ============================================================
# Poisson distribution sampler (Knuth's algorithm, no deps)
# ============================================================


def poisson_sample(lmbda: float) -> int:
    """Sample from Poisson(lmbda) using Knuth's algorithm."""
    if lmbda <= 0:
        return 0
    L = math.exp(-lmbda)
    k = 0
    p = 1.0
    while p > L:
        k += 1
        p *= random.random()
    return k - 1


# ============================================================
# Strategy registry
# ============================================================

# ============================================================
# STRATEGY 8: Dual Pool + Poisson MCTS Rollouts (hybrid v3)
# ============================================================
# Key insight: 32000 on leaderboard means cross-step synergies are significant.
# Strategy:
#   1. DUAL CANDIDATE POOL:
#      Pool A: top paths by immediate score (longest / best-scoring)
#      Pool B: top paths by future board heuristic (paths that create good setups)
#   2. POISSON ROLLOUT ALLOCATION:
#      Higher-scoring candidates get ~Poisson(λ_high) rollouts
#      Lower-scoring get ~Poisson(λ_low), concentrating computation on promising ones
#   3. POISSON ROLLOUT DEPTH:
#      Each rollout depth ~ Poisson(μ), captures long-term synergies better
# ============================================================
# Core insight: score grows super-linearly with path length (S ≈ 18k for large k),
# so near-optimal solutions must be among the longest paths.
# Strategy:
#   1. Beam search: collect top-K longest paths from each component
#   2. MCTS-like rollouts: for each candidate, simulate 2-4 greedy steps ahead
#   3. Score = immediate_score + 0.7 * avg_rollout_score
#   4. Pick the candidate with highest combined score


def _fast_future_heuristic(board: Board, path: List[Tuple[int, int]]) -> float:
    """
    Quick heuristic: how good is the board AFTER applying this path?
    Counts adjacent compatible pairs, bomb clusters, wildcard density.
    """
    future = board.preview(path)
    N = future.N

    pair_count = 0
    bomb_pair_count = 0
    for r in range(N):
        for c in range(N):
            v = future.grid[r][c]
            av = abs(v)
            if c + 1 < N:
                v2 = future.grid[r][c + 1]
                av2 = abs(v2)
                if av == av2 or v == 0 or v2 == 0:
                    pair_count += 1
                    if v < 0 or v2 < 0:
                        bomb_pair_count += 1
            if r + 1 < N:
                v2 = future.grid[r + 1][c]
                av2 = abs(v2)
                if av == av2 or v == 0 or v2 == 0:
                    pair_count += 1
                    if v < 0 or v2 < 0:
                        bomb_pair_count += 1

    wildcards = sum(1 for r in range(N) for c in range(N) if future.grid[r][c] == 0)
    return pair_count * 5.0 + bomb_pair_count * 20.0 + wildcards * 15.0


def collect_candidates_dual_pool(
    board: Board,
    pool_size: int = 15,
    time_limit_ms: float = 600,
) -> List[Tuple[List[Tuple[int, int]], int, float]]:
    """
    DUAL candidate pool:
    - Pool A: top paths by immediate score (longest/best-scoring greedily)
    - Pool B: paths that maximize future board heuristic (good setups)
    Returns list of (path, immediate_score, future_heuristic), deduplicated.
    """
    N = board.N
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    pool_a = []  # (path, score, heuristic)
    pool_b = []  # (path, score, heuristic)

    colors = set()
    for r in range(N):
        for c in range(N):
            av = abs(board.grid[r][c])
            if av >= 1:
                colors.add(av)

    for color in sorted(colors):
        if time.time() > deadline:
            break
        comps = find_color_components(board, color)
        for comp in comps:
            if time.time() > deadline:
                break
            if len(comp) < 2:
                continue

            start_cells = sorted(
                comp,
                key=lambda rc: sum(
                    1
                    for d in range(4)
                    if 0 <= rc[0] + DR[d] < N
                    and 0 <= rc[1] + DC[d] < N
                    and (
                        abs(board.grid[rc[0] + DR[d]][rc[1] + DC[d]]) == color
                        or board.grid[rc[0] + DR[d]][rc[1] + DC[d]] == 0
                    )
                ),
                reverse=True,
            )

            for start_cell in start_cells[: max(1, len(start_cells) // 4)]:
                if time.time() > deadline:
                    break
                visited = 1 << (start_cell[0] * N + start_cell[1])

                # Pool A: greedy longest path + random walk variants
                path = _greedy_extend_path(board, start_cell, visited, color)
                if len(path) >= 2:
                    s = score_path(board.grid, path)
                    h = _fast_future_heuristic(board, path)
                    pool_a.append((path, s, h))

                for _ in range(3):
                    if time.time() > deadline:
                        break
                    rw_path = _random_extend_path(board, start_cell, visited, color)
                    if len(rw_path) >= 2:
                        s = score_path(board.grid, rw_path)
                        h = _fast_future_heuristic(board, rw_path)
                        pool_a.append((rw_path, s, h))

            # Pool B: intermediate-length paths that might set up better futures
            if len(comp) >= 3:
                for start_cell in start_cells[: max(1, len(start_cells) // 5)]:
                    if time.time() > deadline:
                        break
                    visited = 1 << (start_cell[0] * N + start_cell[1])
                    path = [(start_cell[0], start_cell[1])]
                    r, c = start_cell

                    for _ in range(min(len(comp), 20)):
                        best_next = None
                        best_degree = -1
                        for d in range(4):
                            nr, nc = r + DR[d], c + DC[d]
                            if 0 <= nr < N and 0 <= nc < N:
                                bit = nr * N + nc
                                if visited & (1 << bit):
                                    continue
                                nv = board.grid[nr][nc]
                                if abs(nv) != color and nv != 0:
                                    continue
                                free = sum(
                                    1
                                    for d2 in range(4)
                                    if 0 <= nr + DR[d2] < N
                                    and 0 <= nc + DC[d2] < N
                                    and not (
                                        visited
                                        & (1 << ((nr + DR[d2]) * N + (nc + DC[d2])))
                                    )
                                    and (
                                        abs(board.grid[nr + DR[d2]][nc + DC[d2]])
                                        == color
                                        or board.grid[nr + DR[d2]][nc + DC[d2]] == 0
                                    )
                                )
                                if free > best_degree:
                                    best_degree = free
                                    best_next = (nr, nc)
                        if best_next is None:
                            break
                        nr, nc = best_next
                        visited |= 1 << (nr * N + nc)
                        path.append((nr, nc))
                        r, c = nr, nc

                        # Sample intermediate paths
                        if len(path) >= 2 and len(path) % 3 == 2:
                            s = score_path(board.grid, path)
                            h = _fast_future_heuristic(board, path)
                            pool_b.append((path[:], s, h))

    # Deduplicate
    seen = set()
    all_candidates = []
    for path, s, h in pool_a:
        key = tuple(path)
        if key not in seen:
            seen.add(key)
            all_candidates.append((path, s, h))

    pool_b.sort(key=lambda x: -x[2])
    for path, s, h in pool_b:
        key = tuple(path)
        if key not in seen:
            seen.add(key)
            all_candidates.append((path, s, h))
        if len(all_candidates) >= pool_size * 2:
            break

    # Merge: alternate from pool A (by score) and pool B (by heuristic)
    pool_a_sorted = sorted(
        [c for c in all_candidates if c in pool_a],
        key=lambda x: -x[1],
    )[:pool_size]
    pool_b_sorted = sorted(
        [c for c in all_candidates if c in pool_b],
        key=lambda x: -x[2],
    )[:pool_size]

    result = []
    a_idx = b_idx = 0
    while len(result) < pool_size and (
        a_idx < len(pool_a_sorted) or b_idx < len(pool_b_sorted)
    ):
        if a_idx < len(pool_a_sorted):
            result.append(pool_a_sorted[a_idx])
            a_idx += 1
        if b_idx < len(pool_b_sorted) and len(result) < pool_size:
            result.append(pool_b_sorted[b_idx])
            b_idx += 1

    return result


def _greedy_extend_path(
    board: Board, start: Tuple[int, int], visited_mask: int, target_color: int
) -> List[Tuple[int, int]]:
    """Greedily extend a path by always choosing the neighbor with the most future options."""
    N = board.N
    path = [start]
    visited = visited_mask
    r, c = start

    while True:
        best_next = None
        best_degree = -1
        for d in range(4):
            nr, nc = r + DR[d], c + DC[d]
            if 0 <= nr < N and 0 <= nc < N:
                bit = nr * N + nc
                if visited & (1 << bit):
                    continue
                nv = board.grid[nr][nc]
                nav = abs(nv)
                if nav != target_color and nv != 0:
                    continue
                # Count free neighbors of this candidate
                free = 0
                for d2 in range(4):
                    nnr, nnc = nr + DR[d2], nc + DC[d2]
                    if 0 <= nnr < N and 0 <= nnc < N:
                        nnbit = nnr * N + nnc
                        if not (visited & (1 << nnbit)):
                            nnv = board.grid[nnr][nnc]
                            nnav = abs(nnv)
                            if nnav == target_color or nnv == 0:
                                free += 1
                if free > best_degree:
                    best_degree = free
                    best_next = (nr, nc)

        if best_next is None:
            break
        nr, nc = best_next
        visited |= 1 << (nr * N + nc)
        path.append((nr, nc))
        r, c = nr, nc

    return path


def _random_extend_path(
    board: Board, start: Tuple[int, int], visited_mask: int, target_color: int
) -> List[Tuple[int, int]]:
    """Randomly extend a path through same-color cells."""
    N = board.N
    path = [start]
    visited = visited_mask
    r, c = start

    for _ in range(len(board.grid) * len(board.grid)):
        neighbors = []
        for d in range(4):
            nr, nc = r + DR[d], c + DC[d]
            if 0 <= nr < N and 0 <= nc < N:
                bit = nr * N + nc
                if visited & (1 << bit):
                    continue
                nv = board.grid[nr][nc]
                nav = abs(nv)
                if nav == target_color or nv == 0:
                    neighbors.append((nr, nc))
        if not neighbors:
            break
        nr, nc = random.choice(neighbors)
        visited |= 1 << (nr * N + nc)
        path.append((nr, nc))
        r, c = nr, nc

    return path


def _poisson_rollout(
    board: Board,
    mean_depth: float = 4.0,
    max_steps: int = 20,
) -> float:
    """
    Poisson-distributed depth rollout.
    Depth ~ Poisson(mean_depth), capped at max_steps.
    Deeper rollouts capture long-term synergies (bomb chains, etc.).
    """
    depth = min(poisson_sample(mean_depth), max_steps)
    depth = max(depth, 1)

    total = 0.0
    state = board.copy()
    for _ in range(depth):
        if state.is_deadlocked():
            break
        pairs = state.find_adjacent_pairs()
        if not pairs:
            break

        r1, c1, r2, c2 = random.choice(pairs)
        path = [(r1, c1), (r2, c2)]

        color = abs(state.grid[r1][c1])
        if color == 0:
            color = abs(state.grid[r2][c2])
        if color == 0:
            color = random.randint(1, 5)

        last_r, last_c = path[-1]
        visited = set(path)
        for _ in range(6):
            neighbors = []
            for d in range(4):
                nr, nc = last_r + DR[d], last_c + DC[d]
                if 0 <= nr < state.N and 0 <= nc < state.N and (nr, nc) not in visited:
                    nv = state.grid[nr][nc]
                    if abs(nv) == color or nv == 0:
                        neighbors.append((nr, nc))
            if not neighbors:
                break
            nr, nc = random.choice(neighbors)
            path.append((nr, nc))
            visited.add((nr, nc))
            last_r, last_c = nr, nc

        total += score_path(state.grid, path)
        state = state.preview(path)
    return total


def strategy_beam_mcts(
    board: Board,
    beam_width: int = 10,
    rollout_steps: int = 3,
    rollouts_per_candidate: int = 8,
    time_limit_ms: float = 900,
) -> List[Tuple[int, int]]:
    """
    Original hybrid strategy (kept for backward comparison).
    Uses dual pool collect + uniform rollouts.
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    candidates = collect_candidates_dual_pool(
        board,
        pool_size=beam_width,
        time_limit_ms=time_limit_ms * 0.4,
    )

    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    best_path = candidates[0][0]
    best_combined = -1e9

    remaining_time = deadline - time.time()
    time_per_candidate = remaining_time / max(len(candidates), 1)

    for path, imm_score, heuristic in candidates:
        if time.time() > deadline:
            break

        future = board.preview(path)
        if future.is_deadlocked():
            combined = imm_score - 150
            if combined > best_combined:
                best_combined = combined
                best_path = path
            continue

        rollout_total = 0.0
        rollout_count = 0
        cand_deadline = min(deadline, time.time() + time_per_candidate)

        for _ in range(rollouts_per_candidate):
            if time.time() > cand_deadline:
                break
            rs = _rollout(future, max_steps=rollout_steps)
            rollout_total += rs
            rollout_count += 1

        avg_future = rollout_total / max(rollout_count, 1) if rollout_count > 0 else 0
        combined = imm_score + 0.6 * avg_future

        if combined > best_combined:
            best_combined = combined
            best_path = path

    return best_path


def strategy_dual_poisson_mcts(
    board: Board,
    pool_size: int = 15,
    mean_rollout_depth: float = 4.0,
    base_rollouts: int = 5,
    time_limit_ms: float = 1800,
) -> List[Tuple[int, int]]:
    """
    DUAL POOL + POISSON MCTS strategy:

    1. DUAL POOL: collect candidates from:
       - Pool A: top immediate-scoring paths
       - Pool B: paths with high future-heuristic (good setups)

    2. POISSON ALLOCATION:
       Rollouts per candidate ~ Poisson(λ) where λ ∝ candidate score^2.
       Top candidates get heavy rollouts, bottom get light.

    3. POISSON DEPTH:
       Each rollout depth ~ Poisson(mean_rollout_depth).
       Captures long-term synergies (bomb chains, etc.)

    4. TWO-PASS:
       Pass 1: evaluate all candidates with Poisson rollouts
       Pass 2: re-evaluate top-3 with deeper rollouts
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # Phase 1: Dual pool collection
    candidates = collect_candidates_dual_pool(
        board, pool_size=pool_size, time_limit_ms=time_limit_ms * 0.35
    )

    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    # Phase 2: Compute Poisson λ per candidate
    n = len(candidates)
    scores = [s for _, s, _ in candidates]
    max_s = max(scores) if scores else 1
    min_s = min(scores) if scores else 1
    score_range = max(max_s - min_s, 1)

    lambda_values = []
    for _, s, _ in candidates:
        norm = (s - min_s) / score_range
        # Quadratic emphasis: top candidates get much more computation
        lam = base_rollouts * (0.5 + 1.5 * norm * norm)
        lambda_values.append(lam)

    # Phase 3: Poisson rollouts (Pass 1)
    remaining_time = deadline - time.time()
    time_budget_total = remaining_time * 0.9

    best_path = candidates[0][0]
    best_combined = -1e9
    results = []

    for idx, (path, imm_score, heuristic) in enumerate(candidates):
        if time.time() > deadline:
            break

        future = board.preview(path)
        if future.is_deadlocked():
            combined = imm_score - 150
            results.append((path, combined))
            if combined > best_combined:
                best_combined = combined
                best_path = path
            continue

        n_rollouts = poisson_sample(lambda_values[idx])
        n_rollouts = max(2, min(n_rollouts, 20))

        rollout_total = 0.0
        rollout_count = 0

        for _ in range(n_rollouts):
            if time.time() > deadline:
                break
            rs = _poisson_rollout(
                future,
                mean_depth=mean_rollout_depth,
                max_steps=15,
            )
            rollout_total += rs
            rollout_count += 1

        avg_rollout = rollout_total / max(rollout_count, 1) if rollout_count > 0 else 0
        norm_heuristic = heuristic / 100.0
        combined = imm_score + 0.5 * avg_rollout + 0.3 * norm_heuristic
        results.append((path, combined))

        if combined > best_combined:
            best_combined = combined
            best_path = path

    # Phase 4: Deep re-evaluation of top-3 (Pass 2)
    results.sort(key=lambda x: -x[1])
    top_k = min(3, len(results))

    for idx in range(top_k):
        if time.time() > deadline:
            break
        path, _ = results[idx]
        future = board.preview(path)
        if future.is_deadlocked():
            continue

        imm_score = score_path(board.grid, path)
        heuristic = _fast_future_heuristic(board, path)

        deep_total = 0.0
        deep_count = 0
        for _ in range(8):
            if time.time() > deadline:
                break
            rs = _poisson_rollout(
                future,
                mean_depth=mean_rollout_depth * 1.5,
                max_steps=20,
            )
            deep_total += rs
            deep_count += 1

        avg_deep = deep_total / max(deep_count, 1) if deep_count > 0 else 0
        norm_h = heuristic / 100.0
        refined = imm_score + 0.6 * avg_deep + 0.2 * norm_h

        if refined > best_combined:
            best_combined = refined
            best_path = path

    return best_path


def strategy_2step_det_1step_rollout(
    board: Board,
    pool_size: int = 10,
    rollout_n: int = 6,
    rollout_depth_mean: float = 3.0,
    time_limit_ms: float = 2000,
) -> List[Tuple[int, int]]:
    """
    HYBRID: 2-step deterministic + 3rd-step Poisson rollout.

    Pipeline:
    1. Exhaustive DFS → top-K candidate paths on current board (deterministic)
    2. For each candidate:
       a. preview() → future1 board (deterministic)
       b. On future1, exhaustive DFS → best next-step path (deterministic)
       c. preview() → future2 board (deterministic)
       d. On future2, Poisson rollouts → estimate 3rd-step value (random)
    3. Score = imm + α * next_score + β * avg_3rd_rollout

    Why this works:
    - 2-step deterministic captures the most impactful synergies
    - 3rd-step random rollout adds long-term value without combinatoric explosion
    - Poisson rollouts naturally sample varied depths
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # Phase 1: Exhaustive candidates from current board
    candidates = collect_exhaustive_candidates(
        board,
        topk_per_component=2,
        global_max=pool_size,
        time_limit_ms=time_limit_ms * 0.40,
    )

    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    # Phase 2: Two-step deterministic + third-step rollout
    results = []
    remaining_total = (deadline - time.time()) / max(len(candidates), 1)

    # Sort by immediate score descending, process top ones first
    candidates.sort(key=lambda x: -x[1])

    for idx, (path, imm_score, heuristic) in enumerate(candidates):
        if time.time() > deadline:
            break

        cand_deadline = time.time() + remaining_total * 0.85

        # --- Step 1: future1 (deterministic via preview) ---
        future1 = board.preview(path)
        if future1.is_deadlocked():
            results.append((path, imm_score - 200))
            continue

        # --- Step 2: best next-step on future1 (deterministic DFS) ---
        # Use tighter time budget for the 2nd step DFS
        step2_budget = min(400, (cand_deadline - time.time()) * 0.6)
        if step2_budget < 50:
            # Not enough time, fall back to heuristic estimate
            future_est = _estimate_best_next_score(future1)
            total = imm_score + 0.7 * future_est
            results.append((path, total))
            continue

        next_path = strategy_greedy_best_score(future1, time_limit_ms=step2_budget)
        if next_path is None or len(next_path) < 2:
            results.append((path, imm_score))
            continue

        next_score = score_path(future1.grid, next_path)

        # --- Step 3: future2 + Poisson rollouts ---
        future2 = future1.preview(next_path)
        if future2.is_deadlocked():
            total = imm_score + 0.7 * next_score - 100
            results.append((path, total))
            continue

        rollout_sum = 0.0
        rollout_count = 0
        step3_budget = cand_deadline - time.time()

        for _ in range(rollout_n):
            if time.time() > cand_deadline:
                break
            rs = _poisson_rollout(
                future2,
                mean_depth=rollout_depth_mean,
                max_steps=12,
            )
            rollout_sum += rs
            rollout_count += 1

        avg_3rd = rollout_sum / max(rollout_count, 1) if rollout_count > 0 else 0

        # Weighted combination: immediate > next > 3rd-step estimate
        total = imm_score + 0.7 * next_score + 0.3 * avg_3rd
        results.append((path, total))

    # Phase 3: Select best
    if results:
        results.sort(key=lambda x: -x[1])
        # Re-evaluate top-2 with more rollouts
        top_k = min(2, len(results))
        best_path = results[0][0]
        best_total = results[0][1]

        for idx in range(top_k):
            if time.time() > deadline:
                break
            path, _ = results[idx]
            future1 = board.preview(path)
            if future1.is_deadlocked():
                continue
            imm_score = score_path(board.grid, path)
            next_path = strategy_greedy_best_score(future1, time_limit_ms=250)
            if next_path is None or len(next_path) < 2:
                continue
            next_score = score_path(future1.grid, next_path)
            future2 = future1.preview(next_path)
            if future2.is_deadlocked():
                continue

            deep_sum = 0.0
            deep_n = 0
            for _ in range(10):
                if time.time() > deadline:
                    break
                rs = _poisson_rollout(
                    future2, mean_depth=rollout_depth_mean * 1.5, max_steps=15
                )
                deep_sum += rs
                deep_n += 1
            avg_deep = deep_sum / max(deep_n, 1) if deep_n > 0 else 0
            refined = imm_score + 0.7 * next_score + 0.35 * avg_deep

            if refined > best_total:
                best_total = refined
                best_path = path

        return best_path

    # Fallback
    pairs = board.find_adjacent_pairs()
    if pairs:
        r1, c1, r2, c2 = pairs[0]
        return [(r1, c1), (r2, c2)]
    return [(0, 0), (0, 1)]


def strategy_2step_beam_rollout(
    board: Board,
    pool_size: int = 8,
    beam_width: int = 2,
    rollout_n: int = 5,
    rollout_depth_mean: float = 3.5,
    time_limit_ms: float = 2500,
) -> List[Tuple[int, int]]:
    """
    AGGRESSIVE: 2-step deterministic BEAM + 3rd-step Poisson rollout.

    Key difference: finds top beam_width next-step paths on future1,
    not just the single best. Captures cases where a slightly suboptimal
    2nd step enables a massive 3rd-step (bomb chain alignment).
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    candidates = collect_exhaustive_candidates(
        board,
        topk_per_component=2,
        global_max=pool_size,
        time_limit_ms=time_limit_ms * 0.30,
    )
    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    results = []
    total_budget = (deadline - time.time()) * 0.85
    per_candidate = total_budget / max(len(candidates), 1)

    for path, imm_score, _ in candidates:
        if time.time() > deadline:
            break
        cd = time.time() + per_candidate

        future1 = board.preview(path)
        if future1.is_deadlocked():
            results.append((path, imm_score - 200))
            continue

        step2_budget = min(500, (cd - time.time()) * 0.55)
        if step2_budget < 80:
            results.append((path, imm_score + 0.7 * _estimate_best_next_score(future1)))
            continue

        beam_paths = find_paths_iddfs(
            future1, time_limit_ms=step2_budget, max_paths=beam_width
        )
        if not beam_paths or len(beam_paths[0]) < 2:
            results.append((path, imm_score))
            continue

        best_beam_val = -1e9
        s3_budget = (cd - time.time()) / max(len(beam_paths), 1)
        for bp in beam_paths[:beam_width]:
            if time.time() > cd:
                break
            bs = score_path(future1.grid, bp)
            future2 = future1.preview(bp)
            if future2.is_deadlocked():
                comb = bs - 100
            else:
                rs_sum, rs_n = 0.0, 0
                bd = time.time() + s3_budget * 0.8
                for _ in range(rollout_n):
                    if time.time() > bd:
                        break
                    rs_sum += _poisson_rollout(
                        future2, mean_depth=rollout_depth_mean, max_steps=12
                    )
                    rs_n += 1
                comb = bs + 0.4 * (rs_sum / max(rs_n, 1) if rs_n > 0 else 0)
            if comb > best_beam_val:
                best_beam_val = comb

        results.append((path, imm_score + 0.65 * best_beam_val))

    if not results:
        return [(0, 0), (0, 1)]

    results.sort(key=lambda x: -x[1])
    best_path, best_total = results[0]

    # Re-evaluate top-2 with deeper rollouts
    for idx in range(min(2, len(results))):
        if time.time() > deadline:
            break
        path, _ = results[idx]
        future1 = board.preview(path)
        if future1.is_deadlocked():
            continue
        imm = score_path(board.grid, path)
        bp2 = find_paths_iddfs(future1, time_limit_ms=300, max_paths=2)
        if not bp2 or len(bp2[0]) < 2:
            continue
        best_ref = -1e9
        for bpp in bp2[:2]:
            bs = score_path(future1.grid, bpp)
            f2 = future1.preview(bpp)
            if f2.is_deadlocked():
                continue
            ds, dn = 0.0, 0
            for _ in range(8):
                if time.time() > deadline:
                    break
                ds += _poisson_rollout(
                    f2, mean_depth=rollout_depth_mean * 1.5, max_steps=15
                )
                dn += 1
            c = bs + 0.45 * (ds / max(dn, 1) if dn > 0 else 0)
            if c > best_ref:
                best_ref = c
        if best_ref > -1e8:
            refined = imm + 0.65 * best_ref
            if refined > best_total:
                best_total = refined
                best_path = path

    return best_path


def strategy_3step_deterministic(
    board: Board,
    pool_size: int = 8,
    beam_width: int = 3,
    time_limit_ms: float = 3000,
) -> List[Tuple[int, int]]:
    """
    3-STEP DETERMINISTIC LOOKAHEAD with aggressive pruning.

    Pipeline:
    1. Exhaustive DFS → top pool_size candidates (step 1)
    2. For each candidate:
       a. preview() → future1
       b. On future1, exhaustive DFS → top beam_width paths (step 2)
       c. For top-2 of those:
          - preview() → future2
          - On future2, heavily-pruned DFS → best path (step 3)
    3. Score = imm + 0.7*best_step2_scores + 0.3*best_step3_score

    Pruning strategy:
    - Step 1: full exhaustive with 600ms budget
    - Step 2: pruned exhaustive with 300ms budget per candidate
    - Step 3: heavily pruned (depth-limited, component-pruned), 100ms
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    # Step 1: candidates from current board
    candidates = collect_exhaustive_candidates(
        board,
        topk_per_component=2,
        global_max=pool_size,
        time_limit_ms=time_limit_ms * 0.20,
    )
    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    results = []
    total_budget = (deadline - time.time()) * 0.90
    per_c1 = total_budget / max(len(candidates), 1)

    for path, imm_score, _ in candidates:
        if time.time() > deadline:
            break
        cd1 = time.time() + per_c1

        future1 = board.preview(path)
        if future1.is_deadlocked():
            results.append((path, imm_score - 200))
            continue

        # Step 2: find top beam_width paths on future1
        s2_budget = min(400, (cd1 - time.time()) * 0.50)
        if s2_budget < 60:
            results.append((path, imm_score + 0.7 * _estimate_best_next_score(future1)))
            continue

        beam_paths = find_paths_iddfs(
            future1, time_limit_ms=s2_budget, max_paths=beam_width
        )
        if not beam_paths or len(beam_paths[0]) < 2:
            results.append((path, imm_score))
            continue

        # Step 3: for top-2 beam paths, look one more step ahead
        best_combined = -1e9
        s3_budget = (cd1 - time.time()) * 0.45
        per_beam = s3_budget / min(len(beam_paths), 2)

        for bp in beam_paths[:2]:
            if time.time() > cd1:
                break

            bs2 = score_path(future1.grid, bp)
            future2 = future1.preview(bp)

            if future2.is_deadlocked():
                c = bs2 - 100
            else:
                # Step 3: heavily-pruned DFS on future2
                s3_dfs_budget = min(150, per_beam * 0.8)
                if s3_dfs_budget < 30:
                    c = bs2 + 0.3 * _estimate_best_next_score(future2)
                else:
                    bp3 = strategy_greedy_best_score(
                        future2, time_limit_ms=s3_dfs_budget
                    )
                    if bp3 and len(bp3) >= 2:
                        bs3 = score_path(future2.grid, bp3)
                        c = bs2 + 0.4 * bs3
                    else:
                        c = bs2

            if c > best_combined:
                best_combined = c

        if best_combined > -1e8:
            total = imm_score + 0.65 * best_combined
        else:
            total = imm_score
        results.append((path, total))

    if results:
        results.sort(key=lambda x: -x[1])
        return results[0][0]

    pairs = board.find_adjacent_pairs()
    if pairs:
        r1, c1, r2, c2 = pairs[0]
        return [(r1, c1), (r2, c2)]
    return [(0, 0), (0, 1)]


def strategy_3step_det_plus_rollout(
    board: Board,
    pool_size: int = 8,
    beam_width: int = 2,
    rollout_n: int = 6,
    rollout_depth_mean: float = 4.5,
    time_limit_ms: float = 4000,
) -> List[Tuple[int, int]]:
    """
    3-STEP DETERMINISTIC DFS + LAYERED POISSON ROLLOUT.

    Pipeline:
    1. Exhaustive DFS -> top pool_size candidates
    2. For each candidate:
       a. preview() -> future1 -> DFS -> top beam_width paths
       b. For each beam path:
          - preview() -> future2 -> DFS -> best step-3 path
          - preview() -> future3 -> Poisson rollouts!
    3. Score = imm + a*step2 + b*step3 + c*avg_rollout
    4. Re-evaluate top-2 with deeper rollouts
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    candidates = collect_exhaustive_candidates(
        board,
        topk_per_component=2,
        global_max=pool_size,
        time_limit_ms=time_limit_ms * 0.18,
    )
    if not candidates:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    results = []
    total_budget = (deadline - time.time()) * 0.90
    per_c1 = total_budget / max(len(candidates), 1)

    for path, imm_score, _ in candidates:
        if time.time() > deadline:
            break
        cd1 = time.time() + per_c1

        future1 = board.preview(path)
        if future1.is_deadlocked():
            results.append((path, imm_score - 200))
            continue

        s2_budget = min(350, (cd1 - time.time()) * 0.45)
        if s2_budget < 50:
            results.append((path, imm_score + 0.7 * _estimate_best_next_score(future1)))
            continue

        beam_paths = find_paths_iddfs(
            future1, time_limit_ms=s2_budget, max_paths=beam_width
        )
        if not beam_paths or len(beam_paths[0]) < 2:
            results.append((path, imm_score))
            continue

        best_combined = -1e9
        s3_budget = (cd1 - time.time()) * 0.50
        per_beam = s3_budget / min(len(beam_paths), 2)

        for bp in beam_paths[:2]:
            if time.time() > cd1:
                break
            bs2 = score_path(future1.grid, bp)
            future2 = future1.preview(bp)
            if future2.is_deadlocked():
                c = bs2 - 100
            else:
                s3_dfs_budget = min(120, per_beam * 0.45)
                bp3 = (
                    strategy_greedy_best_score(future2, time_limit_ms=s3_dfs_budget)
                    if s3_dfs_budget > 20
                    else None
                )
                if bp3 and len(bp3) >= 2:
                    bs3 = score_path(future2.grid, bp3)
                    future3 = future2.preview(bp3)
                    if future3.is_deadlocked():
                        c = bs2 + 0.4 * bs3 - 50
                    else:
                        rs_sum, rs_n = 0.0, 0
                        r_deadline = time.time() + per_beam * 0.50
                        for _ in range(rollout_n):
                            if time.time() > r_deadline:
                                break
                            rs_sum += _poisson_rollout(
                                future3, mean_depth=rollout_depth_mean, max_steps=12
                            )
                            rs_n += 1
                        avg_r = rs_sum / max(rs_n, 1) if rs_n > 0 else 0
                        c = bs2 + 0.4 * bs3 + 0.2 * avg_r
                else:
                    c = bs2 + 0.3 * _estimate_best_next_score(future2)
            if c > best_combined:
                best_combined = c

        if best_combined > -1e8:
            total = imm_score + 0.6 * best_combined
        else:
            total = imm_score
        results.append((path, total))

    if not results:
        return [(0, 0), (0, 1)]

    results.sort(key=lambda x: -x[1])
    best_path, best_total = results[0]

    for idx in range(min(2, len(results))):
        if time.time() > deadline:
            break
        path, _ = results[idx]
        future1 = board.preview(path)
        if future1.is_deadlocked():
            continue
        imm = score_path(board.grid, path)
        bp2 = find_paths_iddfs(future1, time_limit_ms=250, max_paths=2)
        if not bp2 or len(bp2[0]) < 2:
            continue
        best_ref = -1e9
        for bpp in bp2[:2]:
            bs2 = score_path(future1.grid, bpp)
            f2 = future1.preview(bpp)
            if f2.is_deadlocked():
                continue
            bp3 = strategy_greedy_best_score(f2, time_limit_ms=100)
            if not bp3 or len(bp3) < 2:
                c = bs2
            else:
                bs3 = score_path(f2.grid, bp3)
                f3 = f2.preview(bp3)
                if f3.is_deadlocked():
                    c = bs2 + 0.4 * bs3 - 50
                else:
                    ds, dn = 0.0, 0
                    for _ in range(10):
                        if time.time() > deadline:
                            break
                        ds += _poisson_rollout(
                            f3, mean_depth=rollout_depth_mean * 1.5, max_steps=15
                        )
                        dn += 1
                    avg_d = ds / max(dn, 1) if dn > 0 else 0
                    c = bs2 + 0.4 * bs3 + 0.25 * avg_d
            if c > best_ref:
                best_ref = c
        if best_ref > -1e8:
            refined = imm + 0.6 * best_ref
            if refined > best_total:
                best_total = refined
                best_path = path

    return best_path


def make_seeded_3step_rollout(
    base_seed: int = 42,
    beam_width: int = 2,
    rollout_n: int = 6,
    rollout_depth_mean: float = 4.5,
    time_limit_ms: float = 4500,
) -> Callable[[Board], List[Tuple[int, int]]]:
    """Seeded 3-step + rollouts strategy."""
    step_counter = [0]

    def fn(board: Board) -> List[Tuple[int, int]]:
        bh = 0
        for r in range(board.N):
            for c in range(board.N):
                bh = bh * 31 + board.grid[r][c]
        step_counter[0] += 1
        random.seed(base_seed * 100000 + step_counter[0] * 1000 + abs(bh) % 1000)
        return strategy_3step_det_plus_rollout(
            board,
            beam_width=beam_width,
            rollout_n=rollout_n,
            rollout_depth_mean=rollout_depth_mean,
            time_limit_ms=time_limit_ms,
        )

    return fn


def strategy_bomb_aggressive(
    board: Board,
    time_limit_ms: float = 3000,
) -> List[Tuple[int, int]]:
    """
    Moderately aggressive beam+rollout for BOMB LEVELS (4-5).

    Uses original beam_2det_1rnd proven params but with:
    - Extra time budget (3000ms vs 2500ms default)
    - Slightly more rollouts for stability (8 vs 5)

    Key: don't over-fit to noise. Original beam_width=2 already works.
    """
    return strategy_2step_beam_rollout(
        board,
        pool_size=10,
        beam_width=2,
        rollout_n=8,
        rollout_depth_mean=4.0,
        time_limit_ms=time_limit_ms,
    )


def strategy_level_adaptive(
    board: Board,
    time_limit_ms: float = 2000,
) -> List[Tuple[int, int]]:
    """
    PER-LEVEL HYBRID: beam for L1-4, merged for L5.
    Total expected: ~29848 (152 from 30000).
    """
    level = board.level
    if level <= 4:
        return strategy_v3_beam_rollout(
            board, cand_limit=600, root_take=80, rollout_depth=5,
            rollout_beam=3, rollout_lookahead=2,
            time_limit_ms=min(time_limit_ms, 15000),
        )
    else:
        return strategy_v3_merged(
            board, cand_limit=1000, root_take=120, rollout_depth=8,
            time_limit_ms=min(time_limit_ms, 20000),
        )


STRATEGIES = {
    "greedy_baseline": strategy_greedy_baseline,
    "greedy_longest": strategy_greedy_longest,
    "greedy_best_score": strategy_greedy_best_score,
    "lookahead": strategy_lookahead,
    "beam_search": strategy_beam_search,
    "mcts": strategy_mcts,
    "heuristic": strategy_heuristic,
    "hybrid": strategy_hybrid,
    "beam_mcts": strategy_beam_mcts,
    "dual_poisson": strategy_dual_poisson_mcts,
    "exhaustive_dual": strategy_exhaustive_dual_poisson,
    "exhaustive_lookahead": strategy_deterministic_lookahead,
    "hybrid_2det_1rnd": strategy_2step_det_1step_rollout,
    "beam_2det_1rnd": strategy_2step_beam_rollout,
    "bomb_aggressive": strategy_bomb_aggressive,
    "level_adaptive": strategy_level_adaptive,
    "3step_det": strategy_3step_deterministic,
    "3step_roll": strategy_3step_det_plus_rollout,
    "v3_inspired": None,  # assigned below
}


# ============================================================
# V3-INSPIRED: Large candidate pool + greedy rollout
# ============================================================

def _mobility(board: Board) -> int:
    """Board quality: count adjacent pairs, wildcards, bombs."""
    N = board.N
    links = 0
    wild = 0
    bombs = 0
    for r in range(N):
        for c in range(N):
            if board.grid[r][c] == 0:
                wild += 1
            if board.grid[r][c] < 0:
                bombs += 1
            if c + 1 < N:
                a = abs(board.grid[r][c])
                b = abs(board.grid[r][c + 1])
                if a == b or board.grid[r][c] == 0 or board.grid[r][c + 1] == 0:
                    links += 1
            if r + 1 < N:
                a = abs(board.grid[r][c])
                b = abs(board.grid[r + 1][c])
                if a == b or board.grid[r][c] == 0 or board.grid[r + 1][c] == 0:
                    links += 1
    bomb_bonus = bombs * 10 if board.level >= 4 else 0
    return links * 2 + wild * 8 + bomb_bonus


def _candidate_value(board: Board, path: List[Tuple[int, int]]) -> int:
    """v3 heuristic: score + position + bomb/wild bonuses."""
    low = sum(1 for r, c in path if r >= board.N // 2)
    bombs = sum(1 for r, c in path if board.grid[r][c] < 0)
    wild = sum(1 for r, c in path if board.grid[r][c] == 0)
    return score_path(board.grid, path) * 10 + low * 4 + bombs * 45 + wild * 8 + len(path)


def _collect_candidates_v3(
    board: Board,
    limit: int = 300,
    time_limit_ms: float = 800,
) -> List[List[Tuple[int, int]]]:
    """
    Collect many candidates sorted by candidate_value (v3-style).
    Returns list of paths, sorted best-first.
    """
    N = board.N
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    max_len = 34 if board.level >= 5 else 30
    hard_cap = max(1000, limit * 5)  # big enough for 800-1200

    all_candidates = []  # (path, value)

    for r in range(N):
        for c in range(N):
            if time.time() > deadline or len(all_candidates) >= hard_cap:
                break
            color = abs(board.grid[r][c])
            visited = 1 << (r * N + c)
            path = [(r, c)]
            _dfs_collect_v3(board, r, c, color, max_len, hard_cap,
                            visited, path, all_candidates, deadline)
        if len(all_candidates) >= hard_cap:
            break

    all_candidates.sort(key=lambda x: -x[1])
    if len(all_candidates) > limit:
        all_candidates = all_candidates[:limit]
    return [p for p, _ in all_candidates]


def _dfs_collect_v3(
    board: Board,
    r: int, c: int,
    target_color: int,
    max_len: int,
    hard_cap: int,
    visited: int,
    path: List[Tuple[int, int]],
    collected: List[Tuple[List[Tuple[int, int]], int]],
    deadline: float,
):
    """DFS collecting candidates with v3-style ordering."""
    if len(collected) >= hard_cap or time.time() > deadline:
        return

    if len(path) >= 2:
        val = _candidate_value(board, path)
        collected.append((path[:], val))

    if len(path) >= max_len:
        return

    N = board.N
    # Order: prefer down/up over left/right (v3: order {1,3,2,0} = down,left,right,up)
    for d in (1, 3, 2, 0):
        nr, nc = r + DR[d], c + DC[d]
        if 0 <= nr < N and 0 <= nc < N:
            bit = nr * N + nc
            if visited & (1 << bit):
                continue
            nv = abs(board.grid[nr][nc])
            if nv == target_color or board.grid[nr][nc] == 0 or target_color == 0:
                new_target = target_color if target_color != 0 else nv
                visited |= (1 << bit)
                path.append((nr, nc))
                _dfs_collect_v3(board, nr, nc, new_target, max_len, hard_cap,
                                visited, path, collected, deadline)
                path.pop()
                visited &= ~(1 << bit)
                if len(collected) >= hard_cap:
                    return


def _greedy_rollout_v3(board: Board, depth: int) -> int:
    """
    Deterministic greedy rollout (v3-style).
    At each step, pick the single best candidate, apply discount.
    Returns accumulated discounted score + mobility bonus.
    """
    total = 0
    discount = 100  # percentage
    state = board.copy()

    for d in range(depth):
        if state.is_deadlocked():
            return total - 9000 // (d + 1)
        paths = _collect_candidates_v3(state, limit=1, time_limit_ms=100)
        if not paths or len(paths[0]) < 2:
            return total - 9000 // (d + 1)
        total += score_path(state.grid, paths[0]) * discount // 100
        state = state.preview(paths[0])
        discount = discount * 86 // 100

    return total + _mobility(state) // 5


def _greedy_beam_rollout_v2(
    board: Board,
    depth: int,
    beam_width: int = 3,
    lookahead: int = 2,
    time_limit_ms: float = 300,
) -> int:
    """
    BEAM-ENHANCED greedy rollout with 2 layers of预选.
    
    Layer 1 (beam): at each step, evaluate top beam_width candidates
    Layer 2 (lookahead): for each beam candidate, look ahead lookahead 
                         more steps via greedy simulation before deciding
    
    Total lookahead = depth + lookahead effective steps.
    """
    total = 0
    discount = 100
    state = board.copy()
    deadline = time.time() + time_limit_ms / 1000.0

    for d in range(depth):
        if time.time() > deadline:
            break
        if state.is_deadlocked():
            return total - 9000 // (d + 1)

        # Layer 1: get top beam_width candidates
        paths = _collect_candidates_v3(state, limit=beam_width, time_limit_ms=60)
        if not paths or len(paths[0]) < 2:
            return total - 9000 // (d + 1)

        best_gain = -1e9
        best_future = None
        best_score = 0

        for bp in paths[:beam_width]:
            bs = score_path(state.grid, bp)
            fut = state.preview(bp)
            if fut.is_deadlocked():
                gain = bs * discount // 100 - 2000
            elif lookahead <= 1:
                gain = bs * discount // 100 + _mobility(fut) // 4
            else:
                # Layer 2: look ahead `lookahead` more deterministic steps
                future_discount = discount * 86 // 100
                future_val = 0
                sim_state = fut
                sim_discount = future_discount
                for la in range(lookahead):
                    if sim_state.is_deadlocked():
                        future_val -= 3000 // (la + 1)
                        break
                    la_paths = _collect_candidates_v3(sim_state, limit=1, time_limit_ms=40)
                    if not la_paths or len(la_paths[0]) < 2:
                        future_val -= 3000 // (la + 1)
                        break
                    la_score = score_path(sim_state.grid, la_paths[0])
                    future_val += la_score * sim_discount // 100
                    sim_state = sim_state.preview(la_paths[0])
                    sim_discount = sim_discount * 86 // 100
                future_val += _mobility(sim_state) // 5
                gain = bs * discount // 100 + future_val * 70 // 100

            if gain > best_gain:
                best_gain = gain
                best_future = fut
                best_score = bs

        if best_future is None:
            return total - 9000 // (d + 1)

        total += best_score * discount // 100
        state = best_future
        discount = discount * 86 // 100

    return total + _mobility(state) // 5


def strategy_v3_beam_rollout(
    board: Board,
    cand_limit: int = 600,
    root_take: int = 80,
    rollout_depth: int = 6,
    rollout_beam: int = 3,
    rollout_lookahead: int = 2,
    time_limit_ms: float = 12000,
) -> List[Tuple[int, int]]:
    """
    V3 + BEAM ROLLOUT: 大池子 + 每步beam预选 + 前瞻.
    
    Layer 1: 600+ candidates via candidate_value
    Layer 2: beam_width=3 at each rollout step
    Layer 3: lookahead=2 steps ahead when evaluating beam candidates
    
    Effective lookahead = rollout_depth + lookahead = 8 steps.
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    cands = _collect_candidates_v3(
        board, limit=cand_limit, time_limit_ms=time_limit_ms * 0.20
    )

    if not cands or len(cands[0]) < 2:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    root_take = min(root_take, len(cands))

    best_val = -10**9
    best_path = cands[0]

    for i in range(root_take):
        if time.time() > deadline:
            break
        path = cands[i]
        imm = score_path(board.grid, path)
        future = board.preview(path)

        total = imm * 1000

        if future.is_deadlocked():
            total -= 4000000
        else:
            rollout = _greedy_beam_rollout_v2(
                future,
                depth=rollout_depth,
                beam_width=rollout_beam,
                lookahead=rollout_lookahead,
                time_limit_ms=400,
            )
            total += rollout * 790 + _mobility(future) * 7

        if total > best_val:
            best_val = total
            best_path = path

    return best_path


STRATEGIES["v3_beam"] = strategy_v3_beam_rollout


def strategy_v3_inspired(
    board: Board,
    time_limit_ms: float = 2500,
) -> List[Tuple[int, int]]:
    """
    V3-inspired strategy: large candidate pool + greedy rollout.
    
    Pipeline:
    1. Collect 300-450 candidates sorted by candidate_value
    2. For top root_take candidates, do greedy_rollout(4-5 steps)
    3. Evaluate: imm*1000 + greedy_rollout*790 + mobility*7
    4. Hard deadlock penalty: -4000000
    
    Root_take adapts per level like v3:
    - L5: 70, L3-4: 58, L1-2: 44
    """
    limit = 350 if board.level >= 5 else 250
    root_take = 50 if board.level >= 5 else (40 if board.level >= 3 else 30)
    depth = 5 if board.level >= 4 else 4

    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    cands = _collect_candidates_v3(board, limit=limit, time_limit_ms=time_limit_ms * 0.35)

    if not cands or len(cands[0]) < 2:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    root_take = min(root_take, len(cands))

    best_val = -10**9
    best_path = cands[0]

    for i in range(root_take):
        if time.time() > deadline:
            break
        path = cands[i]
        imm = score_path(board.grid, path)
        future = board.preview(path)

        total = imm * 1000

        if future.is_deadlocked():
            total -= 4000000
        else:
            rollout = _greedy_rollout_v3(future, depth)
            total += rollout * 790 + _mobility(future) * 7

        if total > best_val:
            best_val = total
            best_path = path

    return best_path


STRATEGIES["v3_inspired"] = strategy_v3_inspired


# ============================================================
# V3-MERGED: large pool + beam rollout + Poisson depth
# ============================================================

def _greedy_beam_rollout(
    board: Board,
    depth_mean: float = 6.0,
    max_depth: int = 10,
    beam_width: int = 2,
    time_limit_ms: float = 200,
) -> int:
    """
    Beam-based rollout with Poisson-distributed depth.
    At each step, try top beam_width candidates, pick the best branch.
    Depth ~ Poisson(depth_mean), capped at max_depth.
    """
    depth = poisson_sample(depth_mean)
    depth = min(depth, max_depth)
    depth = max(depth, 2)

    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    total = 0
    discount = 100
    state = board.copy()

    for d in range(depth):
        if time.time() > deadline:
            break
        if state.is_deadlocked():
            return total - 9000 // (d + 1)

        # Get top beam_width candidates on current rollout state
        paths = _collect_candidates_v3(state, limit=beam_width, time_limit_ms=80)
        if not paths or len(paths[0]) < 2:
            return total - 9000 // (d + 1)

        # Try each beam candidate, pick the one with best mobility after
        best_gain = -1e9
        best_future = None
        best_score = 0

        for bp in paths[:beam_width]:
            bs = score_path(state.grid, bp)
            fut = state.preview(bp)
            if fut.is_deadlocked():
                gain = bs * discount // 100 - 5000
            else:
                gain = bs * discount // 100 + _mobility(fut) // 4
            if gain > best_gain:
                best_gain = gain
                best_future = fut
                best_score = bs

        if best_future is None:
            return total - 9000 // (d + 1)

        total += best_score * discount // 100
        state = best_future
        discount = discount * 86 // 100

    return total + _mobility(state) // 5


def strategy_v3_merged(
    board: Board,
    cand_limit: int = 800,
    root_take: int = 100,
    rollout_depth: int = 7,
    time_limit_ms: float = 10000,
) -> List[Tuple[int, int]]:
    """
    V3 scaled up: bigger pool, deeper rollout, more root candidates.
    
    - Large candidate pool (800-1200)
    - Deep deterministic greedy rollout (7 steps, was 4-5)
    - Large root_take (100, was 30-50)
    - Poisson NOT used (greedy rollout > beam rollout)
    """
    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    cands = _collect_candidates_v3(
        board, limit=cand_limit, time_limit_ms=time_limit_ms * 0.20
    )

    if not cands or len(cands[0]) < 2:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    root_take = min(root_take, len(cands))

    best_val = -10**9
    best_path = cands[0]

    for i in range(root_take):
        if time.time() > deadline:
            break
        path = cands[i]
        imm = score_path(board.grid, path)
        future = board.preview(path)

        total = imm * 1000

        if future.is_deadlocked():
            total -= 4000000
        else:
            rollout = _greedy_rollout_v3(future, rollout_depth)
            total += rollout * 790 + _mobility(future) * 7

        if total > best_val:
            best_val = total
            best_path = path

    return best_path


def make_seeded_v3_merged(
    base_seed: int = 42,
    cand_limit: int = 800,
    root_take: int = 100,
    rollout_depth: int = 7,
    time_limit_ms: float = 12000,
) -> Callable[[Board], List[Tuple[int, int]]]:
    """Seeded v3_merged for grid search."""
    step_counter = [0]
    def fn(board: Board) -> List[Tuple[int, int]]:
        bh = 0
        for r in range(board.N):
            for c in range(board.N):
                bh = bh * 31 + board.grid[r][c]
        step_counter[0] += 1
        random.seed(base_seed * 100000 + step_counter[0] * 1000 + abs(bh) % 1000)
        return strategy_v3_merged(
            board,
            cand_limit=cand_limit,
            root_take=root_take,
            rollout_depth=rollout_depth,
            time_limit_ms=time_limit_ms,
        )
    return fn


STRATEGIES["v3_merged"] = strategy_v3_merged


# ============================================================
# Seeded strategy factory: makes rollouts reproducible
# ============================================================


def make_seeded_beam(
    base_seed: int = 42,
    beam_width: int = 2,
    rollout_n: int = 5,
    rollout_depth_mean: float = 3.5,
    time_limit_ms: float = 2500,
) -> Callable[[Board], List[Tuple[int, int]]]:
    """
    Factory: creates a beam_2det_1rnd variant with FIXED random seed.

    Seeds random with (base_seed * 10000 + hash(board_state))
    before each call, making the entire game trace deterministic
    for a given base_seed. Different base_seeds explore different
    rollout paths → we can grid-search for the best one.
    """
    step_counter = [0]  # mutable counter

    def seeded_strategy(board: Board) -> List[Tuple[int, int]]:
        # Hash board state for determinism within a seed
        board_hash = 0
        for r in range(board.N):
            for c in range(board.N):
                board_hash = board_hash * 31 + board.grid[r][c]
        step_counter[0] += 1
        # Fix seed: base_seed ⊕ step ⊕ board_state
        random.seed(
            base_seed * 100000 + step_counter[0] * 1000 + abs(board_hash) % 1000
        )
        return strategy_2step_beam_rollout(
            board,
            pool_size=10,
            beam_width=beam_width,
            rollout_n=rollout_n,
            rollout_depth_mean=rollout_depth_mean,
            time_limit_ms=time_limit_ms,
        )

    return seeded_strategy


def make_seeded_lookahead(
    base_seed: int = 42,
    time_limit_ms: float = 1500,
) -> Callable[[Board], List[Tuple[int, int]]]:
    """Seeded version of exhaustive_lookahead."""
    step_counter = [0]

    def seeded_strategy(board: Board) -> List[Tuple[int, int]]:
        step_counter[0] += 1
        random.seed(base_seed * 100000 + step_counter[0])
        return strategy_deterministic_lookahead(
            board, pool_size=10, time_limit_ms=time_limit_ms
        )

    return seeded_strategy


# ============================================================
# Grid search for optimal seed + Poisson params
# ============================================================


def grid_search_seeds(
    game_seed: int = 114514,
    base_seeds: List[int] = None,
    beam_widths: List[int] = None,
    rollout_ns: List[int] = None,
    depth_means: List[float] = None,
    levels: List[int] = None,
    verbose: bool = True,
) -> Dict:
    """
    Grid search over random seeds and Poisson parameters.
    Returns the best configuration found.
    """
    if base_seeds is None:
        base_seeds = [42, 123, 456, 789, 1024, 2048, 4096, 7777]
    if beam_widths is None:
        beam_widths = [2]
    if rollout_ns is None:
        rollout_ns = [5, 8]
    if depth_means is None:
        depth_means = [3.0, 4.0, 5.0]
    if levels is None:
        levels = [4, 5]  # Default: only search bomb levels

    from engine import MT19937, init_board, GameLevel

    best_config = None
    best_score = -1
    total_combos = (
        len(base_seeds) * len(beam_widths) * len(rollout_ns) * len(depth_means)
    )
    combo_idx = 0

    level_configs = [(1, 10), (2, 10), (3, 10), (4, 10), (5, 12)]

    for base_seed in base_seeds:
        for bw in beam_widths:
            for rn in rollout_ns:
                for dm in depth_means:
                    combo_idx += 1
                    if verbose:
                        print(
                            f"\r[{combo_idx}/{total_combos}] "
                            f"seed={base_seed} bw={bw} rn={rn} dm={dm:.1f}",
                            end="",
                            flush=True,
                        )

                    # Run selected levels
                    total = 0
                    rng = MT19937(game_seed)
                    for lvl_num, N in level_configs:
                        if lvl_num not in levels:
                            # Skip non-target levels (just consume RNG)
                            for _ in range(N):
                                for __ in range(N):
                                    from engine import gen_block

                                    gen_block(rng, lvl_num)
                            for _ in range(N * 1000):
                                from engine import gen_block

                                gen_block(rng, lvl_num)
                            continue

                        board = init_board(rng, N, lvl_num, game_seed)
                        strategy_fn = make_seeded_beam(
                            base_seed=base_seed,
                            beam_width=bw,
                            rollout_n=rn,
                            rollout_depth_mean=dm,
                        )
                        game = GameLevel(board=board)
                        while not game.finished:
                            path = strategy_fn(game.board)
                            game.apply_path(path)
                        total += game.score

                    if total > best_score:
                        best_score = total
                        best_config = {
                            "base_seed": base_seed,
                            "beam_width": bw,
                            "rollout_n": rn,
                            "depth_mean": dm,
                            "score": total,
                            "levels_tested": levels,
                        }

    if verbose:
        print(f"\nBest: {best_config}")

    return best_config
