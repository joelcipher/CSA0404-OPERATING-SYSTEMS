#include <stdio.h>

int main()
{
    FILE *f1, *f2;
    char c;

    f1 = fopen("C:/Users/anlom/OneDrive/Desktop/source.txt", "r");
    f2 = fopen("C:/Users/anlom/OneDrive/Desktop/destination.txt", "w");

    c = fgetc(f1);

    while(c != EOF)
    {
        fputc(c, f2);
        c = fgetc(f1);
    }

    fclose(f1);
    fclose(f2);

    printf("File copied successfully");

    return 0;
}
