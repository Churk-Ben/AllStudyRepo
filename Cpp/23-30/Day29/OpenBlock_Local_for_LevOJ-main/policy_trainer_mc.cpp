#include "locenv.hpp"
#include "ai.hpp"

using Path = std::vector<std::pair<int, int>>;
using Policy = std::vector<std::vector<Path>>;

constexpr int TRAIN_SEED = 114514;
constexpr int STEPS_PER_LEVEL = 50;

struct McStat {
    int visits = 0;
    double total = 0.0;
    int best = -1000000000;
};

Policy load_policy(const std::string& filename) {
    Policy policy(6, std::vector<Path>(64));
    std::ifstream in(filename);
    if (!in) return policy;

    std::string tag;
    in >> tag;
    if (tag != "POLICY_V3") return policy;

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
        policy[level][step] = std::move(path);
    }
    return policy;
}

void save_policy(const std::string& filename, const Policy& policy) {
    std::ofstream out(filename);
    out << "POLICY_V3\n";
    for (int level = 1; level <= 5; ++level) {
        for (int step = 1; step <= STEPS_PER_LEVEL; ++step) {
            const Path& path = policy[level][step];
            if (path.empty()) continue;
            out << level << ' ' << step << ' ' << path.size();
            for (auto [r, c] : path) out << ' ' << r << ' ' << c;
            out << '\n';
        }
    }
}

Board initial_board(int level) {
    int N = (level <= 4) ? 10 : 12;
    Board board(N);
    init_queues(board, TRAIN_SEED, N, level);
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            board.at(r, c).value = board.drop_queue[c][board.queue_ptr[c]++];
        }
    }
    return board;
}

Path online_choice(const Board& board) {
    auto cands = v3ai::find_candidates(board, board.level >= 5 ? 650 : 550);
    if (cands.empty()) return v3ai::fallback_pair(board);

    int root_take = board.level >= 5 ? 70 : (board.level >= 3 ? 58 : 44);
    root_take = std::min(root_take, (int)cands.size());
    int depth = board.level >= 4 ? 5 : 4;

    int best_val = -1000000000;
    Path best_path = cands[0].path;
    for (int i = 0; i < root_take; ++i) {
        Board next = board.preview(cands[i].path);
        int val = cands[i].score * 1000 + v3ai::greedy_rollout(next, depth) * 790 + v3ai::mobility(next) * 7;
        if (next.is_deadlocked()) val -= 4000000;
        if (val > best_val) {
            best_val = val;
            best_path = cands[i].path;
        }
    }
    return best_path;
}

Path policy_or_online(const Board& board, const Policy& policy, int step) {
    if (step >= 1 && step < (int)policy[board.level].size()) {
        const Path& cached = policy[board.level][step];
        if (!cached.empty() && v3ai::is_legal_path(board, cached)) return cached;
    }
    return online_choice(board);
}

int finish_level_from(Board board, int first_step, const Policy& policy) {
    int total = 0;
    for (int step = first_step; step <= STEPS_PER_LEVEL; ++step) {
        if (board.is_deadlocked()) break;
        Path path = policy_or_online(board, policy, step);
        total += path_score(board, path);
        board = board.preview(path);
    }
    return total;
}

int play_level(int level, const Policy& policy, std::vector<Board>* before_step = nullptr) {
    Board board = initial_board(level);
    int total = 0;
    if (before_step) before_step->assign(STEPS_PER_LEVEL + 1, Board());
    for (int step = 1; step <= STEPS_PER_LEVEL; ++step) {
        if (board.is_deadlocked()) break;
        if (before_step) (*before_step)[step] = board;
        Path path = policy_or_online(board, policy, step);
        total += path_score(board, path);
        board = board.preview(path);
    }
    return total;
}

Path random_candidate(const Board& board, int limit, std::mt19937& rng) {
    auto cands = v3ai::find_candidates(board, limit);
    if (cands.empty()) return v3ai::fallback_pair(board);

    int width = std::min<int>(cands.size(), std::max(4, limit / 3));
    int a = (int)(rng() % width);
    int b = (int)(rng() % width);
    int c = (int)(rng() % width);
    int idx = std::min(a, std::min(b, c));
    if ((rng() % 100) < 12) idx = (int)(rng() % width);
    return cands[idx].path;
}

int mc_suffix(Board board, int first_step, const Policy& policy, int rollout_limit,
              int horizon, std::mt19937& rng) {
    int total = 0;
    int last_step = std::min(STEPS_PER_LEVEL, first_step + horizon - 1);
    for (int step = first_step; step <= last_step; ++step) {
        if (board.is_deadlocked()) return total - 8000 / (step - first_step + 1);

        Path path;
        const Path& cached = policy[board.level][step];
        bool use_cached = !cached.empty() && v3ai::is_legal_path(board, cached) && ((rng() % 100) < 58);
        if (use_cached) path = cached;
        else path = random_candidate(board, rollout_limit, rng);

        total += path_score(board, path);
        board = board.preview(path);
    }

    if (last_step < STEPS_PER_LEVEL && !board.is_deadlocked()) {
        int depth = std::min(8, STEPS_PER_LEVEL - last_step);
        total += v3ai::greedy_rollout(board, depth);
    }
    return total;
}

