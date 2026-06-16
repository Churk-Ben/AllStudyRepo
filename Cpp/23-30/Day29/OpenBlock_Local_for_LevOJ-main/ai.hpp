#pragma once

#include "locenv.hpp"
typedef std::vector<std::pair<int,int>> ans;

namespace v3ai {

struct Candidate {
    ans path;
    int score = 0;
    int value = 0;
};

static bool is_legal_path(const Board& board, const ans& path) {
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

static std::vector<std::vector<ans>>& policy_table() {
    static std::vector<std::vector<ans>> table(6, std::vector<ans>(64));
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
        ans path;
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

static int next_step_for_level(int level) {
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

static int mobility(const Board& board) {
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

static int candidate_value(const Board& board, const ans& path) {
    int low = 0, bombs = 0, wild = 0;
    for (auto [r, c] : path) {
        if (r >= board.N / 2) ++low;
        if (board.at(r, c).is_bomb()) ++bombs;
        if (board.at(r, c).is_wildcard()) ++wild;
    }
    return path_score(board, path) * 10 + low * 4 + bombs * 45 + wild * 8 + (int)path.size();
}

static void dfs(const Board& board, int r, int c, int target_color, int max_len, int hard_cap,
                ans& cur, std::vector<std::vector<unsigned char>>& used,
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
                dfs(board, nr, nc, new_target, max_len, hard_cap, cur, used, out);
                if ((int)out.size() >= hard_cap) break;
            }
        }
    }

    used[r][c] = 0;
    cur.pop_back();
}

static std::vector<Candidate> find_candidates(const Board& board, int limit) {
    std::vector<Candidate> all;
    int N = board.N;
    int max_len = (board.level >= 5) ? 34 : 30;
    int hard_cap = std::max(1000, limit * 24);

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            ans cur;
            std::vector<std::vector<unsigned char>> used(N, std::vector<unsigned char>(N, 0));
            dfs(board, r, c, board.at(r, c).color(), max_len, hard_cap, cur, used, all);
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

static int greedy_rollout(Board board, int depth) {
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

static ans fallback_pair(const Board& board) {
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

ans find_best_path(const Board &board) {
    using namespace v3ai;

    int policy_step = next_step_for_level(board.level);
    auto& table = policy_table();
    if (board.level >= 1 && board.level < (int)table.size() &&
        policy_step >= 1 && policy_step < (int)table[board.level].size()) {
        const ans& cached = table[board.level][policy_step];
        if (!cached.empty() && is_legal_path(board, cached)) return cached;
    }

    auto cands = find_candidates(board, board.level >= 5 ? 650 : 550);
    if (cands.empty()) return fallback_pair(board);

    int root_take = board.level >= 5 ? 70 : (board.level >= 3 ? 58 : 44);
    root_take = std::min(root_take, (int)cands.size());
    int depth = board.level >= 4 ? 5 : 4;

    int best_val = -1000000000;
    ans best_path = cands[0].path;
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
