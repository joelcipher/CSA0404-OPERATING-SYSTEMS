#include <stdio.h>
#include <string.h>

int main()
{
    char files[20][20], name[20];
    int n = 0, ch, i;

    while (1) {
        printf("\n1.Create 2.Delete 3.Search 4.Display 5.Exit: ");
        scanf("%d", &ch);
        if (ch == 5) break;

        if (ch == 1) {
            printf("File name: ");
            scanf("%s", files[n++]);
        } else if (ch == 4) {
            for (i = 0; i < n; i++) printf("%s\n", files[i]);
        } else {
            printf("File name: ");
            scanf("%s", name);
            for (i = 0; i < n; i++)
                if (strcmp(name, files[i]) == 0) break;
            if (i == n) printf("Not found\n");
            else if (ch == 3) printf("Found\n");
            else { strcpy(files[i], files[--n]); printf("Deleted\n"); }
        }
    }
    return 0;
}