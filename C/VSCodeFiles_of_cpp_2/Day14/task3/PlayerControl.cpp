#include "PlayerControl.h"
#include <iostream>
#include <algorithm>

int PlayerControl::total_cnt = 0;

PlayerControl::PlayerControl() {}

// 待补足
// 1. 将输入字符串转为小写，实现大小写不敏感
// 2. 匹配"play"/"pause"/"next"/"prev"/"stop"并返回对应枚举
// 3. 未匹配的字符串返回ControlType::Unknown
// 4. 每次成功调用parse时递增total_cnt
ControlType PlayerControl::parse(const std::string &control_str)
{
    std::string cmd = control_str;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    ++total_cnt;

    if (cmd == "play")
        return ControlType::Play;
    if (cmd == "pause")
        return ControlType::Pause;
    if (cmd == "next")
        return ControlType::Next;
    if (cmd == "prev")
        return ControlType::Prev;
    if (cmd == "stop")
        return ControlType::Stop;
    return ControlType::Unknown;
}

void PlayerControl::execute(ControlType cmd) const
{
    switch (cmd)
    {
    case ControlType::Play:
        std::cout << "[play] Playing music...\n";
        break;
    case ControlType::Pause:
        std::cout << "[Pause] Music paused\n";
        break;
    case ControlType::Next:
        std::cout << "[Next] Skipping to next track\n";
        break;
    case ControlType::Prev:
        std::cout << "[Prev] Back to previous track\n";
        break;
    case ControlType::Stop:
        std::cout << "[Stop] Music stopped\n";
        break;
    default:
        std::cout << "[Error] unknown control\n";
        break;
    }
}

int PlayerControl::get_cnt()
{
    return total_cnt;
}