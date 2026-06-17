#if __cplusplus < 201700L
#error "C++17 required"
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
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

    std::vector<std::vector<bool>> to_remove = in_path;

    if (level >= 4) {
      for (auto [r, c] : path) {
        if (!at(r, c).is_bomb())
          continue;
        for (int dr = -1; dr <= 1; ++dr) {
          for (int dc = -1; dc <= 1; ++dc) {
            int nr = r + dr, nc = c + dc;
            if (in_bounds(nr, nc) && !in_path[nr][nc]) {
              to_remove[nr][nc] = true;
            }
          }
        }
      }
    }

    for (int c = 0; c < N; ++c) {
      std::vector<Cell> remaining;
      remaining.reserve(N);
      for (int r = 0; r < N; ++r) {
        if (!to_remove[r][c])
          remaining.push_back(at(r, c));
      }
      int empty = N - (int)remaining.size();
      for (int i = 0; i < empty; ++i) {
        int val = next_b.drop_queue[c][next_b.queue_ptr[c]++];
        next_b.at(i, c).value = val;
      }
      for (int i = 0; i < (int)remaining.size(); ++i) {
        next_b.at(empty + i, c) = remaining[i];
      }
    }
    return next_b;
  }

  bool is_deadlocked() const {
    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
        int ac = at(r, c).color();
        if (c + 1 < N) {
          int ac2 = at(r, c + 1).color();
          if (ac == ac2 || ac == 0 || ac2 == 0)
            return false;
        }
        if (r + 1 < N) {
          int ac2 = at(r + 1, c).color();
          if (ac == ac2 || ac == 0 || ac2 == 0)
            return false;
        }
      }
    }
    return true;
  }
};

class GameController {
  Board _board;
  int _level = 0;
  int _step = 0;
  int _score = 0;
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
      int color = (rng() % 5) + 1;
      return ((rng() % 100) < 10) ? -color : color;
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
    for (int c = 0; c < N; ++c) {
      for (int i = 0; i < 1000; ++i)
        b.drop_queue[c][i] = gen_block(rng, level);
    }
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
      Board new_board = read_board(new_N);
      init_queues(new_board, seed, new_N, _level);
      _board = std::move(new_board);
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
        int next_level, next_seed;
        int next_N = try_parse_level(_pending_line, next_level, next_seed);
        if (next_N > 0) {
          _level = next_level;
          _pending_line.clear();
          Board nb = read_board(next_N);
          init_queues(nb, next_seed, next_N, next_level);
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

constexpr int DR[] = {-1, 1, 0, 0};
constexpr int DC[] = {0, 0, -1, 1};

int path_score(int k) {
  double t = std::sqrt(static_cast<double>(k)) - 1.0;
  return 10 * k + 18 * static_cast<int>(t * t);
}

int path_score(const Board &board,
               const std::vector<std::pair<int, int>> &path) {
  int k = static_cast<int>(path.size());
  int s = path_score(k);

  std::vector<std::vector<bool>> in_path(board.N,
                                         std::vector<bool>(board.N, false));
  for (const auto &p : path)
    in_path[p.first][p.second] = true;
  std::vector<std::vector<bool>> exploded(board.N,
                                          std::vector<bool>(board.N, false));

  for (const auto &p : path) {
    int r = p.first, c = p.second;
    if (!board.at(r, c).is_bomb())
      continue;
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        int nr = r + dr, nc = c + dc;
        if (board.in_bounds(nr, nc) && !in_path[nr][nc] && !exploded[nr][nc]) {
          exploded[nr][nc] = true;
          s += 10;
        }
      }
    }
  }
  return s;
}

static bool compatible_color(int a, int b) {
  return a == b || a == 0 || b == 0;
}

static bool usable_for_color(const Board &board, int r, int c, int color) {
  int x = board.at(r, c).color();
  return x == 0 || x == color;
}

static int id_of(const Board &board, int r, int c) { return r * board.N + c; }

static bool is_valid_path(const Board &board,
                          const std::vector<std::pair<int, int>> &path) {
  if (path.size() < 2)
    return false;
  std::vector<char> seen(board.N * board.N, 0);
  int fixed_color = 0;
  for (std::size_t i = 0; i < path.size(); ++i) {
    int r = path[i].first, c = path[i].second;
    if (!board.in_bounds(r, c))
      return false;
    int id = id_of(board, r, c);
    if (seen[id])
      return false;
    seen[id] = 1;
    if (i > 0) {
      int pr = path[i - 1].first, pc = path[i - 1].second;
      if (std::abs(pr - r) + std::abs(pc - c) != 1)
        return false;
    }
    int col = board.at(r, c).color();
    if (col != 0) {
      if (fixed_color == 0)
        fixed_color = col;
      else if (fixed_color != col)
        return false;
    }
  }
  return true;
}

