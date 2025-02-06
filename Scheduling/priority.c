#include<stdio.h>
#include<string.h>

struct process
{
    char name[10];
    int at, bt, ct, tat, wt, priority;
} p[20], temp;

void main() {
    int i, j, n, time = 0, completed = 0;
    float avgwt = 0, avgtat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter the details of process %d\n", i + 1);
        printf("Process name: ");
        scanf("%s", p[i].name);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);
    }

    // Sort processes by arrival time (to handle processes arriving at the same time)
    for(i = 0; i < n; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Priority Scheduling
    while(completed < n) {
        int highest_priority = -1;
        int index = -1;

        // Find the process with the highest priority that has arrived and not completed
        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].ct == 0) { // Process has arrived and not completed
                if(highest_priority == -1 || p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    index = i;
                }
            }
        }

        if(index == -1) {
            // No process is available to execute, increment time
            time++;
        } else {
            // Execute the process with the highest priority
            time += p[index].bt;
            p[index].ct = time; // Completion time
            p[index].tat = p[index].ct - p[index].at; // Turnaround time
            p[index].wt = p[index].tat - p[index].bt; // Waiting time
            avgtat += p[index].tat;
            avgwt += p[index].wt;
            completed++;
        }
    }

    // Output results
    printf("\nPid\tA.T\tB.T\tPriority\tC.T\tT.A.T\tW.T\n");
    for(i = 0; i < n; i++) {
        printf(" %s\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\n\nAverage waiting time: %.2f", (avgwt / n));
    printf("\nAverage turnaround time: %.2f\n", (avgtat / n));
}
