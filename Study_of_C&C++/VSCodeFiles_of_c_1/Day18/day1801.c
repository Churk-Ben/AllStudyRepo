#include <stdio.h>

inline long long read(){    //¿ì¶Á
    long long s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9'){
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9'){
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}

int main(){
    long long n = read();
    printf("%lld\n", n);
    return 0;
}