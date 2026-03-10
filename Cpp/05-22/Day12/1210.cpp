#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

char getsign(int sign)
{
    switch (sign)
    {
    case 0:
        return '+';
    case 1:
        return '-';
    case 2:
        return '*';
    case 3:
        return '/';
    default:
        return 0;
    }
}

int calculate(int sign, int num1, int num2)
{
    switch (sign)
    {
    case 0:
        return num1 + num2;
    case 1:
        return num1 - num2;
    case 2:
        return num1 * num2;
    case 3:
        return num1 / num2;
    default:
        return 0;
    }
}
int main()
{
    srand(static_cast<unsigned>(time(0)));
    int num1, num2;
    int correctCount = 0;
    int userAnswer;

    for (int i = 0; i < 10; ++i)
    {
        int sign = rand() % 4;
        do
        {
            num1 = rand() % 10 + 1;
            num2 = rand() % 10 + 1;
            if (sign == 1 && num1 < num2)
                continue;
            if (sign == 3 && (num2 == 0 || num1 % num2 != 0))
                continue;
            break;
        } while (true);

        cout << num1 << ' ' << getsign(sign) << ' ' << num2 << " = ";
        cin >> userAnswer;

        if (userAnswer == calculate(sign, num1, num2))
        {
            ++correctCount;
        }
    }

    cout << "ÕıÈ·ÂÊ£º" << fixed << setprecision(2)
         << (correctCount / 10.0) * 100 << "%" << endl;
    return 0;
}
