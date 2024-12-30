#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

// �ȽϺ�����������������
int compare(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    return intervalA->start - intervalB->start;
}

// �ϲ�����ĺ���
void mergeIntervals(Interval intervals[], int n) {
    // ������ʼʱ������
    qsort(intervals, n, sizeof(Interval), compare);

    // ��źϲ��������
    Interval merged[n];
    int mergedIndex = 0;

    for (int i = 0; i < n; i++) {
        // ��� merged �ǿյĻ��ߵ�ǰ��������һ�����䲻�ص�
        if (mergedIndex == 0 || merged[mergedIndex - 1].end < intervals[i].start) {
            merged[mergedIndex++] = intervals[i]; // ���������
        } else {
            // ���ص�����ϲ�
            if (merged[mergedIndex - 1].end < intervals[i].end) {
                merged[mergedIndex - 1].end = intervals[i].end; // ���½���ʱ��
            }
        }
    }

    // ��ӡ�ϲ��������
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
