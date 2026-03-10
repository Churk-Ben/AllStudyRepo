#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
自定义排序算法实现

本模块实现了不使用Python内置sorted()函数的自定义排序算法。
支持对元组列表进行多键排序：第一个元素降序，第二、三个元素升序。

作者：Python学习者
版本：1.0
兼容性：Python 2.7+ / Python 3.x，支持Windows/Linux/macOS
"""


def compare_tuples(tuple1, tuple2):
    """
    自定义比较函数：比较两个元组
    排序规则：第一个元素降序，第二、三个元素升序

    参数：
        tuple1 (tuple): 第一个待比较的元组
        tuple2 (tuple): 第二个待比较的元组

    返回值：
        int: -1 表示 tuple1 < tuple2 (tuple1应该排在前面)
             0  表示 tuple1 == tuple2 (相等)
             1  表示 tuple1 > tuple2 (tuple2应该排在前面)

    注意：
        此函数兼容所有Python版本和操作系统
    """
    # 比较第一个元素（降序）
    if tuple1[0] > tuple2[0]:
        return -1
    elif tuple1[0] < tuple2[0]:
        return 1

    # 第一个元素相等，比较第二个元素（升序）
    if tuple1[1] < tuple2[1]:
        return -1
    elif tuple1[1] > tuple2[1]:
        return 1

    # 前两个元素都相等，比较第三个元素（升序）
    if tuple1[2] < tuple2[2]:
        return -1
    elif tuple1[2] > tuple2[2]:
        return 1

    # 完全相等
    return 0


def quick_sort(arr, compare_func):
    """
    快速排序算法实现

    参数：
        arr (list): 待排序的列表
        compare_func (function): 比较函数，接受两个参数并返回比较结果

    返回值：
        list: 排序后的新列表（不修改原列表）

    时间复杂度：
        平均情况：O(n log n)
        最坏情况：O(n²)

    空间复杂度：O(log n)

    注意：
        此实现兼容Python 2.7+和Python 3.x，支持Windows/Linux/macOS
    """
    if len(arr) <= 1:
        return arr.copy()

    # 选择中间元素作为基准
    pivot_index = len(arr) // 2
    pivot = arr[pivot_index]

    # 分割数组
    left = []
    right = []
    equal = []

    for item in arr:
        comparison = compare_func(item, pivot)
        if comparison < 0:
            left.append(item)
        elif comparison > 0:
            right.append(item)
        else:
            equal.append(item)

    # 递归排序并合并结果
    return quick_sort(left, compare_func) + equal + quick_sort(right, compare_func)


def sort_tuples(tuple_list):
    """
    使用自定义排序算法对元组列表进行排序
    排序规则：第一个元素降序，第二、三个元素升序

    参数：
        tuple_list (list): 包含元组的列表

    返回值：
        list: 排序后的新列表（不修改原列表）

    示例：
        >>> test_list = [(15, 2, 3), (14, 3, 3), (8, 2, 2)]
        >>> result = sort_tuples(test_list)
        >>> print(result)
        [(15, 2, 3), (14, 3, 3), (8, 2, 2)]

    注意：
        - 不使用Python内置的sorted()函数
        - 使用自实现的快速排序算法
        - 兼容所有主流操作系统和Python版本
    """
    if not tuple_list:
        return []

    return quick_sort(tuple_list, compare_tuples)


def merge_sort(arr, compare_func):
    """
    归并排序算法实现（备选方案）

    参数：
    arr: 待排序的列表
    compare_func: 比较函数

    返回：
    排序后的新列表
    """
    if len(arr) <= 1:
        return arr.copy()

    # 分割数组
    mid = len(arr) // 2
    left = merge_sort(arr[:mid], compare_func)
    right = merge_sort(arr[mid:], compare_func)

    # 合并已排序的数组
    result = []
    i = j = 0

    while i < len(left) and j < len(right):
        if compare_func(left[i], right[j]) <= 0:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    # 添加剩余元素
    result.extend(left[i:])
    result.extend(right[j:])

    return result


def sort_tuples_merge(tuple_list):
    """
    使用归并排序算法对元组列表进行排序
    排序规则：第一个元素降序，第二、三个元素升序

    参数：
    tuple_list: 包含元组的列表

    返回：
    排序后的新列表
    """
    if not tuple_list:
        return []

    return merge_sort(tuple_list, compare_tuples)


# 测试函数
if __name__ == "__main__":
    # 测试数据
    test_list = [(15, 2, 3), (14, 3, 3), (8, 2, 2)]

    print("原始列表:", test_list)

    # 使用快速排序
    result_quick = sort_tuples(test_list)
    print("快速排序结果:", result_quick)

    # 使用归并排序
    result_merge = sort_tuples_merge(test_list)
    print("归并排序结果:", result_merge)

    # 更复杂的测试用例
    complex_test = [
        (10, 5, 1),
        (15, 2, 3),
        (10, 3, 2),
        (15, 2, 1),
        (8, 2, 2),
        (10, 3, 1),
    ]
    print("\n复杂测试列表:", complex_test)

    result_complex = sort_tuples(complex_test)
    print("复杂测试排序结果:", result_complex)

    # 验证排序正确性
    print("\n验证排序正确性:")
    for i in range(len(result_complex) - 1):
        current = result_complex[i]
        next_item = result_complex[i + 1]
        comparison = compare_tuples(current, next_item)
        print(f"{current} vs {next_item}: {comparison <= 0}")  # 应该都是True
