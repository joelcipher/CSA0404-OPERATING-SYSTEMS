#include <stdio.h>

int main()
{
    int n,i,j,t,p[10],pri[10];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        p[i]=i+1;
        scanf("%d",&pri[i]);
    }

    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(pri[i]>pri[j])
            {
                t=pri[i]; pri[i]=pri[j]; pri[j]=t;
                t=p[i]; p[i]=p[j]; p[j]=t;
            }

    printf("Execution Order:\n");

    for(i=0;i<n;i++)
        printf("P%d ",p[i]);

    return 0;
}