static std::vector<std::pair<int, int>> fallback_path(const Board &board) {
  int N = board.N;
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      int a = board.at(r, c).color();
      if (c + 1 < N) {
        int b = board.at(r, c + 1).color();
        if (compatible_color(a, b))
          return {{r, c}, {r, c + 1}};
      }
      if (r + 1 < N) {
        int b = board.at(r + 1, c).color();
        if (compatible_color(a, b))
          return {{r, c}, {r + 1, c}};
      }
    }
  }
  return {{0, 0}, {0, std::min(1, N - 1)}};
}

struct Candidate {
  std::vector<std::pair<int, int>> path;
  int score = 0;
  double rank = 0;
};

static bool better_candidate(const Candidate &a, const Candidate &b) {
  if (std::fabs(a.rank - b.rank) > 1e-9)
    return a.rank > b.rank;
  if (a.score != b.score)
    return a.score > b.score;
  return a.path.size() > b.path.size();
}

static bool special_len(int k) {
  if (k <= 8)
    return true;
  int q = static_cast<int>(std::sqrt(static_cast<double>(k)) + 0.5);
  if (q * q == k)
    return true;
  if ((q + 1) * (q + 1) == k + 1 || q * q == k + 1)
    return true;
  if (k % 4 == 0)
    return true;
  return false;
}

static unsigned long long
hash_path_cells(const Board &board,
                const std::vector<std::pair<int, int>> &path) {
  std::vector<int> ids;
  ids.reserve(path.size());
  for (const auto &p : path)
    ids.push_back(id_of(board, p.first, p.second));
  std::sort(ids.begin(), ids.end());
  unsigned long long h = 1469598103934665603ULL;
  for (int id : ids) {
    h ^= static_cast<unsigned long long>(id + 1315423911U);
    h *= 1099511628211ULL;
  }
  h ^= static_cast<unsigned long long>(ids.size()) * 11995408973635179863ULL;
  return h;
}

static int onward_degree(const Board &board, int color, int r, int c,
                         const std::vector<char> &used) {
  int cnt = 0;
  for (int d = 0; d < 4; ++d) {
    int nr = r + DR[d], nc = c + DC[d];
    if (!board.in_bounds(nr, nc))
      continue;
    int id = id_of(board, nr, nc);
    if (!used[id] && usable_for_color(board, nr, nc, color))
      ++cnt;
  }
  return cnt;
}

static int local_bomb_gain(const Board &board, int r, int c,
                           const std::vector<char> &used) {
  if (!board.at(r, c).is_bomb())
    return 0;
  int gain = 0;
  for (int dr = -1; dr <= 1; ++dr) {
    for (int dc = -1; dc <= 1; ++dc) {
      int nr = r + dr, nc = c + dc;
      if (!board.in_bounds(nr, nc))
        continue;
      if (nr == r && nc == c)
        continue;
      int id = id_of(board, nr, nc);
      if (!used[id])
        ++gain;
    }
  }
  return gain;
}

static int pseudo_rand_key(int r, int c, int color, int mode, int len) {
  unsigned int x = static_cast<unsigned int>(r * 92837111u + c * 689287499u +
                                             color * 283923481u +
                                             mode * 97531u + len * 19260817u);
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return static_cast<int>(x & 0x7fffffff);
}

static int move_value(const Board &board, int color, int r, int c,
                      const std::vector<char> &used, int mode, int len) {
  int deg = onward_degree(board, color, r, c, used);
  int bg = local_bomb_gain(board, r, c, used);
  int is_bomb = board.at(r, c).is_bomb() ? 1 : 0;
  int is_wild = board.at(r, c).is_wildcard() ? 1 : 0;
  int center_bias =
      -std::abs(2 * c - (board.N - 1)) - std::abs(2 * r - (board.N - 1));
  int rnd = pseudo_rand_key(r, c, color, mode, len) % 97;

  switch (mode) {
  case 0:
    return -70 * deg + 130 * is_bomb + 28 * bg + 8 * is_wild + rnd;
  case 1:
    return 55 * deg + 100 * is_bomb + 22 * bg + 5 * is_wild + rnd;
  case 2:
    return 190 * is_bomb + 55 * bg - 18 * deg + 5 * board.N * r + rnd;
  case 3:
    return 30 * r + 25 * center_bias + 95 * is_bomb + 20 * bg + rnd;
  case 4:
    return 100 * is_wild + 85 * is_bomb + 24 * bg - 25 * deg + rnd;
  default:
    return rnd + 70 * is_bomb + 10 * bg;
  }
}

