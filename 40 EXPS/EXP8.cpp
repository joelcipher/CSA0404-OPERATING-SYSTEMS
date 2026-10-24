#include <stdio.h>

int main()
{
    int n, i, q, time = 0, done;
    int bt[10], rem[10], wt[10] = {0}, tat[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &q);

    do
    {
        done = 1;

        for(i = 0; i < n; i++)
        {
            if(rem[i] > 0)
            {
                done = 0;

                if(rem[i] > q)
                {
                    time += q;
                    rem[i] -= q;
                }
                else
                {
                    time += rem[i];
                    wt[i] = time - bt[i];
                    rem[i] = 0;
                }
            }
        }
    } while(!done);

    printf("\nProcess\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        printf("P%d\t%d\t%d\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    return 0;
}
