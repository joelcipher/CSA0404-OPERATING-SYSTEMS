#include <stdio.h>

int main()
{
    int n = 5, m = 3, i, j, k, count = 0;
    int alloc[5][3] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[5][3]   = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int avail[3] = {3,3,2};
    int need[5][3], done[5] = {0}, safe[5];

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (done[i]) continue;
            for (j = 0; j < m; j++)
                if (need[i][j] > avail[j]) break;
            if (j == m) {
                for (k = 0; k < m; k++) avail[k] += alloc[i][k];
                safe[count++] = i;
                done[i] = found = 1;
            }
        }
        if (!found) { printf("UNSAFE state\n"); return 0; }
    }

    printf("SAFE state. Sequence: ");
    for (i = 0; i < n; i++) printf("P%d ", safe[i]);
    printf("\n");
    return 0;
}