static double start_value(const Board &board, int color, int r, int c) {
  std::vector<char> empty_used(board.N * board.N, 0);
  int deg = onward_degree(board, color, r, c, empty_used);
  int bg = local_bomb_gain(board, r, c, empty_used);
  return 200.0 * (board.at(r, c).is_bomb() ? 1 : 0) + 35.0 * bg + 12.0 * deg +
         20.0 * (board.at(r, c).is_wildcard() ? 1 : 0) + 0.5 * r;
}

static void trim_candidates(std::vector<Candidate> &cands, int keep) {
  if (static_cast<int>(cands.size()) <= keep)
    return;
  std::nth_element(cands.begin(), cands.begin() + keep, cands.end(),
                   better_candidate);
  cands.resize(keep);
  std::sort(cands.begin(), cands.end(), better_candidate);
}

static std::vector<Candidate> generate_candidates(const Board &board, int limit,
                                                  bool fast) {
  std::vector<Candidate> cands;
  std::unordered_set<unsigned long long> seen;
  int N = board.N;
  int hard_keep = std::max(limit * (fast ? 5 : 8), limit + 20);

  auto add_candidate = [&](const std::vector<std::pair<int, int>> &path) {
    if (path.size() < 2)
      return;
    unsigned long long h = hash_path_cells(board, path);
    if (seen.find(h) != seen.end())
      return;
    seen.insert(h);

    int sc = path_score(board, path);
    int bombs = 0;
    int wilds = 0;
    for (const auto &p : path) {
      const Cell &cell = board.at(p.first, p.second);
      if (cell.is_bomb())
        ++bombs;
      if (cell.is_wildcard())
        ++wilds;
    }
    Candidate cand;
    cand.path = path;
    cand.score = sc;
    cand.rank = sc + 0.45 * static_cast<double>(path.size()) + 4.0 * bombs +
                0.8 * wilds;
    cands.push_back(std::move(cand));
    if (static_cast<int>(cands.size()) > hard_keep) {
      trim_candidates(cands, std::max(limit * (fast ? 3 : 4), limit));
    }
  };

  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      int a = board.at(r, c).color();
      if (c + 1 < N) {
        int b = board.at(r, c + 1).color();
        if (compatible_color(a, b))
          add_candidate({{r, c}, {r, c + 1}});
      }
      if (r + 1 < N) {
        int b = board.at(r + 1, c).color();
        if (compatible_color(a, b))
          add_candidate({{r, c}, {r + 1, c}});
      }
    }
  }

  if (!fast) {
    int comp_cap = (board.level <= 2 ? 22 : 17);
    int comps_used = 0;
    int comp_limit = (board.level <= 2 ? 80 : 40);
    for (int color = 1; color <= 5 && comps_used < comp_limit; ++color) {
      std::vector<char> vis(N * N, 0);
      for (int sr = 0; sr < N && comps_used < comp_limit; ++sr) {
        for (int sc = 0; sc < N && comps_used < comp_limit; ++sc) {
          if (!usable_for_color(board, sr, sc, color))
            continue;
          int sid = id_of(board, sr, sc);
          if (vis[sid])
            continue;

          std::vector<std::pair<int, int>> cells;
          std::queue<std::pair<int, int>> q;
          q.push({sr, sc});
          vis[sid] = 1;
          while (!q.empty()) {
            auto p = q.front();
            q.pop();
            cells.push_back(p);
            for (int d = 0; d < 4; ++d) {
              int nr = p.first + DR[d], nc = p.second + DC[d];
              if (!board.in_bounds(nr, nc))
                continue;
              if (!usable_for_color(board, nr, nc, color))
                continue;
              int id = id_of(board, nr, nc);
              if (vis[id])
                continue;
              vis[id] = 1;
              q.push({nr, nc});
            }
          }

          if (static_cast<int>(cells.size()) < 3 ||
              static_cast<int>(cells.size()) > comp_cap)
            continue;
          ++comps_used;
          int m = static_cast<int>(cells.size());
          std::vector<std::vector<int>> adj(m);
          std::vector<int> pos(N * N, -1);
          for (int i = 0; i < m; ++i)
            pos[id_of(board, cells[i].first, cells[i].second)] = i;
          for (int i = 0; i < m; ++i) {
            int r = cells[i].first, c = cells[i].second;
            for (int d = 0; d < 4; ++d) {
              int nr = r + DR[d], nc = c + DC[d];
              if (!board.in_bounds(nr, nc))
                continue;
              int j = pos[id_of(board, nr, nc)];
              if (j >= 0)
                adj[i].push_back(j);
            }
          }

          std::vector<int> starts(m);
          for (int i = 0; i < m; ++i)
            starts[i] = i;
          std::sort(starts.begin(), starts.end(), [&](int a, int b) {
            if (adj[a].size() != adj[b].size())
              return adj[a].size() < adj[b].size();
            return cells[a] < cells[b];
          });

          std::vector<char> used_comp(m, 0);
          std::vector<int> cur, best;
          long long nodes_left = (board.level <= 2 ? 18000LL : 7000LL);

          std::function<void(int, int)> dfs_exact = [&](int v, int used_cnt) {
            if (nodes_left-- <= 0)
              return;
            if (cur.size() > best.size())
              best = cur;
            if (static_cast<int>(cur.size()) + (m - used_cnt) <=
                static_cast<int>(best.size()))
              return;

            std::vector<std::pair<int, int>> nb;
            for (int u : adj[v]) {
              if (used_comp[u])
                continue;
              int onward = 0;
              for (int w : adj[u]) {
                if (!used_comp[w])
                  ++onward;
              }
              int bomb =
                  board.at(cells[u].first, cells[u].second).is_bomb() ? -6 : 0;
              nb.push_back({onward + bomb, u});
            }
            std::sort(nb.begin(), nb.end());
            for (const auto &entry : nb) {
              int u = entry.second;
              used_comp[u] = 1;
              cur.push_back(u);
              dfs_exact(u, used_cnt + 1);
              cur.pop_back();
              used_comp[u] = 0;
              if (nodes_left <= 0)
                break;
            }
          };

          int start_cap = (board.level <= 2 ? m : std::min(m, 8));
          for (int si = 0; si < start_cap && nodes_left > 0; ++si) {
            int st = starts[si];
            used_comp[st] = 1;
            cur.clear();
            cur.push_back(st);
            dfs_exact(st, 1);
            used_comp[st] = 0;
          }
          if (best.size() >= 2) {
            std::vector<std::pair<int, int>> path;
            for (int idx : best)
              path.push_back(cells[idx]);
            add_candidate(path);
          }
        }
      }
    }
  }

  int mode_count = fast ? 3 : 6;
  int fast_start_cap = (board.level >= 5 ? 30 : 24);

  for (int color = 1; color <= 5; ++color) {
    std::vector<std::pair<double, std::pair<int, int>>> starts;
    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
        if (!usable_for_color(board, r, c, color))
          continue;
        std::vector<char> empty_used(N * N, 0);
        if (onward_degree(board, color, r, c, empty_used) == 0)
          continue;
        starts.push_back({start_value(board, color, r, c), {r, c}});
      }
    }
    std::sort(starts.begin(), starts.end(),
              [](const auto &a, const auto &b) { return a.first > b.first; });
    if (fast && static_cast<int>(starts.size()) > fast_start_cap)
      starts.resize(fast_start_cap);

    for (const auto &start : starts) {
      int sr = start.second.first;
      int sc = start.second.second;

      for (int mode = 0; mode < mode_count; ++mode) {
        std::vector<char> used(N * N, 0);
        std::vector<std::pair<int, int>> path;
        path.push_back({sr, sc});
        used[id_of(board, sr, sc)] = 1;

        while (true) {
          int cr = path.back().first;
          int cc = path.back().second;
          int best_val = std::numeric_limits<int>::min();
          int br = -1, bc = -1;

          for (int d = 0; d < 4; ++d) {
            int nr = cr + DR[d], nc = cc + DC[d];
            if (!board.in_bounds(nr, nc))
              continue;
            int id = id_of(board, nr, nc);
            if (used[id])
              continue;
            if (!usable_for_color(board, nr, nc, color))
              continue;
            int val = move_value(board, color, nr, nc, used, mode,
                                 static_cast<int>(path.size()));
            if (val > best_val) {
              best_val = val;
              br = nr;
              bc = nc;
            }
          }

          if (br < 0)
            break;
          path.push_back({br, bc});
          used[id_of(board, br, bc)] = 1;

          int k = static_cast<int>(path.size());
          if (special_len(k) || board.at(br, bc).is_bomb())
            add_candidate(path);
          if (k == N * N)
            break;
        }
        add_candidate(path);
      }
    }

    if (!fast && !starts.empty()) {
      int dfs_start_cap =
          (board.level >= 4 ? 28 : (board.level <= 2 ? 24 : 20));
      int depth_limit = (board.level >= 4 ? 14 : (board.level <= 2 ? 17 : 12));
      if (board.level == 3)
        depth_limit = 15;
      if (board.level == 5)
        depth_limit = 15;
      long long nodes_left =
          (board.level >= 4 ? 70000LL : (board.level <= 2 ? 68000LL : 42000LL));
      int use_starts = std::min(static_cast<int>(starts.size()), dfs_start_cap);

      for (int si = 0; si < use_starts && nodes_left > 0; ++si) {
        int sr = starts[si].second.first;
        int sc = starts[si].second.second;
        std::vector<char> used(N * N, 0);
        std::vector<std::pair<int, int>> path;
        path.push_back({sr, sc});
        used[id_of(board, sr, sc)] = 1;

        std::function<void(int, int)> dfs = [&](int r, int c) {
          if (nodes_left-- <= 0)
            return;
          int k = static_cast<int>(path.size());
          if (k >= 2 && (special_len(k) || board.at(r, c).is_bomb()))
            add_candidate(path);
          if (k >= depth_limit)
            return;

          std::vector<std::pair<int, std::pair<int, int>>> nb;
          for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d], nc = c + DC[d];
            if (!board.in_bounds(nr, nc))
              continue;
            int id = id_of(board, nr, nc);
            if (used[id])
              continue;
            if (!usable_for_color(board, nr, nc, color))
              continue;
            int val = move_value(board, color, nr, nc, used, 2, k);
            nb.push_back({val, {nr, nc}});
          }
          std::sort(nb.begin(), nb.end(), [](const auto &a, const auto &b) {
            return a.first > b.first;
          });
          int branch_cap = (k < 4 ? 4 : 3);
          if (static_cast<int>(nb.size()) > branch_cap)
            nb.resize(branch_cap);

          for (const auto &entry : nb) {
            int nr = entry.second.first;
            int nc = entry.second.second;
            int id = id_of(board, nr, nc);
            used[id] = 1;
            path.push_back({nr, nc});
            dfs(nr, nc);
            path.pop_back();
            used[id] = 0;
            if (nodes_left <= 0)
              break;
          }
        };
        dfs(sr, sc);
      }
    }
  }

  if (cands.empty())
    return cands;
  trim_candidates(cands, limit);
  return cands;
}

