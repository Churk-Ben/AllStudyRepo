#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    while (n--)
    {
        vector<int> boxes(6); // 存储各尺寸盒子数量
        for (int i = 0; i < 6; ++i)
        {
            cin >> boxes[i];
        }

        int container_count = 0;

        // 处理6x6盒子
        container_count += boxes[5];
        boxes[5] = 0;

        // 处理5x5盒子
        container_count += boxes[4];
        int remaining_space = boxes[4] * 11;
        boxes[0] = max(boxes[0] - remaining_space, 0);
        boxes[4] = 0;

        // 处理4x4盒子
        container_count += boxes[3];
        remaining_space = boxes[3] * 5;
        if (boxes[1] >= remaining_space)
        {
            boxes[1] -= remaining_space;
        }
        else
        {
            remaining_space = (remaining_space - boxes[1]) * 4;
            boxes[1] = 0;
            boxes[0] = max(boxes[0] - remaining_space, 0);
        }
        boxes[3] = 0;

        // 处理3x3盒子
        container_count += (boxes[2] + 3) / 4;
        int remaining_3x3 = boxes[2] % 4;
        boxes[2] = 0;

        if (remaining_3x3 > 0)
        {
            int space_for_2x2 = 7 - 2 * remaining_3x3;
            int space_for_1x1 = 8 - remaining_3x3;

            if (boxes[1] >= space_for_2x2)
            {
                boxes[1] -= space_for_2x2;
                boxes[0] = max(boxes[0] - space_for_1x1, 0);
            }
            else
            {
                space_for_1x1 += (space_for_2x2 - boxes[1]) * 4;
                boxes[1] = 0;
                boxes[0] = max(boxes[0] - space_for_1x1, 0);
            }
        }

        // 处理2x2盒子
        container_count += (boxes[1] + 8) / 9;
        int remaining_2x2 = boxes[1] % 9;
        boxes[1] = 0;

        if (remaining_2x2 > 0)
        {
            boxes[0] = max(boxes[0] - (36 - remaining_2x2 * 4), 0);
        }

        // 处理1x1盒子
        container_count += (boxes[0] + 35) / 36;

        cout << container_count << endl;
    }
    return 0;
}
