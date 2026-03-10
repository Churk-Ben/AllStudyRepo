#include <iostream>
using namespace std;

char map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'};

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string isbn;
        cin >> isbn;
        int sum = 0;
        int pos = 1;
        for (int i = 0; i < 11; i++)
        {
            if (isbn[i] == '-')
            {
                continue;
            }
            sum += (isbn[i] - '0') * pos;
            pos++;
        }
        if (isbn[12] == map[sum % 11])
        {
            cout << "Right" << endl;
        }
        else
        {
            cout << isbn.substr(0, 12) + map[sum % 11] << endl;
        }
    }

    return 0;
}
