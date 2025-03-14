#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

// 将时间转换为分钟数
int timeToMinutes(int hour, int minute, bool isAM)
{
    if (!isAM)
    {
        hour += 12;
    }
    return hour * 60 + minute;
}

// 将分钟数转换回时间格式
void minutesToTime(int totalMinutes, int &hour, int &minute, bool &isAM)
{
    hour = totalMinutes / 60 % 24;
    minute = totalMinutes % 60;

    isAM = (hour >= 0 && hour < 12);

    // 特殊情况处理：12:00 a.m. 是午夜，12:00 p.m. 是中午
    if (hour == 0)
    {
        hour = 12;
        isAM = true;
    }
    else if (hour > 12)
    {
        hour -= 12;
    }
}

int main()
{
    string timeStr;
    double hoursPassed;

    cout << "请输入时间（格式为 1:23 a.m. 或 12:30 p.m.）：";
    getline(cin, timeStr);

    cout << "请输入经过的小时数（可以是小数，如 -1.5）：";
    cin >> hoursPassed;

    // 解析时间字符串
    size_t colonPos = timeStr.find(':');
    size_t spacePos = timeStr.find(' ');
    size_t periodPos = timeStr.find('.');

    int hour = stoi(timeStr.substr(0, colonPos));
    int minute = stoi(timeStr.substr(colonPos + 1, spacePos - colonPos - 1));
    string amPm = timeStr.substr(periodPos - 2, 2);

    bool isAM = (amPm == "a.m");

    // 将时间转换为分钟数
    int currentTime = timeToMinutes(hour, minute, isAM);

    // 计算总经过分钟数（包括小时和分钟）
    int totalPassedMinutes = static_cast<int>(hoursPassed * 60);

    // 计算新的时间
    int newTime = currentTime + totalPassedMinutes;

    // 处理跨天的情况
    newTime %= (24 * 60);
    if (newTime < 0)
    {
        newTime += 24 * 60;
    }

    // 将新的时间转换回小时、分钟和上午/下午标识
    int newHour, newMinute;
    bool newIsAM;
    minutesToTime(newTime, newHour, newMinute, newIsAM);

    // 格式化输出
    cout << newHour << ":" << (newMinute < 10 ? "0" : "") << newMinute << " "
         << (newIsAM ? "a.m." : "p.m.") << endl;

    return 0;
}