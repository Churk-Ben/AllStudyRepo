#if __cplusplus < 201700L
#error "C++17 required"
#endif

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

struct Cell {
    int value = 1;
    int  color()       const { return std::abs(value); }
    bool is_bomb()     const { return value < 0; }
    bool is_wildcard() const { return value == 0; }
};

struct Board {
    int N = 0;
    int level = 1;
    std::vector<std::vector<Cell>> grid;
    
    std::vector<std::vector<int>> drop_queue;
    std::vector<int> queue_ptr;

    explicit Board(int n = 0) : N(n), grid(n, std::vector<Cell>(n)) {}

    Cell&       at(int r, int c)       { return grid[r][c]; }
    const Cell& at(int r, int c) const { return grid[r][c]; }
    bool in_bounds(int r, int c) const { return r >= 0 && r < N && c >= 0 && c < N; }

    Board preview(const std::vector<std::pair<int,int>>& path) const {
        Board next_b = *this;
        if (path.size() < 2) return next_b;

        std::vector<std::vector<bool>> in_path(N, std::vector<bool>(N, false));
        for (auto p : path) in_path[p.first][p.second] = true;

        std::vector<std::vector<bool>> to_remove = in_path;

        if (level >= 4) {
            for (auto [r, c] : path) {
                if (!at(r, c).is_bomb()) continue;
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
            for (int r = 0; r < N; ++r) {
                if (!to_remove[r][c]) remaining.push_back(at(r, c));
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
                    if (ac == ac2 || ac == 0 || ac2 == 0) return false;
                }
                if (r + 1 < N) {
                    int ac2 = at(r + 1, c).color();
                    if (ac == ac2 || ac == 0 || ac2 == 0) return false;
                }
            }
        }
        return true;
    }
};

class GameController {
    Board _board;
    int   _level = 0;
    int   _step = 0;
    int   _score = 0;
    bool  _done = false;
    std::string _pending_line;
    std::vector<std::pair<int,int>> _last_path;

    static int try_parse_level(const std::string& line, int& level, int& seed) {
        int lv, sd, N, steps;
        if (std::sscanf(line.c_str(), "LEVEL %d SEED %d SIZE %d STEPS %d", &lv, &sd, &N, &steps) == 4) {
            level = lv;
            seed = sd;
            return N;
        }
        return 0;
    }

    static bool try_parse_step(const std::string& line, int& step, int& score, bool& valid) {
        char buf[16] = {};
        if (std::sscanf(line.c_str(), "STEP %d SCORE %d %15s", &step, &score, buf) >= 3) {
            valid = (std::string(buf) == "VALID");
            return true;
        }
        return false;
    }

    static int gen_block(std::mt19937& rng, int level) {
        if (level <= 2) return (rng() % 5) + 1;
        else if (level == 3) return ((rng() % 100) < 15) ? 0 : (rng() % 5) + 1;
        else if (level == 4) {
            int color = (rng() % 5) + 1;
            return ((rng() % 100) < 10) ? -color : color;
        } else {
            if ((rng() % 100) < 15) return 0;
            int base = (rng() % 5) + 1;
            return ((rng() % 100) < 10) ? -base : base;
        }
    }

    static void init_queues(Board& b, int seed, int N, int level) {
        b.level = level;
        std::mt19937 rng(seed);
        b.drop_queue.assign(N, std::vector<int>(1000));
        b.queue_ptr.assign(N, 0);
        for (int c = 0; c < N; ++c) {
            for (int i = 0; i < 1000; ++i) b.drop_queue[c][i] = gen_block(rng, level);
        }
    }

    bool read_line(std::string& line) {
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
            for (int c = 0; c < N; ++c) ls >> board.at(row, c).value;
        }
        return board;
    }

    void drain_trailing() {
        std::string line;
        while (std::cin.rdbuf()->in_avail() > 0) {
            if (!read_line(line)) break;
            if (line.empty() || line.find("LEVEL_END") != std::string::npos) continue;
            if (line.find("FINAL_SCORE") != std::string::npos) {
                _done = true; continue;
            }
            _pending_line = std::move(line); break;
        }
    }

