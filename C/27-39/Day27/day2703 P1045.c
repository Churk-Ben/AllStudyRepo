#include <stdio.h>

int main() {
    int nums[10],sum=0;
    for(int i=0;i<10;i++){
        scanf("%d",&nums[i]);
        if (nums[i]%2!=0)
        {
            sum+=nums[i];
        }
    }
    printf("%d\n",sum);
    return 0;
}