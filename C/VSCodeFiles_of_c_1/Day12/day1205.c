#include <stdio.h>

int countInversions(int arr[], int n) {
    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    int arr[] = {3, 1, 2, 5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int inversions = countInversions(arr, n);
    printf("逆序数的数量是: %d\n", inversions);
    return 0;
}