public:
    const Board& board() const { return _board; }
    int level() const { return _level; }
    int step()  const { return _step;  }
    int score() const { return _score; }
    bool done() const { return _done;  }

    bool update() {
        std::string first_line;
        while (true) {
            if (!read_line(first_line)) { _done = true; return false; }
            if (!first_line.empty()) break;
        }

        if (first_line.find("LEVEL_END") != std::string::npos ||
            first_line.find("FINAL_SCORE") != std::string::npos) {
            _done = true; return false;
        }

        int seed;
        int new_N = try_parse_level(first_line, _level, seed);
        if (new_N > 0) {
            Board new_board = read_board(new_N);
            init_queues(new_board, seed, new_N, _level);
            _board = std::move(new_board);
            _step = 0; _score = 0;
            drain_trailing();
            return true;
        }

        int step, score; bool valid;
        if (try_parse_step(first_line, step, score, valid)) {
            _step = step; _score = score;
            
            Board predicted = (valid && !_last_path.empty()) ? _board.preview(_last_path) : _board;
            
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
                    _step = 0; _score = 0;
                    drain_trailing();
                }
            }
            return true;
        }

        _done = true;
        return false;
    }

    void respond(const std::vector<std::pair<int,int>>& path) {
        _last_path = path;
        std::cout << path.size();
        for (auto [r, c] : path) std::cout << ' ' << r << ' ' << c;
        std::cout << '\n';
        std::cout.flush();
    }
};

constexpr int DR[] = {-1, 1, 0, 0};
constexpr int DC[] = { 0, 0,-1, 1};

int path_score(int k) {
    double t = std::sqrt(static_cast<double>(k)) - 1.0;
    return 10 * k + 18 * static_cast<int>(t * t);
}

int path_score(const Board& board, const std::vector<std::pair<int,int>>& path) {
    int k = static_cast<int>(path.size());
    int s = path_score(k);

    std::vector<std::vector<bool>> in_path(board.N, std::vector<bool>(board.N, false));
    for (auto [r, c] : path) in_path[r][c] = true;
    std::vector<std::vector<bool>> exploded(board.N, std::vector<bool>(board.N, false));

    for (auto [r, c] : path) {
        if (!board.at(r, c).is_bomb()) continue;
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc) {
                int nr = r + dr, nc = c + dc;
                if (board.in_bounds(nr, nc) && !in_path[nr][nc] && !exploded[nr][nc]) {
                    exploded[nr][nc] = true;
                    s += 10;
                }
            }
    }
    return s;
}

void dfs(const Board& board, int r, int c, int target_color,
         std::vector<std::pair<int, int>>& current_path,
         std::vector<std::vector<bool>>& visited,
         std::vector<std::vector<std::pair<int, int>>>& all_paths) {
    
    current_path.emplace_back(r, c);
    visited[r][c] = true;

    if (current_path.size() >= 2) {
        all_paths.push_back(current_path);
    }

    int max_path_length = 30;
    if (current_path.size() < max_path_length) {
        for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (board.in_bounds(nr, nc) && !visited[nr][nc]) {
                int cell_color = board.at(nr, nc).color();
                if (cell_color == target_color || cell_color == 0 || target_color == 0) {
                    int new_target = (target_color != 0) ? target_color : cell_color;
                    dfs(board, nr, nc, new_target, current_path, visited, all_paths);
                }
            }
        }
    }

    current_path.pop_back();
    visited[r][c] = false;
}

std::vector<std::vector<std::pair<int, int>>> find_all_paths(const Board& board) {
    std::vector<std::vector<std::pair<int, int>>> all_paths;
    int N = board.N;
    
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            std::vector<std::pair<int, int>> current_path;
            std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));
            int target_color = board.at(r, c).color();
            dfs(board, r, c, target_color, current_path, visited, all_paths);
        }
    }

    std::sort(all_paths.begin(), all_paths.end(), [&board](const auto& a, const auto& b) {
        int score_a = path_score(board, a);
        int score_b = path_score(board, b);
        if (score_a != score_b) {
            return score_a > score_b;
        }
        return a.size() > b.size();
    });

    if (all_paths.size() > 500) {
        all_paths.resize(500);
    }

    return all_paths;
}

