def C(n, m):
    if m == 0 or m == n:
        return 1
    else:
        return C(n-1, m) + C(n-1, m-1)

def main():
    n = int(input())
    ans=[]
    for i in range(n+1):
        ans.append(C(n, i))

    print(" ".join(map(str,ans)))

if __name__ == '__main__':
    main()