def solve(n: int):
    a, b = n ** 2, n ** 3
    # 使用set集合进行去重
    rec = set()
    # 计算当前数字的平方的各个位置上的数字
    while a > 0:
        rec.add(a % 10)
        a //= 10
    # 计算当前数字的立方的各个位置上的数字
    while b > 0:
        rec.add(b % 10)
        b //= 10
    return len(rec) == 10
 
 
if __name__ == '__main__':
    # 感觉2000的范围已经比较够了可以计算出来
    # print(1000 ** 3)
    for i in range(1, 100):
        if solve(i):
            # print(i, i ** 2, i ** 3)
            print(i)
            break