static double board_potential(const Board &board) {
  int N = board.N;
  std::vector<double> tops;
  double sum_small = 0.0;
  double adj_bonus = 0.0;
  double gap_bonus = 0.0;
  double block_bonus = 0.0;
  double bomb_bonus = 0.0;

  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      int a = board.at(r, c).color();
      if (board.at(r, c).is_bomb())
        bomb_bonus += 1.5;
      if (c + 1 < N) {
        int b = board.at(r, c + 1).color();
        if (compatible_color(a, b))
          adj_bonus += 1.0;
      }
      if (r + 1 < N) {
        int b = board.at(r + 1, c).color();
        if (compatible_color(a, b))
          adj_bonus += 1.0;
      }
      if (c + 2 < N) {
        int b = board.at(r, c + 2).color();
        if (compatible_color(a, b))
          gap_bonus += 1.0;
      }
      if (r + 2 < N) {
        int b = board.at(r + 2, c).color();
        if (compatible_color(a, b))
          gap_bonus += 1.0;
      }
      if (r + 1 < N && c + 1 < N) {
        for (int color = 1; color <= 5; ++color) {
          int cnt = 0;
          if (usable_for_color(board, r, c, color))
            ++cnt;
          if (usable_for_color(board, r + 1, c, color))
            ++cnt;
          if (usable_for_color(board, r, c + 1, color))
            ++cnt;
          if (usable_for_color(board, r + 1, c + 1, color))
            ++cnt;
          if (cnt >= 3)
            block_bonus += (cnt == 4 ? 2.0 : 0.8);
        }
      }
    }
  }

  for (int color = 1; color <= 5; ++color) {
    std::vector<char> vis(N * N, 0);
    for (int sr = 0; sr < N; ++sr) {
      for (int sc = 0; sc < N; ++sc) {
        if (!usable_for_color(board, sr, sc, color))
          continue;
        int sid = id_of(board, sr, sc);
        if (vis[sid])
          continue;
        int sz = 0, bombs = 0, wilds = 0, bottom = 0;
        std::queue<std::pair<int, int>> q;
        q.push({sr, sc});
        vis[sid] = 1;
        while (!q.empty()) {
          auto p = q.front();
          q.pop();
          int r = p.first, c = p.second;
          ++sz;
          bottom += r;
          if (board.at(r, c).is_bomb())
            ++bombs;
          if (board.at(r, c).is_wildcard())
            ++wilds;
          for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d], nc = c + DC[d];
            if (!board.in_bounds(nr, nc))
              continue;
            if (!usable_for_color(board, nr, nc, color))
              continue;
            int id = id_of(board, nr, nc);
            if (vis[id])
              continue;
            vis[id] = 1;
            q.push({nr, nc});
          }
        }
        if (sz >= 2) {
          double approx =
              static_cast<double>(path_score(sz)) + 20.0 * bombs + 4.0 * wilds;
          if (board.level <= 2)
            approx += 0.10 * bottom;
          tops.push_back(approx);
          sum_small += std::min(approx, board.level >= 5 ? 360.0 : 280.0);
        }
      }
    }
  }

  if (tops.empty())
    return 0.0;
  std::sort(tops.begin(), tops.end(), std::greater<double>());
  double pot = tops[0];
  if (tops.size() > 1)
    pot += 0.42 * tops[1];
  if (tops.size() > 2)
    pot += 0.22 * tops[2];
  if (tops.size() > 3)
    pot += 0.10 * tops[3];
  pot += 0.020 * sum_small;

  if (board.level <= 2) {
    pot += 2.2 * adj_bonus + 1.05 * gap_bonus + 0.65 * block_bonus;
  } else if (board.level == 3) {
    pot += 1.4 * adj_bonus + 0.70 * gap_bonus + 0.45 * block_bonus;
  } else if (board.level == 4) {
    pot += 0.8 * adj_bonus + 0.35 * gap_bonus + 2.2 * bomb_bonus;
  } else {
    pot += 0.9 * adj_bonus + 0.35 * gap_bonus + 0.35 * block_bonus +
           1.7 * bomb_bonus;
  }
  return pot;
}

