#include <stdio.h>

int main()
{
    int n,i,j,t,bt[10],p[10];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        p[i]=i+1;
        scanf("%d",&bt[i]);
    }

    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(bt[i]>bt[j])
            {
                t=bt[i]; bt[i]=bt[j]; bt[j]=t;
                t=p[i]; p[i]=p[j]; p[j]=t;
            }

    printf("Execution Order:\n");

    for(i=0;i<n;i++)
        printf("P%d ",p[i]);

    return 0;
}