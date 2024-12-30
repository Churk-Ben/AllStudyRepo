#include <stdio.h>
#include <stdlib.h>

enum{
    N=100000
};

int main() {
    int n, m;

    scanf("%d %d", &n, &m);
    char **text = malloc(n * sizeof(char *));
    
    for (int i = 0; i < n; i++) {
        text[i] = malloc((N + 1) * sizeof(char));
    }

    int *len = malloc(n * sizeof(int));
    int *find = malloc(m * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d %s", &len[i], text[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &find[i]);
    }
    for (int i = 0; i < m; i++) {
        printf("%s\n", text[find[i] - 1]);
    }

    for (int i = 0; i < n; i++) {
        free(text[i]);
    }
    free(text);
    free(len);
    free(find);

    return 0;
}