struct BeamNode {
  Board board;
  std::vector<std::pair<int, int>> first;
  double value = 0.0;
  double key = 0.0;
  int projected_step = 0;
};

static bool better_node(const BeamNode &a, const BeamNode &b) {
  if (std::fabs(a.key - b.key) > 1e-9)
    return a.key > b.key;
  return a.value > b.value;
}

static double setup_rank_weight(const Board &board) {
  if (board.level <= 2)
    return 0.82;
  if (board.level == 3)
    return 0.66;
  if (board.level == 4)
    return 0.58;
  return 0.54;
}

static void
add_ranked_setup_candidate(const Board &board,
                           std::unordered_set<unsigned long long> &seen,
                           std::vector<Candidate> &extra,
                           const std::vector<std::pair<int, int>> &path) {
  if (path.size() < 2 || !is_valid_path(board, path))
    return;
  unsigned long long h = hash_path_cells(board, path);
  if (seen.find(h) != seen.end())
    return;
  seen.insert(h);

  Candidate cand;
  cand.path = path;
  cand.score = path_score(board, path);

  Board nb = board.preview(path);
  double penalty = nb.is_deadlocked() ? 5000.0 : 0.0;
  double potential = board_potential(nb);
  int bombs = 0;
  int wilds = 0;
  for (const auto &p : path) {
    const Cell &cell = board.at(p.first, p.second);
    if (cell.is_bomb())
      ++bombs;
    if (cell.is_wildcard())
      ++wilds;
  }
  cand.rank = cand.score + setup_rank_weight(board) * potential + 5.0 * bombs +
              1.2 * wilds - penalty;
  extra.push_back(std::move(cand));
}

