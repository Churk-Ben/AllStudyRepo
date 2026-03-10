#include <iostream>
using namespace std;

int isYearLeap(int year)
{
    if (year % 4 == 0 && year % 100 != 0)
        return 1;
    else if (year % 400 == 0)
        return 1;
    else
        return 0;
}

int daysInMonth(int year, int month)
{
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isYearLeap(year))
        return 29;
    else
        return days[month - 1];
}

int main()
{
    string dayOfWeek[7] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday"};
    int year, month, day;
    int pass;
    while (true)
    {
        cin >> pass;
        if (pass == -1)
        {
            break;
        }

        string week = dayOfWeek[pass % 7];
        for (int i = 0; i < pass; i++)
        {
            if (pass - (365 + isYearLeap(2000 + i)) < 0)
            {
                year = 2000 + i;
                break;
            }
            pass -= (365 + isYearLeap(2000 + i));
        }
        for (int i = 0; i < 12; i++)
        {
            if (pass - daysInMonth(year, i + 1) < 0)
            {
                month = i + 1;
                break;
            }
            pass -= daysInMonth(year, i + 1);
        }
        day = pass + 1;
        printf("%4d-%02d-%02d %s\n", year, month, day, week.c_str());
    }

    return 0;
}