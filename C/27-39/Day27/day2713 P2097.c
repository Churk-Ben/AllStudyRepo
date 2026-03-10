#include <stdio.h>

int main() {
    int ans[100];
    int a1,a2,n;
    scanf("%d%d%d",&a1,&a2,&n);
    ans[0]=a1;
    ans[1]=a2;
    int j=2;
    for(int i=0;i<10;i++){
        if (ans[i]*ans[i+1]>9)
        {
            ans[j]=(ans[i]*ans[i+1])/10;
            j++;
            ans[j]=(ans[i]*ans[i+1])%10;
            j++;
        }
        else
        {
            ans[j]=ans[i]*ans[i+1];
            j++;
        }
    }
    for(int i=0;i<n;i++){
        printf("%d ",ans[i]);
    }
    printf("\n");
    return 0;
}