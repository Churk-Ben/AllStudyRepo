"""
Training framework and evaluator for Block Sequence Grand Master.
- Evaluates all strategies on the fixed-seed game
- Runs MCTS training to find optimal paths
- Generates comparison reports
"""

from __future__ import annotations
import time
import json
import os
import sys
from typing import List, Tuple, Dict, Callable
from dataclasses import dataclass, field

from engine import (
    Board,
    GameLevel,
    MT19937,
    gen_block,
    init_board,
    run_level,
    run_full_game,
    validate_path,
    score_path,
)
from solver import (
    STRATEGIES,
    find_paths_iddfs,
    find_longest_path_dfs,
    score_path as solver_score_path,
)

# ============================================================
# Evaluation runner
# ============================================================


@dataclass
class LevelResult:
    level: int
    N: int
    score: int
    steps: int
    finish_reason: str


@dataclass
class GameResult:
    strategy_name: str
    levels: List[LevelResult]
    total_score: int
    total_time_ms: float


def evaluate_strategy(
    strategy_name: str, strategy_fn: Callable, seed: int = 114514, verbose: bool = True
) -> GameResult:
    """Run the full 5-level game with a given strategy."""
    rng = MT19937(seed)
    levels = []
    total_time = 0.0

    level_configs = [(1, 10), (2, 10), (3, 10), (4, 10), (5, 12)]

    for level_num, N in level_configs:
        if verbose:
            print(f"  Level {level_num} ({N}x{N})...", end=" ", flush=True)

        board = init_board(rng, N, level_num, seed)
        game = GameLevel(board=board)

        t0 = time.time()
        while not game.finished:
            path = strategy_fn(game.board)
            game.apply_path(path)
        elapsed = (time.time() - t0) * 1000
        total_time += elapsed

        levels.append(
            LevelResult(
                level=level_num,
                N=N,
                score=game.score,
                steps=game.step,
                finish_reason=game.finish_reason,
            )
        )

        if verbose:
            print(f"Score={game.score}, Steps={game.step}, Reason={game.finish_reason}")

    return GameResult(
        strategy_name=strategy_name,
        levels=levels,
        total_score=sum(l.score for l in levels),
        total_time_ms=total_time,
    )


def compare_strategies(
    strategies: List[str] = None, seed: int = 114514, verbose: bool = True
):
    """Compare multiple strategies and print results."""
    if strategies is None:
        strategies = list(STRATEGIES.keys())

    print("=" * 80)
    print(f"STRATEGY COMPARISON (seed={seed})")
    print("=" * 80)

    results = []
    for name in strategies:
        if name not in STRATEGIES:
            print(f"Unknown strategy: {name}")
            continue
        print(f"\n[{name}]")
        result = evaluate_strategy(name, STRATEGIES[name], seed=seed, verbose=verbose)
        results.append(result)
        print(f"  TOTAL: {result.total_score} | Time: {result.total_time_ms:.0f}ms")

    # Summary table
    print("\n" + "=" * 80)
    print("SUMMARY")
    print("=" * 80)
    print(
        f"{'Strategy':<25} {'L1':>6} {'L2':>6} {'L3':>6} {'L4':>6} {'L5':>6} {'Total':>8} {'Time':>8}"
    )
    print("-" * 80)
    for r in sorted(results, key=lambda x: -x.total_score):
        scores = [str(l.score) for l in r.levels]
        print(
            f"{r.strategy_name:<25} {scores[0]:>6} {scores[1]:>6} {scores[2]:>6} {scores[3]:>6} {scores[4]:>6} {r.total_score:>8} {r.total_time_ms:>7.0f}ms"
        )

    return results


# ============================================================
# MCTS Deep Training (offline, for pre-computing decision tree)
# ============================================================


