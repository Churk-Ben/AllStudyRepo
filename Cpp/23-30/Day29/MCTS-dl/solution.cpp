/**
 * V3-inspired solution: large candidate pool + greedy rollout.
 * Collects 400-600 candidates per step, evaluates with 4-5 step
 * deterministic greedy rollout + mobility heuristic.
 */
#if __cplusplus < 201700L
#error "C++17 required"
#endif

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

struct Cell {
  int value = 1;
  int color() const { return std::abs(value); }
  bool is_bomb() const { return value < 0; }
  bool is_wildcard() const { return value == 0; }
};

struct Board {
  int N = 0;
  int level = 1;
  std::vector<std::vector<Cell>> grid;
  std::vector<std::vector<int>> drop_queue;
  std::vector<int> queue_ptr;

  explicit Board(int n = 0) : N(n), grid(n, std::vector<Cell>(n)) {}

  Cell &at(int r, int c) { return grid[r][c]; }
  const Cell &at(int r, int c) const { return grid[r][c]; }
  bool in_bounds(int r, int c) const {
    return r >= 0 && r < N && c >= 0 && c < N;
  }

  Board preview(const std::vector<std::pair<int, int>> &path) const {
    Board next_b = *this;
    if (path.size() < 2)
      return next_b;

    std::vector<std::vector<bool>> in_path(N, std::vector<bool>(N, false));
    for (auto p : path)
      in_path[p.first][p.second] = true;
    auto to_remove = in_path;

    if (level >= 4) {
      for (auto [r, c] : path) {
        if (!at(r, c).is_bomb())
          continue;
        for (int dr = -1; dr <= 1; ++dr)
          for (int dc = -1; dc <= 1; ++dc) {
            int nr = r + dr, nc = c + dc;
            if (in_bounds(nr, nc) && !in_path[nr][nc])
              to_remove[nr][nc] = true;
          }
      }
    }

    for (int c = 0; c < N; ++c) {
      std::vector<Cell> remaining;
      for (int r = 0; r < N; ++r)
        if (!to_remove[r][c])
          remaining.push_back(at(r, c));
      int empty = N - (int)remaining.size();
      for (int i = 0; i < empty; ++i)
        next_b.at(i, c).value = next_b.drop_queue[c][next_b.queue_ptr[c]++];
      for (int i = 0; i < (int)remaining.size(); ++i)
        next_b.at(empty + i, c) = remaining[i];
    }
    return next_b;
  }

  bool is_deadlocked() const {
    for (int r = 0; r < N; ++r)
      for (int c = 0; c < N; ++c) {
        int ac = at(r, c).color();
        if (c + 1 < N && (ac == at(r, c + 1).color() || ac == 0 ||
                          at(r, c + 1).color() == 0))
          return false;
        if (r + 1 < N && (ac == at(r + 1, c).color() || ac == 0 ||
                          at(r + 1, c).color() == 0))
          return false;
      }
    return true;
  }
};

class GameController {
  Board _board;
  int _level = 0, _step = 0, _score = 0;
  bool _done = false;
  std::string _pending_line;
  std::vector<std::pair<int, int>> _last_path;

  static int try_parse_level(const std::string &line, int &level, int &seed) {
    int lv, sd, N, steps;
    if (std::sscanf(line.c_str(), "LEVEL %d SEED %d SIZE %d STEPS %d", &lv, &sd,
                    &N, &steps) == 4) {
      level = lv;
      seed = sd;
      return N;
    }
    return 0;
  }

  static bool try_parse_step(const std::string &line, int &step, int &score,
                             bool &valid) {
    char buf[16] = {};
    if (std::sscanf(line.c_str(), "STEP %d SCORE %d %15s", &step, &score,
                    buf) >= 3) {
      valid = (std::string(buf) == "VALID");
      return true;
    }
    return false;
  }

  static int gen_block(std::mt19937 &rng, int level) {
    if (level <= 2)
      return (rng() % 5) + 1;
    if (level == 3)
      return ((rng() % 100) < 15) ? 0 : (rng() % 5) + 1;
    if (level == 4) {
      int c = (rng() % 5) + 1;
      return ((rng() % 100) < 10) ? -c : c;
    }
    if ((rng() % 100) < 15)
      return 0;
    int base = (rng() % 5) + 1;
    return ((rng() % 100) < 10) ? -base : base;
  }

  static void init_queues(Board &b, int seed, int N, int level) {
    b.level = level;
    std::mt19937 rng(seed);
    b.drop_queue.assign(N, std::vector<int>(1000));
    b.queue_ptr.assign(N, 0);
    for (int c = 0; c < N; ++c)
      for (int i = 0; i < 1000; ++i)
        b.drop_queue[c][i] = gen_block(rng, level);
  }

