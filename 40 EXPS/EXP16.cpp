#include <stdio.h>

struct emp { int id; char name[20]; float sal; };

int main()
{
    struct emp e;
    int n, pos;
    FILE *fp = fopen("emp.dat", "wb+");

    printf("How many employees? ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter id name salary: ");
        scanf("%d %s %f", &e.id, e.name, &e.sal);
        fwrite(&e, sizeof(e), 1, fp);
    }

    printf("Record number to read: ");
    scanf("%d", &pos);
    fseek(fp, (pos - 1) * sizeof(e), SEEK_SET);   /* jump straight to the record */
    if (fread(&e, sizeof(e), 1, fp) == 1)
        printf("%d %s %.2f\n", e.id, e.name, e.sal);
    else
        printf("Record not found\n");

    fclose(fp);
    return 0;
}