static void add_setup_roots(const Board &board, std::vector<Candidate> &roots,
                            int extra_limit) {
  std::unordered_set<unsigned long long> seen;
  for (const auto &root : roots)
    seen.insert(hash_path_cells(board, root.path));

  std::vector<Candidate> extra;
  int N = board.N;

  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      int a = board.at(r, c).color();
      for (int dd = 0; dd < 2; ++dd) {
        int nr = r + (dd == 0 ? 1 : 0);
        int nc = c + (dd == 1 ? 1 : 0);
        if (!board.in_bounds(nr, nc))
          continue;
        int b = board.at(nr, nc).color();
        if (!compatible_color(a, b))
          continue;

        std::vector<std::pair<int, int>> path;
        path.push_back({r, c});
        path.push_back({nr, nc});
        add_ranked_setup_candidate(board, seen, extra, path);
      }
    }
  }

  std::vector<int> prefix_lengths;
  if (board.level <= 2) {
    prefix_lengths = {3, 4, 5, 6, 7, 8, 10, 12};
  } else if (board.level == 3) {
    prefix_lengths = {3, 4, 5, 6, 8, 10};
  } else if (board.level == 4) {
    prefix_lengths = {3, 4, 5, 6, 8};
  } else {
    prefix_lengths = {3, 4, 5, 6, 7, 8};
  }

  int prefix_seed_cap =
      std::min(static_cast<int>(roots.size()), board.level <= 2 ? 24 : 16);
  for (int i = 0; i < prefix_seed_cap; ++i) {
    const auto &base = roots[i].path;
    if (base.size() < 4)
      continue;

    for (int dir = 0; dir < 2; ++dir) {
      std::vector<std::pair<int, int>> work = base;
      if (dir == 1)
        std::reverse(work.begin(), work.end());

      for (int len : prefix_lengths) {
        if (len >= static_cast<int>(work.size()))
          continue;
        std::vector<std::pair<int, int>> pref(work.begin(), work.begin() + len);
        add_ranked_setup_candidate(board, seen, extra, pref);
      }
    }
  }

  std::sort(extra.begin(), extra.end(), better_candidate);
  if (static_cast<int>(extra.size()) > extra_limit)
    extra.resize(extra_limit);
  roots.insert(roots.end(), extra.begin(), extra.end());
}