  bool read_line(std::string &line) {
    if (!_pending_line.empty()) {
      line = std::move(_pending_line);
      _pending_line.clear();
      return true;
    }
    return (bool)std::getline(std::cin, line);
  }

  Board read_board(int N) {
    Board board(N);
    for (int row = 0; row < N; ++row) {
      std::string line;
      read_line(line);
      std::istringstream ls(line);
      for (int c = 0; c < N; ++c)
        ls >> board.at(row, c).value;
    }
    return board;
  }

  void drain_trailing() {
    std::string line;
    while (std::cin.rdbuf()->in_avail() > 0) {
      if (!read_line(line))
        break;
      if (line.empty() || line.find("LEVEL_END") != std::string::npos)
        continue;
      if (line.find("FINAL_SCORE") != std::string::npos) {
        _done = true;
        continue;
      }
      _pending_line = std::move(line);
      break;
    }
  }

public:
  const Board &board() const { return _board; }
  int level() const { return _level; }
  int step() const { return _step; }
  int score() const { return _score; }
  bool done() const { return _done; }

  bool update() {
    std::string first_line;
    while (true) {
      if (!read_line(first_line)) {
        _done = true;
        return false;
      }
      if (!first_line.empty())
        break;
    }
    if (first_line.find("LEVEL_END") != std::string::npos ||
        first_line.find("FINAL_SCORE") != std::string::npos) {
      _done = true;
      return false;
    }

    int seed;
    int new_N = try_parse_level(first_line, _level, seed);
    if (new_N > 0) {
      _board = read_board(new_N);
      init_queues(_board, seed, new_N, _level);
      _step = 0;
      _score = 0;
      drain_trailing();
      return true;
    }

    int step, score;
    bool valid;
    if (try_parse_step(first_line, step, score, valid)) {
      _step = step;
      _score = score;
      Board predicted =
          (valid && !_last_path.empty()) ? _board.preview(_last_path) : _board;
      Board new_board = read_board(_board.N);
      new_board.level = _level;
      new_board.drop_queue = std::move(predicted.drop_queue);
      new_board.queue_ptr = std::move(predicted.queue_ptr);
      _board = std::move(new_board);
      _last_path.clear();
      drain_trailing();
      if (!_pending_line.empty()) {
        int nl, ns;
        int nn = try_parse_level(_pending_line, nl, ns);
        if (nn > 0) {
          _level = nl;
          _pending_line.clear();
          Board nb = read_board(nn);
          init_queues(nb, ns, nn, nl);
          _board = std::move(nb);
          _step = 0;
          _score = 0;
          drain_trailing();
        }
      }
      return true;
    }
    _done = true;
    return false;
  }

  void respond(const std::vector<std::pair<int, int>> &path) {
    _last_path = path;
    std::cout << path.size();
    for (auto [r, c] : path)
      std::cout << ' ' << r << ' ' << c;
    std::cout << '\n';
    std::cout.flush();
  }
};

// ============================================================
// Level-adaptive v3 path finder
// ============================================================

constexpr int DR[] = {-1, 1, 0, 0};
constexpr int DC[] = {0, 0, -1, 1};

int path_score_k(int k) {
  double t = std::sqrt((double)k) - 1.0;
  return 10 * k + 18 * (int)(t * t);
}

int path_score(const Board &board,
               const std::vector<std::pair<int, int>> &path) {
  int k = (int)path.size();
  int s = path_score_k(k);
  if (board.level < 4)
    return s;

  int N = board.N;
  bool in_path[12][12] = {};
  bool exploded[12][12] = {};
  for (auto [r, c] : path)
    in_path[r][c] = true;

  for (auto [r, c] : path) {
    if (!board.at(r, c).is_bomb())
      continue;
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        int nr = r + dr, nc = c + dc;
        if ((unsigned)nr < (unsigned)N && (unsigned)nc < (unsigned)N &&
            !in_path[nr][nc] && !exploded[nr][nc]) {
          exploded[nr][nc] = true;
          s += 10;
        }
      }
    }
  }
  return s;
}

