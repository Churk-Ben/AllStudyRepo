#include <stdio.h>
#include <stdlib.h>

enum {
    N = 20000
};

void swap(int order[], int a1, int a2) {
    int temp = order[a1 - 1];
    order[a1 - 1] = order[a2 - 1];
    order[a2 - 1] = temp;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char **text = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        text[i] = malloc((N + 1) * sizeof(char));
    }

    int *order = malloc(n * sizeof(int));
    int (*s)[2] = malloc(m * sizeof(*s));

    for (int i = 0; i < n; i++) {
        order[i] = i;
        scanf("%s", text[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &s[i][0], &s[i][1]);
        swap(order, s[i][0], s[i][1]);
    }
    for (int i = 0; i < n; i++) {
        printf("%s\n", text[order[i]]);
    }

    for (int i = 0; i < n; i++) {
        free(text[i]);
    }
    free(text);
    free(order);
    free(s);

    return 0;
}
