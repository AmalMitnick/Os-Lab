#include<stdio.h>
#include<string.h>

struct process
{
    char name[10];
    int at, bt, ct, tat, wt;
} p[20], temp;

void main()
{
    int i, j, n, time = 0;
    float avgwt = 0, avgtat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++)
    {
        printf("Enter the details of process %d\n", i + 1);
        printf("Process name: ");
        scanf("%s", p[i].name);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
    }

    // Sort processes by arrival time
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // SJF Scheduling
    for (i = 0; i < n; i++)
    {
        // Find the process with the shortest burst time among the arrived processes
        int shortest = i;
        for (j = i + 1; j < n; j++)
        {
            if (p[j].at <= time && p[j].bt < p[shortest].bt)
            {
                shortest = j;
            }
        }

        // Swap the shortest process with the current process
        if (shortest != i)
        {
            temp = p[i];
            p[i] = p[shortest];
            p[shortest] = temp;
        }

        // If the current process arrives after the completion of the previous process
        if (time < p[i].at)
        {
            time = p[i].at;
        }

        // Calculate completion time, turnaround time, and waiting time
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        // Update the current time
        time += p[i].bt;

        // Update sums for average calculation
        avgtat += p[i].tat;
        avgwt += p[i].wt;
    }

    // Display the results
    printf("\nPid\tA.T\tB.T\tC.T\tT.A.T\tW.T\n");
    for (i = 0; i < n; i++)
    {
        printf(" %s\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Calculate and display average waiting time and turnaround time
    printf("\n\nAverage waiting time: %.2f", (avgwt / n));
    printf("\nAverage turnaround time: %.2f\n", (avgtat / n));
}
