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

std::vector<std::pair<int, int>> find_best_path(const Board& board) {
    int N = board.N;
    
    auto all_paths = find_all_paths(board);
    
    if (all_paths.empty()) {
        return {{0, 0}, {0, 1}};
    }

    int best_total = -1;
    std::vector<std::pair<int, int>> best_path;

    int sample_size = std::min(20, (int)all_paths.size());
    for (int i = 0; i < sample_size; ++i) {
        const auto& path = all_paths[i];
        int score1 = path_score(board, path);
        Board board1 = board.preview(path);
        
        if (board1.is_deadlocked()) {
            continue;
        }

        auto paths2 = find_all_paths(board1);
        if (paths2.empty()) continue;
        int score2 = path_score(board1, paths2[0]);
        Board board2 = board1.preview(paths2[0]);
        
        if (board2.is_deadlocked()) {
            int total = score1 + score2;
            if (total > best_total) { best_total = total; best_path = path; }
            continue;
        }
        
        auto paths3 = find_all_paths(board2);
        if (paths3.empty()) {
            int total = score1 + score2;
            if (total > best_total) { best_total = total; best_path = path; }
            continue;
        }
        int score3 = path_score(board2, paths3[0]);
        Board board3 = board2.preview(paths3[0]);
        
        if (board3.is_deadlocked()) {
            int total = score1 + score2 + score3;
            if (total > best_total) { best_total = total; best_path = path; }
            continue;
        }
        
        auto paths4 = find_all_paths(board3);
        int score4 = 0;
        if (!paths4.empty()) {
            score4 = path_score(board3, paths4[0]);
        }

        int total = score1 + score2 + score3 + score4;
        if (total > best_total) {
            best_total = total;
            best_path = path;
        }
    }

    if (!best_path.empty()) {
        return best_path;
    }

    return all_paths[0];
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
