#ifndef SORTALGO_H
#define SORTALGO_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

typedef int KeyType;

struct Record
{
    KeyType key;
};

struct SortStats
{
    long long comparisons;
    long long moves;

    void reset()
    {
        comparisons = 0;
        moves = 0;
    }
};

class SortList
{
public:
    vector<Record> r;
    int length;
    SortStats stats;

    SortList(int n = 0)
    {
        length = n;
        if (n > 0)
            r.resize(n + 1);
    }

    void load(const vector<int> &data)
    {
        length = data.size();
        r.resize(length + 1);
        for (size_t i = 0; i < data.size(); ++i)
        {
            r[i + 1].key = data[i];
        }
        stats.reset();
    }

    // Comparison helpers
    bool LT(KeyType k1, KeyType k2)
    {
        stats.comparisons++;
        return k1 < k2;
    }

    bool GT(KeyType k1, KeyType k2)
    {
        stats.comparisons++;
        return k1 > k2;
    }

    bool LE(KeyType k1, KeyType k2)
    {
        stats.comparisons++;
        return k1 <= k2;
    }

    bool GE(KeyType k1, KeyType k2)
    {
        stats.comparisons++;
        return k1 >= k2;
    }

    // Move helpers
    void copyRec(Record &dest, const Record &src)
    {
        stats.moves++;
        dest = src;
    }

    void swapRec(int i, int j)
    {
        if (i == j)
            return;
        stats.moves += 3;
        std::swap(r[i], r[j]);
    }

    // 1. Direct Insertion Sort
    void InsertSort()
    {
        for (int i = 2; i <= length; ++i)
        {
            if (LT(r[i].key, r[i - 1].key))
            {
                r[0] = r[i];   // Sentinel
                stats.moves++; // Move to sentinel
                r[i] = r[i - 1];
                stats.moves++;
                int j;
                for (j = i - 2; LT(r[0].key, r[j].key); --j)
                {
                    r[j + 1] = r[j];
                    stats.moves++;
                }
                r[j + 1] = r[0];
                stats.moves++; // Move from sentinel
            }
            else
            {
                // Comparison r[i] < r[i-1] happened in if condition
            }
        }
    }

    // 2. Binary Insertion Sort
    void BinaryInsertSort()
    {
        for (int i = 2; i <= length; ++i)
        {
            r[0] = r[i]; // Sentinel
            stats.moves++;

            int low = 1;
            int high = i - 1;
            while (low <= high)
            {
                int m = (low + high) / 2;
                if (LT(r[0].key, r[m].key))
                {
                    high = m - 1;
                }
                else
                {
                    low = m + 1;
                }
            }

            for (int j = i - 1; j >= high + 1; --j)
            {
                r[j + 1] = r[j];
                stats.moves++;
            }
            r[high + 1] = r[0];
            stats.moves++;
        }
    }

    // 3. Two-Way Insertion Sort
    void TwoWayInsertSort()
    {
        vector<Record> d(length);
        d[0] = r[1];
        stats.moves++;

        int first = 0;
        int final = 0;

        for (int i = 2; i <= length; ++i)
        {
            if (LT(r[i].key, d[first].key))
            { // Smaller than min
                first = (first - 1 + length) % length;
                d[first] = r[i];
                stats.moves++;
            }
            else if (GT(r[i].key, d[final].key))
            { // Larger than max
                final = (final + 1) % length;
                d[final] = r[i];
                stats.moves++;
            }
            else
            { // Middle
                int k = final;
                while (LT(r[i].key, d[k].key))
                {
                    d[(k + 1) % length] = d[k];
                    stats.moves++;
                    k = (k - 1 + length) % length;
                }
                d[(k + 1) % length] = r[i];
                stats.moves++;
                final = (final + 1) % length;
            }
        }

        // Copy back
        for (int i = 0; i < length; ++i)
        {
            r[i + 1] = d[(first + i) % length];
            stats.moves++;
        }
    }

    // 4. Shell Sort
    void ShellInsert(int dk)
    {
        for (int i = dk + 1; i <= length; ++i)
        {
            if (LT(r[i].key, r[i - dk].key))
            {
                r[0] = r[i];
                stats.moves++;
                int j;
                for (j = i - dk; j > 0 && LT(r[0].key, r[j].key); j -= dk)
                {
                    r[j + dk] = r[j];
                    stats.moves++;
                }
                r[j + dk] = r[0];
                stats.moves++;
            }
            else
            {
                // Comparison in if
            }
        }
    }

    void ShellSort()
    {
        int dlta[] = {5, 3, 1}; // Example increments
        for (int k = 0; k < 3; ++k)
        {
            ShellInsert(dlta[k]);
        }
    }

