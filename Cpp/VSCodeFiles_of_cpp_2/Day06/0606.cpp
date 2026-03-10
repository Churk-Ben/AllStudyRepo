#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// 定义时区与UTC偏移量的映射
map<string, int> timezone_offsets = {
    {"HST", -10}, {"EST", -5}, {"CST", -6}, {"MST", -7}, {"PST", -8}, {"AST", -4}, {"ADT", -3}, {"GMT", 0}, {"UTC", 0}, {"CEST", 2}, {"MSK", 3}};

struct Time
{
    int hour;
    int minute;
    string am_pm;
};

// 将时间转换为分钟数
int time_to_minutes(const Time &t)
{
    int total = t.hour * 60 + t.minute;
    if (t.am_pm == "p.m." && t.hour != 12)
    {
        total += 12 * 60;
    }
    else if (t.am_pm == "a.m." && t.hour == 12)
    {
        total -= 12 * 60;
    }
    return total;
}

// 将分钟数转换回时间格式
Time minutes_to_time(int total_minutes)
{
    Time t;
    t.hour = total_minutes / 60;
    t.minute = total_minutes % 60;
    if (t.hour >= 24)
    {
        t.hour -= 24;
    }
    else if (t.hour < 0)
    {
        t.hour += 24;
    }
    t.am_pm = (t.hour >= 12) ? "p.m." : "a.m.";
    if (t.hour == 0)
    {
        t.hour = 12;
        t.am_pm = "a.m.";
    }
    else if (t.hour > 12)
    {
        t.hour -= 12;
    }
    return t;
}

// 格式化输出时间
string format_time(const Time &t)
{
    string result;
    if (t.hour == 0)
    {
        result += "midnight";
    }
    else
    {
        result += (t.hour < 10 ? "0" : "") + to_string(t.hour) + ":";
        result += (t.minute < 10 ? "0" : "") + to_string(t.minute) + " ";
        result += t.am_pm;
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(); // 忽略换行符

    for (int i = 0; i < n; ++i)
    {
        string time_str, am_pm, from_tz, to_tz;
        getline(cin, time_str, ' ');
        cin >> am_pm >> from_tz >> to_tz;
        cin.ignore(); // 忽略换行符

        // 解析时间
        Time time;
        int colon_pos = time_str.find(':');
        time.hour = stoi(time_str.substr(0, colon_pos));
        time.minute = stoi(time_str.substr(colon_pos + 1));
        time.am_pm = am_pm;

        // 转换为分钟数
        int total_minutes = time_to_minutes(time);

        // 计算时区差
        int offset_diff = timezone_offsets[to_tz] - timezone_offsets[from_tz];
        total_minutes += offset_diff * 60;

        // 转换回时间格式
        Time converted_time = minutes_to_time(total_minutes);

        // 输出结果
        cout << format_time(converted_time) << endl;
    }

    return 0;
}