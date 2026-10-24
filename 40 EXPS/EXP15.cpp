#include <stdio.h>
#include <string.h>

struct { char name[20]; char files[10][20]; int n; } dir[10];

int main()
{
    int nd = 0, ch, i, j;
    char d[20], f[20];

    while (1) {
        printf("\n1.Create Dir 2.Create File 3.Search File 4.Display 5.Exit: ");
        scanf("%d", &ch);
        if (ch == 5) break;

        if (ch == 1) {
            printf("Dir name: ");
            scanf("%s", dir[nd].name);
            dir[nd++].n = 0;
        } else if (ch == 4) {
            for (i = 0; i < nd; i++) {
                printf("%s:", dir[i].name);
                for (j = 0; j < dir[i].n; j++) printf(" %s", dir[i].files[j]);
                printf("\n");
            }
        } else {
            printf("Dir name: ");
            scanf("%s", d);
            for (i = 0; i < nd; i++)
                if (strcmp(d, dir[i].name) == 0) break;
            if (i == nd) { printf("Dir not found\n"); continue; }

            printf("File name: ");
            scanf("%s", f);
            if (ch == 2)
                strcpy(dir[i].files[dir[i].n++], f);
            else {
                for (j = 0; j < dir[i].n; j++)
                    if (strcmp(f, dir[i].files[j]) == 0) break;
                printf(j < dir[i].n ? "Found\n" : "Not found\n");
            }
        }
    }
    return 0;
}