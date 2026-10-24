#include <stdio.h>

int main()
{
    char line[100];
    FILE *fp = fopen("a.txt", "w");          /* create + write */
    fprintf(fp, "Hello\n");
    fclose(fp);

    fp = fopen("a.txt", "a");                /* append */
    fprintf(fp, "World\n");
    fclose(fp);

    fp = fopen("a.txt", "r");                /* read */
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);
    fclose(fp);

    rename("a.txt", "b.txt");                /* rename */
    remove("b.txt");                         /* delete */
    printf("Done\n");
    return 0;
}