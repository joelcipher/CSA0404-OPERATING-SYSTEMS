#include <stdio.h>

int main()
{
    int b[] = {100, 500, 200, 300, 600}, p[] = {212, 417, 112, 426};
    int m = 5, n = 4;

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++)
            if (b[j] >= p[i]) { idx = j; break; }                        /* first hole that fits */
        if (idx != -1) { b[idx] -= p[i]; printf("P%d (%d) -> Block %d\n", i + 1, p[i], idx + 1); }
        else printf("P%d (%d) -> Not allocated\n", i + 1, p[i]);
    }
    return 0;
}