namespace v3ai {

using Path = std::vector<std::pair<int, int>>;
using Clock = std::chrono::steady_clock;

struct Candidate {
  Path path;
  int score = 0;
  int value = 0;
};

int mobility(const Board &board) {
  int links = 0, wild = 0, bombs = 0;
  for (int r = 0; r < board.N; ++r) {
    for (int c = 0; c < board.N; ++c) {
      if (board.at(r, c).is_wildcard())
        ++wild;
      if (board.at(r, c).is_bomb())
        ++bombs;
      if (c + 1 < board.N) {
        int a = board.at(r, c).color();
        int b = board.at(r, c + 1).color();
        if (a == b || a == 0 || b == 0)
          ++links;
      }
      if (r + 1 < board.N) {
        int a = board.at(r, c).color();
        int b = board.at(r + 1, c).color();
        if (a == b || a == 0 || b == 0)
          ++links;
      }
    }
  }
  return links * 2 + wild * 8 + (board.level >= 4 ? bombs * 10 : 0);
}

int candidate_value(const Board &board, const Path &path) {
  int low = 0, bombs = 0, wild = 0;
  for (auto [r, c] : path) {
    if (r >= board.N / 2)
      ++low;
    if (board.at(r, c).is_bomb())
      ++bombs;
    if (board.at(r, c).is_wildcard())
      ++wild;
  }
  return path_score(board, path) * 10 + low * 4 + bombs * 45 + wild * 8 +
         (int)path.size();
}

void dfs_candidates(const Board &board, int r, int c, int target_color,
                    int max_len, int hard_cap, Path &cur, uint8_t used[12][12],
                    std::vector<Candidate> &out, bool use_deadline,
                    Clock::time_point deadline, bool &stop) {
  if (stop)
    return;
  if (use_deadline && Clock::now() > deadline) {
    stop = true;
    return;
  }

  cur.emplace_back(r, c);
  used[r][c] = 1;

  if (cur.size() >= 2) {
    Candidate cand;
    cand.path = cur;
    cand.score = path_score(board, cur);
    cand.value = candidate_value(board, cur);
    out.push_back(std::move(cand));
  }

  if ((int)out.size() >= hard_cap || (int)cur.size() >= max_len) {
    if ((int)out.size() >= hard_cap)
      stop = true;
    used[r][c] = 0;
    cur.pop_back();
    return;
  }

  const int order[4] = {1, 3, 2, 0};
  for (int oi = 0; oi < 4; ++oi) {
    int d = order[oi];
    int nr = r + DR[d], nc = c + DC[d];
    if (!board.in_bounds(nr, nc) || used[nr][nc])
      continue;
    int cc = board.at(nr, nc).color();
    if (cc == target_color || cc == 0 || target_color == 0) {
      int nt = (target_color != 0) ? target_color : cc;
      dfs_candidates(board, nr, nc, nt, max_len, hard_cap, cur, used, out,
                     use_deadline, deadline, stop);
      if (stop)
        break;
    }
  }

  used[r][c] = 0;
  cur.pop_back();
}

std::vector<Candidate> find_candidates(const Board &board, int limit,
                                       double time_limit_ms = -1.0) {
  std::vector<Candidate> all;
  int max_len = (board.level >= 5) ? 34 : 30;
  int hard_cap = std::max(1000, limit * 5);
  bool use_deadline = time_limit_ms > 0.0;
  auto deadline = Clock::now() + std::chrono::microseconds(
                                     (long long)(time_limit_ms * 1000.0));
  bool stop = false;

  for (int r = 0; r < board.N; ++r) {
    for (int c = 0; c < board.N; ++c) {
      if (stop || (int)all.size() >= hard_cap)
        goto done;
      Path cur;
      uint8_t used[12][12] = {};
      dfs_candidates(board, r, c, board.at(r, c).color(), max_len, hard_cap,
                     cur, used, all, use_deadline, deadline, stop);
    }
  }

done:
  // Python keeps DFS insertion order for equal candidate_value because
  // list.sort is stable.
  std::stable_sort(
      all.begin(), all.end(),
      [](const Candidate &a, const Candidate &b) { return a.value > b.value; });
  if ((int)all.size() > limit)
    all.resize(limit);
  return all;
}

int greedy_rollout(Board board, int depth) {
  int total = 0;
  int discount = 100;
  for (int d = 0; d < depth; ++d) {
    if (board.is_deadlocked())
      return total - 9000 / (d + 1);
    auto paths = find_candidates(board, 1, 100.0);
    if (paths.empty())
      return total - 9000 / (d + 1);
    total += paths[0].score * discount / 100;
    board = board.preview(paths[0].path);
    discount = discount * 86 / 100;
  }
  return total + mobility(board) / 5;
}

int greedy_beam_rollout_v2(Board board, int depth, int beam_width,
                           int lookahead, double time_limit_ms) {
  int total = 0;
  int discount = 100;
  auto deadline = Clock::now() + std::chrono::microseconds(
                                     (long long)(time_limit_ms * 1000.0));

  for (int d = 0; d < depth; ++d) {
    if (Clock::now() > deadline)
      break;
    if (board.is_deadlocked())
      return total - 9000 / (d + 1);

    auto paths = find_candidates(board, beam_width, 60.0);
    if (paths.empty())
      return total - 9000 / (d + 1);

    int best_gain = -1000000000;
    Board best_future;
    int best_score = 0;
    bool has_best = false;

    for (int i = 0; i < (int)paths.size() && i < beam_width; ++i) {
      int base_score = paths[i].score;
      Board future = board.preview(paths[i].path);
      int gain = 0;

      if (future.is_deadlocked()) {
        gain = base_score * discount / 100 - 2000;
      } else if (lookahead <= 1) {
        gain = base_score * discount / 100 + mobility(future) / 4;
      } else {
        int future_discount = discount * 86 / 100;
        int future_val = 0;
        Board sim_state = future;
        int sim_discount = future_discount;

        for (int la = 0; la < lookahead; ++la) {
          if (Clock::now() > deadline)
            break;
          if (sim_state.is_deadlocked()) {
            future_val -= 3000 / (la + 1);
            break;
          }
          auto la_paths = find_candidates(sim_state, 1, 40.0);
          if (la_paths.empty()) {
            future_val -= 3000 / (la + 1);
            break;
          }
          future_val += la_paths[0].score * sim_discount / 100;
          sim_state = sim_state.preview(la_paths[0].path);
          sim_discount = sim_discount * 86 / 100;
        }

        future_val += mobility(sim_state) / 5;
        gain = base_score * discount / 100 + future_val * 70 / 100;
      }

      if (!has_best || gain > best_gain) {
        best_gain = gain;
        best_future = future;
        best_score = base_score;
        has_best = true;
      }
    }

    if (!has_best)
      return total - 9000 / (d + 1);

    total += best_score * discount / 100;
    board = best_future;
    discount = discount * 86 / 100;
  }

  return total + mobility(board) / 5;
}

Path fallback_pair(const Board &board) {
  for (int r = 0; r < board.N; ++r) {
    for (int c = 0; c < board.N; ++c) {
      int a = board.at(r, c).color();
      if (c + 1 < board.N) {
        int b = board.at(r, c + 1).color();
        if (a == b || a == 0 || b == 0)
          return {{r, c}, {r, c + 1}};
      }
      if (r + 1 < board.N) {
        int b = board.at(r + 1, c).color();
        if (a == b || a == 0 || b == 0)
          return {{r, c}, {r + 1, c}};
      }
    }
  }
  return {{0, 0}, {0, 1}};
}

Path strategy_v3_beam_rollout(const Board &board, int cand_limit, int root_take,
                              int rollout_depth, int rollout_beam,
                              int rollout_lookahead, double time_limit_ms) {
  auto deadline = Clock::now() + std::chrono::microseconds(
                                     (long long)(time_limit_ms * 1000.0));
  auto cands = find_candidates(board, cand_limit, time_limit_ms * 0.20);
  if (cands.empty())
    return fallback_pair(board);

  root_take = std::min(root_take, (int)cands.size());
  int best_val = -1000000000;
  Path best_path = cands[0].path;

  for (int i = 0; i < root_take; ++i) {
    if (Clock::now() > deadline)
      break;
    Board future = board.preview(cands[i].path);
    int total = cands[i].score * 1000;

    if (future.is_deadlocked()) {
      total -= 4000000;
    } else {
      int rollout = greedy_beam_rollout_v2(future, rollout_depth, rollout_beam,
                                           rollout_lookahead, 400.0);
      total += rollout * 790 + mobility(future) * 7;
    }

    if (total > best_val) {
      best_val = total;
      best_path = cands[i].path;
    }
  }

  return best_path;
}

Path strategy_v3_merged(const Board &board, int cand_limit, int root_take,
                        int rollout_depth, double time_limit_ms) {
  auto deadline = Clock::now() + std::chrono::microseconds(
                                     (long long)(time_limit_ms * 1000.0));
  auto cands = find_candidates(board, cand_limit, time_limit_ms * 0.20);
  if (cands.empty())
    return fallback_pair(board);

  root_take = std::min(root_take, (int)cands.size());
  int best_val = -1000000000;
  Path best_path = cands[0].path;

  for (int i = 0; i < root_take; ++i) {
    if (Clock::now() > deadline)
      break;
    Board future = board.preview(cands[i].path);
    int total = cands[i].score * 1000;

    if (future.is_deadlocked()) {
      total -= 4000000;
    } else {
      int rollout = greedy_rollout(future, rollout_depth);
      total += rollout * 790 + mobility(future) * 7;
    }

    if (total > best_val) {
      best_val = total;
      best_path = cands[i].path;
    }
  }

  return best_path;
}

} // namespace v3ai

std::vector<std::pair<int, int>> find_best_path(const Board &board) {
  using namespace v3ai;
  if (board.level <= 4) {
    return strategy_v3_beam_rollout(board, 600, 80, 5, 3, 2, 2000.0);
  }
  return strategy_v3_merged(board, 1000, 120, 8, 2000.0);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  GameController ctl;
  while (ctl.update()) {
    auto path = find_best_path(ctl.board());
    ctl.respond(path);
  }
  return 0;
}