def mcts_deep_search(
    board: Board, iterations: int = 500, depth: int = 4, time_limit_ms: float = 2000
) -> List[Tuple[int, int]]:
    """
    Deep MCTS search with more iterations for offline training.
    Explores deeper and wider than the online version.
    """
    from solver import MCTSNode, _rollout

    start_time = time.time()
    deadline = start_time + time_limit_ms / 1000.0

    root = MCTSNode(board)
    candidates = find_paths_iddfs(board, time_limit_ms=300, max_paths=20)
    root.untried_paths = list(candidates) if candidates else []

    if not root.untried_paths:
        pairs = board.find_adjacent_pairs()
        if pairs:
            r1, c1, r2, c2 = pairs[0]
            return [(r1, c1), (r2, c2)]
        return [(0, 0), (0, 1)]

    iter_count = 0
    while iter_count < iterations and time.time() < deadline:
        # Selection with tree policy
        node = root
        while node.children and node.is_fully_expanded():
            best_child = max(node.children, key=lambda c: c.ucb1(2.0))
            node = best_child

        # Expansion
        if not node.is_fully_expanded() and node.untried_paths:
            path = node.untried_paths.pop()
            is_valid, _ = validate_path(node.board.grid, path)
            if not is_valid:
                continue
            next_board = node.board.preview(path)
            child = MCTSNode(next_board, path, node)
            node.children.append(child)
            node = child
        else:
            continue

        # Deep rollout
        rollout_score = _rollout(node.board, max_steps=20)

        # Backpropagation
        while node is not None:
            node.visits += 1
            node.total_score += rollout_score
            node = node.parent

        iter_count += 1

    if not root.children:
        return root.untried_paths[0] if root.untried_paths else [(0, 0), (0, 1)]

    # Select best child
    best = max(root.children, key=lambda c: c.visits)
    return best.path


def train_mcts_level(
    rng: MT19937,
    level_num: int,
    N: int,
    seed: int,
    train_iterations: int = 100,
    mcts_per_step: int = 500,
) -> Dict:
    """
    Train MCTS on a single level with many iterations.
    Returns the best game trace found.
    """
    print(f"\n  Training Level {level_num} ({N}x{N})...")

    board = init_board(rng, N, level_num, seed)
    game = GameLevel(board=board)

    trace = []  # List of paths taken
    step_scores = []

    while not game.finished:
        path = mcts_deep_search(
            game.board, iterations=mcts_per_step, depth=3, time_limit_ms=3000
        )
        valid, gained = game.apply_path(path)

        trace.append(
            {
                "step": game.step,
                "path": path,
                "score_gained": gained,
                "total_score": game.score,
                "valid": valid,
            }
        )
        if valid:
            step_scores.append(gained)

        if game.step % 10 == 0:
            print(f"    Step {game.step}: score={game.score}")

    result = {
        "level": level_num,
        "N": N,
        "final_score": game.score,
        "total_steps": game.step,
        "valid_steps": len(step_scores),
        "finish_reason": game.finish_reason,
        "trace": trace,
    }

    print(
        f"    Result: score={game.score}, steps={game.step}, reason={game.finish_reason}"
    )
    return result


def train_mcts_full_game(seed: int = 114514, mcts_per_step: int = 300) -> List[Dict]:
    """Train MCTS on the full 5-level game."""
    rng = MT19937(seed)
    results = []

    level_configs = [(1, 10), (2, 10), (3, 10), (4, 10), (5, 12)]

    for level_num, N in level_configs:
        result = train_mcts_level(rng, level_num, N, seed, mcts_per_step=mcts_per_step)
        results.append(result)

    total = sum(r["final_score"] for r in results)
    print(f"\n  MCTS Training Total Score: {total}")
    return results


# ============================================================
# Decision Tree Export (for C++ solution)
# ============================================================


def export_decision_tree(training_results: List[Dict], output_path: str):
    """
    Export the trained decision paths as a C++ header file.
    The C++ solution can replay these paths directly.
    """
    lines = []
    lines.append("// Auto-generated decision tree from MCTS training (seed=114514)")
    lines.append("// DO NOT EDIT MANUALLY")
    lines.append("")
    lines.append("#ifndef DECISION_TREE_H")
    lines.append("#define DECISION_TREE_H")
    lines.append("")
    lines.append("#include <vector>")
    lines.append("#include <utility>")
    lines.append("")
    lines.append("namespace DecisionTree {")
    lines.append("")

    for level_result in training_results:
        level = level_result["level"]
        trace = level_result["trace"]
        lines.append(
            f"// Level {level} - expected score: {level_result['final_score']}"
        )
        lines.append(
            f"inline std::vector<std::vector<std::pair<int,int>>> level{level}_paths = {{"
        )

        for step_data in trace:
            path = step_data["path"]
            path_str = ", ".join(f"{{{r},{c}}}" for r, c in path)
            lines.append(f"    {{ {path_str} }},")

        lines.append("};")
        lines.append("")

    lines.append("} // namespace DecisionTree")
    lines.append("")
    lines.append("#endif // DECISION_TREE_H")
    lines.append("")

    with open(output_path, "w") as f:
        f.write("\n".join(lines))
    print(f"Decision tree exported to {output_path}")


