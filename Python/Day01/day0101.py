def bubble_sort(n,arr):

    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1] :
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

n=int(input())
str = input()
nums=list(map(int,str.split(" ")))
bubble_sort(n,nums)
for i in nums:
    if i==nums[-1]:
        print(i)
        break
    print(i,end=" ")
    

