#if __cplusplus < 201700L
#error "C++17 required"
#endif

#ifndef SUBMISSION_FILE
#define SUBMISSION_FILE "solution.cpp"
#endif

#define main submission_main
#include SUBMISSION_FILE
#undef main

#include <chrono>
#include <iomanip>

static int bench_gen_block(std::mt19937 &rng, int level) {
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

static bool bench_has_move(const Board &b) { return !b.is_deadlocked(); }

static bool bench_compatible(int a, int b) {
  return a == b || a == 0 || b == 0;
}

static bool bench_is_valid_path(const Board &board,
                                const std::vector<std::pair<int, int>> &path) {
  if (path.size() < 2)
    return false;
  std::vector<char> seen(board.N * board.N, 0);
  int fixed_color = 0;
  for (std::size_t i = 0; i < path.size(); ++i) {
    int r = path[i].first, c = path[i].second;
    if (!board.in_bounds(r, c))
      return false;
    int id = r * board.N + c;
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

static std::vector<std::pair<int, int>> bench_fallback_path(const Board &board) {
  for (int r = 0; r < board.N; ++r) {
    for (int c = 0; c < board.N; ++c) {
      int a = board.at(r, c).color();
      if (c + 1 < board.N &&
          bench_compatible(a, board.at(r, c + 1).color()))
        return {{r, c}, {r, c + 1}};
      if (r + 1 < board.N &&
          bench_compatible(a, board.at(r + 1, c).color()))
        return {{r, c}, {r + 1, c}};
    }
  }
  return {{0, 0}, {0, std::min(1, board.N - 1)}};
}

template <typename B>
static auto bench_find_best_path_impl(const B &b, int step, int)
    -> decltype(find_best_path(b, step)) {
  return find_best_path(b, step);
}

template <typename B>
static auto bench_find_best_path_impl(const B &b, int, long)
    -> decltype(find_best_path(b)) {
  return find_best_path(b);
}

static std::vector<std::pair<int, int>> bench_find_best_path(const Board &b,
                                                             int step) {
  return bench_find_best_path_impl(b, step, 0);
}

static Board bench_init_board(int seed, int level, int N) {
  std::mt19937 init_rng(seed + level * 1000003);
  Board b(N);
  b.level = level;

  do {
    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
        b.at(r, c).value = bench_gen_block(init_rng, level);
      }
    }
  } while (!bench_has_move(b));

  std::mt19937 drop_rng(seed);
  b.drop_queue.assign(N, std::vector<int>(5000));
  b.queue_ptr.assign(N, 0);
  for (int c = 0; c < N; ++c) {
    for (int i = 0; i < 5000; ++i)
      b.drop_queue[c][i] = bench_gen_block(drop_rng, level);
  }
  return b;
}

struct BenchLevelResult {
  int score = 0;
  int steps = 0;
  bool deadlock = false;
  double millis = 0.0;
};

static BenchLevelResult bench_run_level(int seed, int level, int N) {
  Board b = bench_init_board(seed, level, N);
  BenchLevelResult result;
  auto t0 = std::chrono::steady_clock::now();

  for (int step = 0; step < 50; ++step) {
    if (b.is_deadlocked()) {
      result.deadlock = true;
      break;
    }
    auto path = bench_find_best_path(b, step);
    if (!bench_is_valid_path(b, path)) {
      path = bench_fallback_path(b);
    }
    result.score += path_score(b, path);
    b = b.preview(path);
    result.steps = step + 1;
  }

  auto t1 = std::chrono::steady_clock::now();
  result.millis =
      std::chrono::duration<double, std::milli>(t1 - t0).count();
  if (b.is_deadlocked() && result.steps < 50)
    result.deadlock = true;
  return result;
}

int main(int argc, char **argv) {
  int first_seed = 114514;
  int seed_count = 1;
  int only_level = 0;
  if (argc >= 2)
    first_seed = std::atoi(argv[1]);
  if (argc >= 3)
    seed_count = std::atoi(argv[2]);
  if (argc >= 4)
    only_level = std::atoi(argv[3]);

  long long grand_total = 0;
  double grand_ms = 0.0;
  for (int si = 0; si < seed_count; ++si) {
    int seed = first_seed + si;
    int total = 0;
    double total_ms = 0.0;
    std::cout << "seed " << seed;
    for (int level = 1; level <= 5; ++level) {
      if (only_level != 0 && level != only_level)
        continue;
      int N = (level == 5 ? 12 : 10);
      BenchLevelResult r = bench_run_level(seed, level, N);
      total += r.score;
      total_ms += r.millis;
      std::cout << " L" << level << "=" << r.score << "/" << r.steps;
      if (r.deadlock)
        std::cout << "D";
    }
    std::cout << " total=" << total << " time_ms=" << std::fixed
              << std::setprecision(1) << total_ms << "\n";
    grand_total += total;
    grand_ms += total_ms;
  }
  if (seed_count > 1) {
    std::cout << "avg_total=" << (grand_total / (double)seed_count)
              << " avg_time_ms=" << (grand_ms / seed_count) << "\n";
  }
}
