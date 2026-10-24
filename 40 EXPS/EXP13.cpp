#include <stdio.h>
#include <string.h>

#define MAXN 20

void allocate(int block[], int m, int proc[], int n, int type)
{
    int b[MAXN], alloc[MAXN];
    memcpy(b, block, sizeof(int) * m);

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (b[j] >= proc[i]) {
                if (type == 1) { idx = j; break; }                          /* first fit */
                if (type == 2 && (idx == -1 || b[j] < b[idx])) idx = j;     /* best fit  */
                if (type == 3 && (idx == -1 || b[j] > b[idx])) idx = j;     /* worst fit */
            }
        }
        alloc[i] = idx;
        if (idx != -1) b[idx] -= proc[i];
    }

    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", i + 1, proc[i]);
        if (alloc[i] != -1) printf("%d\n", alloc[i] + 1);
        else printf("Not allocated\n");
    }
}

int main()
{
    int block[] = {100, 500, 200, 300, 600};
    int proc[] = {212, 417, 112, 426};
    int m = 5, n = 4;

    printf("--- First Fit ---\n");  allocate(block, m, proc, n, 1);
    printf("--- Best Fit ---\n");   allocate(block, m, proc, n, 2);
    printf("--- Worst Fit ---\n");  allocate(block, m, proc, n, 3);
    return 0;
}