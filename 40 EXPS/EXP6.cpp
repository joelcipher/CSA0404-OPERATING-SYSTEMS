#include <stdio.h>

int main()
{
    int n, i;
    int at[20], bt[20], rt[20], pr[20];
    int ct[20], tat[20], wt[20];
    int completed = 0, time = 0;
    int highest, min_priority;

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);

        rt[i] = bt[i];
    }

    while(completed < n)
    {
        highest = -1;
        min_priority = 9999;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(pr[i] < min_priority)
                {
                    min_priority = pr[i];
                    highest = i;
                }
            }
        }

        if(highest == -1)
        {
            time++;
        }
        else
        {
            rt[highest]--;
            time++;

            if(rt[highest] == 0)
            {
                ct[highest] = time;
                completed++;
            }
        }
    }

    printf("\n\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f",
           avg_tat / n);

    printf("\nAverage Waiting Time = %.2f\n",
           avg_wt / n);

    return 0;
}
