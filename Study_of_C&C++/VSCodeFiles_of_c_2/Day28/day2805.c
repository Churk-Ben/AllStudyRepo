#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

// 比较函数，用于排序区间
int compare(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    return intervalA->start - intervalB->start;
}

// 合并区间的函数
void mergeIntervals(Interval intervals[], int n) {
    // 按照起始时间排序
    qsort(intervals, n, sizeof(Interval), compare);

    // 存放合并后的区间
    Interval merged[n];
    int mergedIndex = 0;

    for (int i = 0; i < n; i++) {
        // 如果 merged 是空的或者当前区间与上一个区间不重叠
        if (mergedIndex == 0 || merged[mergedIndex - 1].end < intervals[i].start) {
            merged[mergedIndex++] = intervals[i]; // 添加新区间
        } else {
            // 有重叠，则合并
            if (merged[mergedIndex - 1].end < intervals[i].end) {
                merged[mergedIndex - 1].end = intervals[i].end; // 更新结束时间
            }
        }
    }

    // 打印合并后的区间
    printf("Merged Intervals:\n");
    for (int i = 0; i < mergedIndex; i++) {
        printf("[%d, %d]\n", merged[i].start, merged[i].end);
    }
}

int main() {
    int n;
    printf("Enter the number of intervals: ");
    scanf("%d", &n);

    Interval intervals[n];
    printf("Enter the intervals (start and end):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    mergeIntervals(intervals, n);

    return 0;
}
