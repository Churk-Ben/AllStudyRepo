#!/usr/bin/env python3
import argparse
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parent
TRAINER = ROOT / "policy_trainer_mc.exe"
JUDGE = ROOT / "local_judge.exe"
V3 = ROOT / "data" / "v3.cpp"
V4 = ROOT / "data" / "v4.cpp"
POLICY = ROOT / "data" / "v3_policy.txt"


JOBS = [
    # passes, samples, candidate_limit, verify_limit, first_level, last_level,
    # first_step, last_step, rollout_limit, horizon
    (1, 48, 36, 4, 4, 4, 35, 50, 10, 8),
    (1, 40, 32, 4, 3, 3, 25, 50, 10, 8),
    (1, 36, 28, 3, 5, 5, 42, 50, 8, 7),
    (1, 30, 24, 3, 5, 5, 25, 41, 8, 7),
    (1, 36, 30, 3, 4, 4, 20, 34, 9, 7),
    (1, 32, 28, 3, 1, 2, 1, 50, 8, 7),
]


def run(cmd, timeout=None):
    try:
        proc = subprocess.run(
            cmd,
            cwd=ROOT,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            timeout=timeout,
        )
        return proc.returncode, proc.stdout, False
    except subprocess.TimeoutExpired as exc:
        output = exc.stdout or ""
        if isinstance(output, bytes):
            output = output.decode(errors="replace")
        return 124, output + "\n[TIMEOUT]\n", True


def compile_targets():
    commands = [
        ["g++", "-std=c++17", "-O2", "-o", str(TRAINER), "policy_trainer_mc.cpp"],
        ["g++", "-std=c++17", "-O2", "-o", str(JUDGE), "local_judge.cpp"],
    ]
    for cmd in commands:
        code, out, _ = run(cmd, timeout=120)
        print(out, end="")
        if code != 0:
            raise SystemExit(f"compile failed: {' '.join(cmd)}")


def judge_score():
    code, out, _ = run([str(JUDGE)], timeout=180)
    print(out, end="")
    match = re.search(r"FINAL_SCORE:\s*(\d+)", out)
    if code != 0 or not match:
        raise RuntimeError("local_judge failed or FINAL_SCORE missing")
    return int(match.group(1))


def hardcode_v4():
    text = V3.read_text(encoding="utf-8")
    lines = POLICY.read_text(encoding="utf-8").splitlines()
    entries = []
    for line in lines[1:]:
        if not line.strip():
            continue
        nums = list(map(int, line.split()))
        level, step = nums[0], nums[1]
        coords = nums[3:]
        pairs = [f"{{{coords[i]}, {coords[i + 1]}}}" for i in range(0, len(coords), 2)]
        entries.append(f"        table[{level}][{step}] = Path{{{', '.join(pairs)}}};")

    init = (
        "std::vector<std::vector<Path>>& policy_table() {\n"
        "    static std::vector<std::vector<Path>> table(6, std::vector<Path>(64));\n"
        "    static bool loaded = false;\n"
        "    if (loaded) return table;\n"
        "    loaded = true;\n\n"
        + "\n".join(entries)
        + "\n    return table;\n"
        "}\n"
    )
    pattern = re.compile(
        r"std::vector<std::vector<Path>>& policy_table\(\) \{.*?\n\}\n\nint next_step_for_level",
        re.S,
    )
    text, count = pattern.subn(init + "\nint next_step_for_level", text, count=1)
    if count != 1:
        raise RuntimeError("failed to replace policy_table in v4 source")
    text = text.replace("#include <fstream>\n", "")
    V4.write_text(text, encoding="utf-8")

    code, out, _ = run(["g++", "-std=c++17", "-O2", "-o", str(ROOT / "data" / "v4.exe"), str(V4)], timeout=120)
    print(out, end="")
    if code != 0:
        raise RuntimeError("v4.cpp compile failed")
    print(f"[sync] hardcoded {len(entries)} policy entries into data/v4.cpp")


def main():
    parser = argparse.ArgumentParser(description="Run MC policy improvement forever or for fixed rounds.")
    parser.add_argument("--target", type=int, default=30000)
    parser.add_argument("--max-rounds", type=int, default=0, help="0 means infinite")
    parser.add_argument("--timeout", type=int, default=120, help="seconds per trainer job")
    parser.add_argument("--sleep", type=float, default=0.0, help="seconds between jobs")
    parser.add_argument("--seed", type=int, default=20260619)
    parser.add_argument("--compile-only", action="store_true")
    args = parser.parse_args()

    compile_targets()
    if args.compile_only:
        return

    best = judge_score()
    hardcode_v4()
    print(f"[start] score={best}, target={args.target}")

    round_id = 0
    job_id = 0
    while args.max_rounds == 0 or round_id < args.max_rounds:
        round_id += 1
        print(f"[round {round_id}]")
        for job in JOBS:
            job_id += 1
            seed = args.seed + job_id * 9973
            cmd = [str(TRAINER)] + [str(x) for x in job] + [str(seed)]
            backup = POLICY.with_suffix(".txt.bak")
            shutil.copyfile(POLICY, backup)
            print("[run]", " ".join(Path(x).name if i == 0 else x for i, x in enumerate(cmd)))
            _, out, timed_out = run(cmd, timeout=args.timeout)
            print(out, end="")

            if "improve L" in out:
                score = judge_score()
                if score > best:
                    print(f"[best] {best} -> {score}")
                    best = score
                    hardcode_v4()
                    if best >= args.target:
                        print(f"[done] reached target {args.target}")
                        return
                else:
                    print(f"[warn] trainer reported improvement but judge score is {score}, best is {best}")
                    shutil.copyfile(backup, POLICY)
                    hardcode_v4()
                    print("[rollback] restored previous policy")

            if timed_out:
                print("[next] job timed out; continuing with next interval")
            if args.sleep > 0:
                time.sleep(args.sleep)

    print(f"[stop] max rounds reached, best={best}")


if __name__ == "__main__":
    main()
