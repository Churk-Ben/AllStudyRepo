#include <iostream>
using namespace std;

int main()
{
    while (true)
    {
        int R[5][5];
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cin >> R[i][j];
            }
        }
        int tR[5][5];
        for (int i = 0; i < 5; i++) // copy R to tR
        {
            for (int j = 0; j < 5; j++)
                tR[i][j] = R[i][j];
        }

        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 5; i++)
            {
                if (tR[i][j] == 1)
                {
                    for (int k = 0; k < 5; k++)
                        tR[i][k] = tR[i][k] || tR[j][k];
                }
            }
        }
        // print
        cout << "After:" << endl;
        for (int a = 0; a < 5; a++)
        {
            for (int b = 0; b < 5; b++)
                cout << tR[a][b] << " ";
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
}

// Warshall algorithm