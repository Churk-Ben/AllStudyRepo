#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

vector<string> TimeZone = {"UTC", "GMT", "BST", "IST", "WET", "WEST", "CET", "CEST", "EET", "EEST", "MSK", "MSD", "AST", "ADT", "NST", "NDT", "EST", "EDT", "CST", "CDT", "MST", "MDT", "PST", "PDT", "HST", "AKST", "AKDT", "AEST", "AEDT", "ACST", "ACDT", "AWST"};
vector<double> Offset = {+0, +0, +1, +1, +0, +1, +1, +2, +2, +3, +3, +4, -4, -3, -3.5, -2.5, -5, -4, -6, -5, -7, -6, -8, -7, -10, -9, -8, +10, +11, +9.5, +10.5, +8};

// 计算时区偏移
double offset(string ori, string to)
{
    double sum = 0;
    string target = ori;
    auto it = find(TimeZone.begin(), TimeZone.end(), target);
    int index = distance(TimeZone.begin(), it);
    sum -= Offset[index];
    target = to;
    it = find(TimeZone.begin(), TimeZone.end(), target);
    index = distance(TimeZone.begin(), it);
    sum += Offset[index];
    return sum;
}

// 将时间转换为分钟数
int timeToMinutes(int hour, int minute, bool isAM)
{
    if (!isAM && hour != 12)
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
    int n;
    cin >> n;
    string time, ampm, ori, to;
    while (n--)
    {
        cin >> time;
        if (time == "noon")
        {
            time = "12:00";
            ampm = "p.m.";
            cin >> ori >> to;
        }
        else if (time == "midnight")
        {
            time = "12:00";
            ampm = "a.m.";
            cin >> ori >> to;
        }
        else
        {
            cin >> ampm >> ori >> to;
        }
        double hoursPassed = offset(ori, to);

        // 解析时间字符串
        size_t colonPos = time.find(':');
        int hour = stoi(time.substr(0, colonPos));
        int minute = stoi(time.substr(colonPos + 1, time.length() - 1));
        bool isAM = (ampm == "a.m.");

        // 将时间转换为分钟数，计算新的时间
        int currentTime = timeToMinutes(hour, minute, isAM);
        int totalPassedMinutes = static_cast<int>(hoursPassed * 60);
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
        if (newHour == 12 && newMinute == 0)
        {
            cout << (newIsAM ? "midnight" : "noon") << endl;
        }
        else
        {
            cout << newHour << ":" << newMinute << " "
                 << (newIsAM ? "a.m." : "p.m.") << endl;
        }
    }

    return 0;
}