# ============================================================
# Interactive training (iterative improvement)
# ============================================================


def iterative_training(seed: int = 114514, rounds: int = 5, mcts_per_step: int = 200):
    """
    Iterative training: run multiple rounds, keep the best trace.
    Each round tries to beat the previous best score.
    """
    print("=" * 80)
    print(f"ITERATIVE MCTS TRAINING (seed={seed}, rounds={rounds})")
    print("=" * 80)

    best_results = None
    best_total = 0

    for round_num in range(1, rounds + 1):
        print(f"\n--- Round {round_num}/{rounds} ---")
        rng = MT19937(seed)
        results = []
        total = 0

        level_configs = [(1, 10), (2, 10), (3, 10), (4, 10), (5, 12)]

        for level_num, N in level_configs:
            board = init_board(rng, N, level_num, seed)
            game = GameLevel(board=board)
            trace = []

            while not game.finished:
                iter_count = mcts_per_step + (round_num - 1) * 50  # Increase per round
                path = mcts_deep_search(
                    game.board, iterations=iter_count, depth=3, time_limit_ms=4000
                )
                game.apply_path(path)
                trace.append(
                    {
                        "step": game.step,
                        "path": path,
                        "score_gained": score_path(game.board.grid, path)
                        if len(path) >= 2
                        else 0,
                        "total_score": game.score,
                    }
                )

            results.append(
                {
                    "level": level_num,
                    "N": N,
                    "final_score": game.score,
                    "total_steps": game.step,
                    "finish_reason": game.finish_reason,
                    "trace": trace,
                }
            )
            total += game.score
            print(
                f"  Level {level_num}: {game.score} ({game.step} steps, {game.finish_reason})"
            )

        print(f"  Round {round_num} Total: {total}")

        if total > best_total:
            best_total = total
            best_results = results
            print(f"  *** NEW BEST: {best_total} ***")

    print(f"\nBest total score after {rounds} rounds: {best_total}")
    return best_results


# ============================================================
# Main entry point
# ============================================================


def main():
    import argparse

    parser = argparse.ArgumentParser(
        description="Block Sequence Grand Master - Training & Evaluation"
    )
    parser.add_argument(
        "--mode",
        choices=["compare", "train", "iterative", "export"],
        default="compare",
        help="Mode: compare strategies, train MCTS, iterative training, or export tree",
    )
    parser.add_argument("--seed", type=int, default=114514, help="Random seed")
    parser.add_argument(
        "--strategies",
        nargs="*",
        default=None,
        help="Strategies to compare (default: all)",
    )
    parser.add_argument(
        "--rounds", type=int, default=3, help="Iterative training rounds"
    )
    parser.add_argument(
        "--mcts-iter", type=int, default=200, help="MCTS iterations per step"
    )
    parser.add_argument(
        "--output",
        type=str,
        default="decision_tree.h",
        help="Output path for decision tree",
    )
    args = parser.parse_args()

    if args.mode == "compare":
        compare_strategies(args.strategies, seed=args.seed)

    elif args.mode == "train":
        print("Training MCTS on full game...")
        results = train_mcts_full_game(seed=args.seed, mcts_per_step=args.mcts_iter)

        output_dir = os.path.dirname(os.path.abspath(__file__))
        with open(os.path.join(output_dir, "training_results.json"), "w") as f:
            json.dump(results, f, indent=2, default=str)
        print("Results saved to training_results.json")

    elif args.mode == "iterative":
        results = iterative_training(
            seed=args.seed, rounds=args.rounds, mcts_per_step=args.mcts_iter
        )

        output_dir = os.path.dirname(os.path.abspath(__file__))
        with open(os.path.join(output_dir, "best_training.json"), "w") as f:
            json.dump(results, f, indent=2, default=str)
        print("Best results saved to best_training.json")

        if results:
            export_decision_tree(results, args.output)

    elif args.mode == "export":
        output_dir = os.path.dirname(os.path.abspath(__file__))
        json_path = os.path.join(output_dir, "best_training.json")
        if os.path.exists(json_path):
            with open(json_path, "r") as f:
                results = json.load(f)
            export_decision_tree(results, args.output)
        else:
            print("No training results found. Run --mode train first.")


if __name__ == "__main__":
    main()