int select_ucb(const std::vector<McStat>& stats, int total_visits, double explore, std::mt19937& rng) {
    int best = 0;
    double best_score = -1e100;
    for (int i = 0; i < (int)stats.size(); ++i) {
        double noise = (double)(rng() % 1000) / 1000000.0;
        double score;
        if (stats[i].visits == 0) {
            score = 1e50 + noise - i * 0.01;
        } else {
            double avg = stats[i].total / stats[i].visits;
            score = avg + explore * std::sqrt(std::log(total_visits + 2.0) / stats[i].visits) + noise;
        }
        if (score > best_score) {
            best_score = score;
            best = i;
        }
    }
    return best;
}

int main(int argc, char** argv) {
    std::string filename = "data/v3_policy.txt";
    int passes = (argc >= 2) ? std::max(1, std::atoi(argv[1])) : 1;
    int samples = (argc >= 3) ? std::max(1, std::atoi(argv[2])) : 96;
    int candidate_limit = (argc >= 4) ? std::max(8, std::atoi(argv[3])) : 64;
    int verify_limit = (argc >= 5) ? std::max(1, std::atoi(argv[4])) : 6;
    int first_level = (argc >= 6) ? std::max(1, std::atoi(argv[5])) : 1;
    int last_level = (argc >= 7) ? std::min(5, std::atoi(argv[6])) : 5;
    int first_step = (argc >= 8) ? std::max(1, std::atoi(argv[7])) : 1;
    int last_step = (argc >= 9) ? std::min(STEPS_PER_LEVEL, std::atoi(argv[8])) : STEPS_PER_LEVEL;
    int rollout_limit = (argc >= 10) ? std::max(4, std::atoi(argv[9])) : 16;
    int horizon = (argc >= 11) ? std::max(1, std::atoi(argv[10])) : 10;
    unsigned seed = (argc >= 12) ? (unsigned)std::strtoul(argv[11], nullptr, 10) : 20260616u;

    if (first_level > last_level) std::swap(first_level, last_level);
    if (first_step > last_step) std::swap(first_step, last_step);
    std::mt19937 rng(seed);

    Policy policy = load_policy(filename);
    int grand = 0;
    for (int level = 1; level <= 5; ++level) grand += play_level(level, policy);
    std::cerr << "baseline " << grand << "\n";

    for (int pass = 1; pass <= passes; ++pass) {
        bool changed = false;
        for (int level = first_level; level <= last_level; ++level) {
            std::vector<Board> states;
            int level_score = play_level(level, policy, &states);
            std::cerr << "pass " << pass << " level " << level << " start " << level_score << "\n";

            for (int step = first_step; step <= last_step; ++step) {
                if (states[step].N == 0 || states[step].is_deadlocked()) continue;
                Board before = states[step];
                int base_suffix = finish_level_from(before, step, policy);
                auto cands = v3ai::find_candidates(before, candidate_limit);
                if (cands.empty()) continue;

                std::vector<McStat> stats(cands.size());
                for (int s = 0; s < samples; ++s) {
                    int idx = select_ucb(stats, s, 180.0, rng);
                    if (!v3ai::is_legal_path(before, cands[idx].path)) continue;
                    Board after = before.preview(cands[idx].path);
                    int value = cands[idx].score + mc_suffix(after, step + 1, policy, rollout_limit, horizon, rng);
                    stats[idx].visits++;
                    stats[idx].total += value;
                    stats[idx].best = std::max(stats[idx].best, value);
                }

                std::vector<std::pair<double, int>> ranked;
                for (int i = 0; i < (int)cands.size(); ++i) {
                    if (stats[i].visits == 0) continue;
                    double avg = stats[i].total / stats[i].visits;
                    double rank_score = std::max<double>(stats[i].best, avg + cands[i].score * 0.15);
                    ranked.push_back({rank_score, i});
                }
                std::sort(ranked.begin(), ranked.end(), std::greater<std::pair<double, int>>());
                if ((int)ranked.size() > verify_limit) ranked.resize(verify_limit);

                int best_suffix = base_suffix;
                Path best_path;
                for (auto [unused, idx] : ranked) {
                    Board after = before.preview(cands[idx].path);
                    int value = cands[idx].score + finish_level_from(after, step + 1, policy);
                    if (value > best_suffix) {
                        best_suffix = value;
                        best_path = cands[idx].path;
                    }
                }

                std::cerr << "  mc L" << level << " S" << step
                          << " sampled " << samples << " verify " << ranked.size() << "\n";
                if (!best_path.empty()) {
                    policy[level][step] = best_path;
                    changed = true;
                    int gain = best_suffix - base_suffix;
                    std::cerr << "  improve L" << level << " S" << step << " +" << gain << "\n";
                    save_policy(filename, policy);
                    level_score = play_level(level, policy, &states);
                    std::cerr << "  level " << level << " now " << level_score << "\n";
                }
            }
        }

        grand = 0;
        for (int level = 1; level <= 5; ++level) grand += play_level(level, policy);
        std::cerr << "after pass " << pass << " score " << grand << "\n";
        save_policy(filename, policy);
        if (!changed) break;
    }

    return 0;
}