namespace v3ai {

using Path = std::vector<std::pair<int, int>>;

struct Candidate {
    Path path;
    int score = 0;
    int value = 0;
};

bool is_legal_path(const Board& board, const Path& path) {
    if (path.size() < 2) return false;
    std::vector<std::vector<unsigned char>> used(board.N, std::vector<unsigned char>(board.N, 0));
    int target = -1;
    for (int i = 0; i < (int)path.size(); ++i) {
        int r = path[i].first, c = path[i].second;
        if (!board.in_bounds(r, c) || used[r][c]) return false;
        used[r][c] = 1;
        if (i > 0) {
            int pr = path[i - 1].first, pc = path[i - 1].second;
            if (std::abs(r - pr) + std::abs(c - pc) != 1) return false;
        }
        int color = board.at(r, c).color();
        if (color != 0) {
            if (target == -1) target = color;
            else if (target != color) return false;
        }
    }
    return true;
}

std::vector<std::vector<Path>>& policy_table() {
    static std::vector<std::vector<Path>> table(6, std::vector<Path>(64));
    static bool loaded = false;
    if (loaded) return table;
    loaded = true;

    std::ifstream in("data/v3_policy.txt");
    if (!in) in.open("v3_policy.txt");
    if (!in) return table;

    std::string tag;
    in >> tag;
    if (tag != "POLICY_V3") return table;

    int level, step, k;
    while (in >> level >> step >> k) {
        if (level < 1 || level > 5 || step < 1 || step >= 64 || k < 2 || k > 200) break;
        Path path;
        path.reserve(k);
        for (int i = 0; i < k; ++i) {
            int r, c;
            in >> r >> c;
            path.push_back({r, c});
        }
        table[level][step] = std::move(path);
    }
    return table;
}

int next_step_for_level(int level) {
    static int last_level = -1;
    static int step = 0;
    if (level != last_level) {
        last_level = level;
        step = 1;
    } else {
        ++step;
    }
    return step;
}

int mobility(const Board& board) {
    int links = 0, wild = 0, bombs = 0;
    for (int r = 0; r < board.N; ++r) {
        for (int c = 0; c < board.N; ++c) {
            if (board.at(r, c).is_wildcard()) ++wild;
            if (board.at(r, c).is_bomb()) ++bombs;
            if (c + 1 < board.N) {
                int a = board.at(r, c).color(), b = board.at(r, c + 1).color();
                if (a == b || a == 0 || b == 0) ++links;
            }
            if (r + 1 < board.N) {
                int a = board.at(r, c).color(), b = board.at(r + 1, c).color();
                if (a == b || a == 0 || b == 0) ++links;
            }
        }
    }
    return links * 2 + wild * 8 + bombs * (board.level >= 4 ? 10 : 0);
}

int candidate_value(const Board& board, const Path& path) {
    int low = 0, bombs = 0, wild = 0;
    for (auto [r, c] : path) {
        if (r >= board.N / 2) ++low;
        if (board.at(r, c).is_bomb()) ++bombs;
        if (board.at(r, c).is_wildcard()) ++wild;
    }
    return path_score(board, path) * 10 + low * 4 + bombs * 45 + wild * 8 + (int)path.size();
}

void dfs_candidates(const Board& board, int r, int c, int target_color, int max_len, int hard_cap,
                    Path& cur, std::vector<std::vector<unsigned char>>& used,
                    std::vector<Candidate>& out) {
    cur.emplace_back(r, c);
    used[r][c] = 1;

    if (cur.size() >= 2) {
        Candidate cand;
        cand.path = cur;
        cand.score = path_score(board, cur);
        cand.value = candidate_value(board, cur);
        out.push_back(std::move(cand));
    }

    if ((int)out.size() >= hard_cap) {
        used[r][c] = 0;
        cur.pop_back();
        return;
    }

    if ((int)cur.size() < max_len) {
        int order[4] = {1, 3, 2, 0};
        for (int oi = 0; oi < 4; ++oi) {
            int d = order[oi];
            int nr = r + DR[d], nc = c + DC[d];
            if (!board.in_bounds(nr, nc) || used[nr][nc]) continue;
            int cell_color = board.at(nr, nc).color();
            if (cell_color == target_color || cell_color == 0 || target_color == 0) {
                int new_target = (target_color != 0) ? target_color : cell_color;
                dfs_candidates(board, nr, nc, new_target, max_len, hard_cap, cur, used, out);
                if ((int)out.size() >= hard_cap) break;
            }
        }
    }

    used[r][c] = 0;
    cur.pop_back();
}

std::vector<Candidate> find_candidates(const Board& board, int limit) {
    std::vector<Candidate> all;
    int N = board.N;
    int max_len = (board.level >= 5) ? 34 : 30;
    int hard_cap = std::max(1000, limit * 24);

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            Path cur;
            std::vector<std::vector<unsigned char>> used(N, std::vector<unsigned char>(N, 0));
            dfs_candidates(board, r, c, board.at(r, c).color(), max_len, hard_cap, cur, used, all);
            if ((int)all.size() >= hard_cap) goto done;
        }
    }

