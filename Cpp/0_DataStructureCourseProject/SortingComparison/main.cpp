#include "SortAlgo.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

void RunTest(int n)
{
    cout << "\n------------------------------------------------------------\n";
    cout << "Testing with List Length: " << n << endl;
    cout << "------------------------------------------------------------\n";

    // Generate Random Data
    vector<int> data(n);
    for (int i = 0; i < n; ++i)
    {
        data[i] = rand() % 10000; // Random numbers 0-9999
    }

    SortList sl;
    string algoNames[] = {
        "Direct Insert", "Binary Insert", "Two-Way Insert", "Shell Sort   ",
        "Bubble Sort  ", "Quick Sort   ", "Select Sort  ", "Heap Sort    ",
        "Merge Sort   ", "Radix Sort   "};

    cout << left << setw(20) << "Algorithm" << setw(15) << "Comparisons" << setw(15) << "Moves" << endl;
    cout << "------------------------------------------------------------\n";

    // 1. Direct Insert
    sl.load(data);
    sl.InsertSort();
    cout << left << setw(20) << algoNames[0] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 2. Binary Insert
    sl.load(data);
    sl.BinaryInsertSort();
    cout << left << setw(20) << algoNames[1] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 3. Two-Way Insert
    sl.load(data);
    sl.TwoWayInsertSort();
    cout << left << setw(20) << algoNames[2] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 4. Shell Sort
    sl.load(data);
    sl.ShellSort();
    cout << left << setw(20) << algoNames[3] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 5. Bubble Sort
    sl.load(data);
    sl.BubbleSort();
    cout << left << setw(20) << algoNames[4] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 6. Quick Sort
    sl.load(data);
    sl.QuickSort();
    cout << left << setw(20) << algoNames[5] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 7. Select Sort
    sl.load(data);
    sl.SelectSort();
    cout << left << setw(20) << algoNames[6] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 8. Heap Sort
    sl.load(data);
    sl.HeapSort();
    cout << left << setw(20) << algoNames[7] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 9. Merge Sort
    sl.load(data);
    sl.MergeSort();
    cout << left << setw(20) << algoNames[8] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;

    // 10. Radix Sort
    sl.load(data);
    sl.RadixSort();
    cout << left << setw(20) << algoNames[9] << setw(15) << sl.stats.comparisons << setw(15) << sl.stats.moves << endl;
}

int main()
{
    srand(time(0));

    int lengths[] = {100, 200, 500, 1000, 2000};
    for (int i = 0; i < 5; ++i)
    {
        RunTest(lengths[i]);
    }

    return 0;
}