    // 5. Bubble Sort
    void BubbleSort()
    {
        bool change = true;
        for (int i = length; i > 1 && change; --i)
        {
            change = false;
            for (int j = 1; j < i; ++j)
            {
                if (GT(r[j].key, r[j + 1].key))
                {
                    swapRec(j, j + 1);
                    change = true;
                }
            }
        }
    }

    // 6. Quick Sort
    int Partition(int low, int high)
    {
        r[0] = r[low];
        stats.moves++;
        KeyType pivotkey = r[low].key;

        while (low < high)
        {
            while (low < high && GE(r[high].key, pivotkey))
                --high;
            r[low] = r[high];
            stats.moves++;

            while (low < high && LE(r[low].key, pivotkey))
                ++low;
            r[high] = r[low];
            stats.moves++;
        }
        r[low] = r[0];
        stats.moves++;
        return low;
    }

    void QSort(int low, int high)
    {
        if (low < high)
        {
            int pivotloc = Partition(low, high);
            QSort(low, pivotloc - 1);
            QSort(pivotloc + 1, high);
        }
    }

    void QuickSort()
    {
        QSort(1, length);
    }

    // 7. Simple Selection Sort
    void SelectSort()
    {
        for (int i = 1; i < length; ++i)
        {
            int k = i;
            for (int j = i + 1; j <= length; ++j)
            {
                if (LT(r[j].key, r[k].key))
                    k = j;
            }
            if (k != i)
            {
                swapRec(i, k);
            }
        }
    }

    // 8. Heap Sort
    void HeapAdjust(int s, int m)
    {
        Record rc = r[s];
        stats.moves++;
        for (int j = 2 * s; j <= m; j *= 2)
        {
            if (j < m && LT(r[j].key, r[j + 1].key))
                ++j;
            if (!LT(rc.key, r[j].key))
                break;
            r[s] = r[j];
            stats.moves++;
            s = j;
        }
        r[s] = rc;
        stats.moves++;
    }

    void HeapSort()
    {
        for (int i = length / 2; i > 0; --i)
        {
            HeapAdjust(i, length);
        }
        for (int i = length; i > 1; --i)
        {
            swapRec(1, i);
            HeapAdjust(1, i - 1);
        }
    }

    // 9. Merge Sort
    void Merge(vector<Record> &SR, vector<Record> &TR, int i, int m, int n)
    {
        int j, k;
        for (j = m + 1, k = i; i <= m && j <= n; ++k)
        {
            if (LE(SR[i].key, SR[j].key))
            {
                TR[k] = SR[i++];
            }
            else
            {
                TR[k] = SR[j++];
            }
            stats.moves++; // Move to TR
        }
        if (i <= m)
        {
            while (i <= m)
            {
                TR[k++] = SR[i++];
                stats.moves++;
            }
        }
        if (j <= n)
        {
            while (j <= n)
            {
                TR[k++] = SR[j++];
                stats.moves++;
            }
        }
    }

    void MSort(vector<Record> &SR, vector<Record> &TR1, int s, int t)
    {
        if (s == t)
        {
            TR1[s] = SR[s];
            stats.moves++;
        }
        else
        {
            int m = (s + t) / 2;
            vector<Record> TR2(length + 1); // Aux array
            MSort(SR, TR2, s, m);
            MSort(SR, TR2, m + 1, t);
            Merge(TR2, TR1, s, m, t);
        }
    }

    void MergeSort()
    {
        MSort(r, r, 1, length);
    }

    // 10. Radix Sort
    // Assuming positive integers for simplicity
    int GetDigit(int num, int d)
    {
        // d=1 means LSD
        int p = 1;
        for (int i = 1; i < d; ++i)
            p *= 10;
        return (num / p) % 10;
    }

    int MaxBits()
    {
        KeyType maxK = 0;
        for (int i = 1; i <= length; ++i)
        {
            if (r[i].key > maxK)
                maxK = r[i].key;
        }
        int d = 1;
        while (maxK >= 10)
        {
            maxK /= 10;
            d++;
        }
        return d;
    }

    void RadixSort()
    {
        int d = MaxBits();
        int n = length;

        // Buckets (queues)
        vector<queue<Record>> buckets(10);

        for (int k = 1; k <= d; ++k)
        {
            // Distribute
            for (int i = 1; i <= n; ++i)
            {
                int digit = GetDigit(r[i].key, k);
                buckets[digit].push(r[i]);
                stats.moves++; // Move to bucket
            }

            // Collect
            int idx = 1;
            for (int j = 0; j < 10; ++j)
            {
                while (!buckets[j].empty())
                {
                    r[idx++] = buckets[j].front();
                    buckets[j].pop();
                    stats.moves++; // Move back to list
                }
            }
        }
    }
};

#endif