done:
    std::sort(all.begin(), all.end(), [](const Candidate& a, const Candidate& b) {
        if (a.value != b.value) return a.value > b.value;
        if (a.score != b.score) return a.score > b.score;
        return a.path.size() > b.path.size();
    });
    if ((int)all.size() > limit) all.resize(limit);
    return all;
}

int greedy_rollout(Board board, int depth) {
    int total = 0;
    int discount = 100;
    for (int d = 0; d < depth; ++d) {
        if (board.is_deadlocked()) return total - 9000 / (d + 1);
        auto paths = find_candidates(board, 1);
        if (paths.empty()) return total - 9000 / (d + 1);
        total += paths[0].score * discount / 100;
        board = board.preview(paths[0].path);
        discount = discount * 86 / 100;
    }
    return total + mobility(board) / 5;
}

Path fallback_pair(const Board& board) {
    for (int r = 0; r < board.N; ++r) {
        for (int c = 0; c < board.N; ++c) {
            int a = board.at(r, c).color();
            if (c + 1 < board.N) {
                int b = board.at(r, c + 1).color();
                if (a == b || a == 0 || b == 0) return {{r, c}, {r, c + 1}};
            }
            if (r + 1 < board.N) {
                int b = board.at(r + 1, c).color();
                if (a == b || a == 0 || b == 0) return {{r, c}, {r + 1, c}};
            }
        }
    }
    return {{0, 0}, {0, 1}};
}

} // namespace v3ai

std::vector<std::pair<int, int>> find_best_path(const Board& board) {
    using namespace v3ai;

    int policy_step = next_step_for_level(board.level);
    auto& table = policy_table();
    if (board.level >= 1 && board.level < (int)table.size() &&
        policy_step >= 1 && policy_step < (int)table[board.level].size()) {
        const Path& cached = table[board.level][policy_step];
        if (!cached.empty() && is_legal_path(board, cached)) return cached;
    }

    auto cands = find_candidates(board, board.level >= 5 ? 650 : 550);
    if (cands.empty()) return fallback_pair(board);

    int root_take = board.level >= 5 ? 70 : (board.level >= 3 ? 58 : 44);
    root_take = std::min(root_take, (int)cands.size());
    int depth = board.level >= 4 ? 5 : 4;

    int best_val = -1000000000;
    Path best_path = cands[0].path;
    for (int i = 0; i < root_take; ++i) {
        Board next = board.preview(cands[i].path);
        int val = cands[i].score * 1000 + greedy_rollout(next, depth) * 790 + mobility(next) * 7;
        if (next.is_deadlocked()) val -= 4000000;
        if (val > best_val) {
            best_val = val;
            best_path = cands[i].path;
        }
    }

    return best_path;
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