std::vector<std::pair<int, int>> find_best_path(const Board &board,
                                                int current_step) {
  if (board.N <= 1)
    return {{0, 0}, {0, 0}};

  int root_limit = (board.level <= 2 ? 300 : (board.level >= 5 ? 125 : (board.level == 3 ? 118 : 240)));
  std::vector<Candidate> roots = generate_candidates(board, root_limit, false);
  if (roots.empty())
    return fallback_path(board);

  add_setup_roots(board, roots,
                  board.level <= 2 ? 128 : (board.level >= 5 ? 36 : (board.level == 3 ? 38 : 80)));

  int steps_left = 50 - current_step;
  if (steps_left <= 1) {
    int best = 0;
    for (int i = 1; i < static_cast<int>(roots.size()); ++i) {
      if (roots[i].score > roots[best].score ||
          (roots[i].score == roots[best].score &&
           roots[i].path.size() > roots[best].path.size())) {
        best = i;
      }
    }
    return is_valid_path(board, roots[best].path) ? roots[best].path
                                                  : fallback_path(board);
  }

  const double DISCOUNT = (board.level <= 2 ? 0.992 : 0.98);
  const double DEADLOCK_PENALTY = (board.level <= 2 ? 10000.0 : 6500.0);

  double root_weight =
      (board.level <= 2
           ? 1.08
           : (board.level == 3 ? 0.62 : (board.level == 4 ? 0.65 : 0.45)));
  double leaf_weight =
      (board.level <= 2
           ? 0.72
           : (board.level == 3 ? 0.44 : (board.level == 4 ? 0.48 : 0.33)));

  std::vector<BeamNode> beam;
  beam.reserve(roots.size());

  for (const auto &root : roots) {
    BeamNode node;
    node.board = board.preview(root.path);
    node.first = root.path;
    node.value = static_cast<double>(root.score);
    node.projected_step = current_step + 1;
    double penalty = (node.projected_step < 50 && node.board.is_deadlocked())
                         ? DEADLOCK_PENALTY
                         : 0.0;
    double potential =
        (node.projected_step < 50) ? board_potential(node.board) : 0.0;
    node.key = node.value + root_weight * potential - penalty;
    beam.push_back(std::move(node));
  }

  std::sort(beam.begin(), beam.end(), better_node);
  int width1 = (board.level <= 2
                    ? 60
                    : (board.level == 3 ? 25 : (board.level >= 5 ? 24 : 42)));
  if (static_cast<int>(beam.size()) > width1)
    beam.resize(width1);

  double mult = DISCOUNT;
  int max_depth =
      std::min(board.level <= 2 ? 8 : (board.level == 3 ? 5 : (board.level >= 5 ? 4 : 6)), steps_left);

  for (int depth = 2; depth <= max_depth; ++depth) {
    std::vector<BeamNode> next;
    int expand_width, cand_limit, keep_width;
    if (board.level <= 2) {
      if (depth == 2) {
        expand_width = 60;
        cand_limit = 48;
        keep_width = 60;
      } else if (depth == 3) {
        expand_width = 45;
        cand_limit = 36;
        keep_width = 45;
      } else if (depth == 4) {
        expand_width = 22;
        cand_limit = 20;
        keep_width = 22;
      } else if (depth == 5) {
        expand_width = 15;
        cand_limit = 15;
        keep_width = 15;
      } else {
        expand_width = 9;
        cand_limit = 10;
        keep_width = 10;
      }
    } else if (depth == 2) {
      expand_width = (board.level >= 5 ? 22 : (board.level == 3 ? 21 : 42));
      cand_limit = (board.level >= 5 ? 26 : (board.level == 3 ? 25 : 42));
      keep_width = (board.level >= 5 ? 22 : (board.level == 3 ? 21 : 42));
    } else if (depth == 3) {
      expand_width = (board.level == 3 ? 16 : (board.level >= 5 ? 14 : 28));
      cand_limit = (board.level == 3 ? 16 : (board.level >= 5 ? 14 : 28));
      keep_width = (board.level == 3 ? 16 : (board.level >= 5 ? 14 : 28));
    } else {
      expand_width = (board.level == 3 || board.level >= 5) ? 8 : 16;
      cand_limit = (board.level == 3 || board.level >= 5) ? 8 : 16;
      keep_width = (board.level == 3 || board.level >= 5) ? 10 : 18;
    }

    int expand_count = std::min(static_cast<int>(beam.size()), expand_width);
    for (int bi = 0; bi < expand_count; ++bi) {
      if (beam[bi].projected_step >= 50 || beam[bi].board.is_deadlocked()) {
        next.push_back(beam[bi]);
        continue;
      }

      std::vector<Candidate> cands =
          generate_candidates(beam[bi].board, cand_limit, true);
      if (!cands.empty()) {
        if (board.level <= 2 && depth <= 5)
          add_setup_roots(beam[bi].board, cands, depth <= 3 ? 10 : 6);
        else if (board.level == 3 && depth <= 3)
          add_setup_roots(beam[bi].board, cands, 6);
      }
      if (cands.empty()) {
        BeamNode dead = beam[bi];
        dead.key = dead.value - DEADLOCK_PENALTY;
        next.push_back(std::move(dead));
        continue;
      }

      for (const auto &cand : cands) {
        BeamNode node;
        node.board = beam[bi].board.preview(cand.path);
        node.first = beam[bi].first;
        node.value = beam[bi].value + mult * static_cast<double>(cand.score);
        node.projected_step = beam[bi].projected_step + 1;
        double penalty =
            (node.projected_step < 50 && node.board.is_deadlocked())
                ? DEADLOCK_PENALTY
                : 0.0;
        double potential =
            (node.projected_step < 50) ? board_potential(node.board) : 0.0;
        node.key = node.value + (mult * leaf_weight) * potential - penalty;
        next.push_back(std::move(node));
      }
    }

    if (next.empty())
      break;
    std::sort(next.begin(), next.end(), better_node);
    if (static_cast<int>(next.size()) > keep_width)
      next.resize(keep_width);
    beam.swap(next);
    mult *= DISCOUNT;
  }

  std::sort(beam.begin(), beam.end(), better_node);
  std::vector<std::pair<int, int>> ans =
      beam.empty() ? roots[0].path : beam[0].first;
  if (!is_valid_path(board, ans))
    ans = fallback_path(board);
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  GameController ctl;
  while (ctl.update()) {
    auto path = find_best_path(ctl.board(), ctl.step());
    ctl.respond(path);
  }
  return 0;
}
