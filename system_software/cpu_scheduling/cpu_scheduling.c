#include <stdio.h>
#include<stdlib.h>

typedef struct process
{
    int num;
    int burst;
    int arrival;
    int priority;
    int ta;
    int wt;
    int finished;
    int rt;
    int queueno;
} process;

process procArray[10];
int n, timeElapsed, tq;
float avgwt, avgta;

void InputProcesses()
{
    int i;

    printf("\nEnter the details for each process:\n");
    for (i = 0; i < n; i++)
    {
        procArray[i].num = i + 1;
        procArray[i].finished = 0;
        printf("\nProcess number: %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &procArray[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &procArray[i].burst);
        printf("Priority: ");
        scanf("%d", &procArray[i].priority);
        procArray[i].rt = procArray[i].burst;
    }
}

void SortArrival(int choice)
{
    int i, j, flag;
    process temp;

    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (procArray[j].arrival > procArray[j + 1].arrival)
            {
                temp = procArray[j];
                procArray[j] = procArray[j + 1];
                procArray[j + 1] = temp;
                flag = 1;
            }
            else if (procArray[j].arrival != 0 && procArray[j].arrival == procArray[j + 1].arrival && choice == 1)
            {
                if (procArray[j].burst > procArray[j + 1].burst)
                {
                    temp = procArray[j];
                    procArray[j] = procArray[j + 1];
                    procArray[j + 1] = temp;
                    flag = 1;
                }
            }
            else if (procArray[j].arrival == procArray[j + 1].arrival && choice == 2)
            {
                if (procArray[j].burst > procArray[j + 1].burst)
                {
                    temp = procArray[j];
                    procArray[j] = procArray[j + 1];
                    procArray[j + 1] = temp;
                    flag = 1;
                }
            }
            else if (procArray[j].arrival == procArray[j + 1].arrival && choice == 4)
            {
                if (procArray[j].priority > procArray[j + 1].priority)
                {
                    temp = procArray[j];
                    procArray[j] = procArray[j + 1];
                    procArray[j + 1] = temp;
                    flag = 1;
                }
            }
        }
        if (flag == 0)
            break;
    }
}

void SortNum()
{
    int i, j, flag;
    process temp;

    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (procArray[j].num > procArray[j + 1].num)
            {
                temp = procArray[j];
                procArray[j] = procArray[j + 1];
                procArray[j + 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}

void Display()
{
    int i;

    SortNum();

    printf("\nProcess No.");
    printf("\tBurst Time");
    printf("\tArrival Time");
    printf("\tWaiting Time");
    printf("\tTurnaround Time\n");

    for (i = 0; i < n; i++)
    {
        printf("   %d\t\t   ", procArray[i].num);
        printf("%d\t\t   ", procArray[i].burst);
        printf("%d\t\t  ", procArray[i].arrival);
        printf("%d\t\t   ", procArray[i].wt);
        printf("%d\n", procArray[i].ta);
    }

    printf("\nAverage Waiting Time: %0.3f", avgwt);
    printf("\nAverage Turnaround Time: %0.3f\n", avgta);
}

void FCFSwt(int index)
{
    procArray[index].wt = timeElapsed - procArray[index].arrival;
}

void FCFSta(int index)
{
    procArray[index].ta = procArray[index].burst + procArray[index].wt;
    procArray[index].finished = 1;
}

void FindAvgWtTa()
{
    int i;
    int totalwt = 0, totalta = 0;

    for (i = 0; i < n; i++)
    {
        totalwt = totalwt + procArray[i].wt;
        totalta = totalta + procArray[i].ta;
    }

    avgwt = (float)totalwt / n;
    avgta = (float)totalta / n;
}

void FCFS()
{
    int i, j, smallestArrival;

    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            procArray[i].wt = 0;
            FCFSta(i);
            timeElapsed += procArray[i].burst;
        }
        else
        {
            smallestArrival = 0;
            for (j = 1; j < n; j++)
            {
                if (procArray[j].finished == 0 && procArray[j].arrival <= timeElapsed)
                {
                    if (smallestArrival == 0)
                    {
                        smallestArrival = j;
                    }
                    else
                    {
                        if (j < smallestArrival)
                        {
                            smallestArrival = j;
                        }
                        else if (j == smallestArrival)
                        {
                            if (procArray[j].burst < procArray[smallestArrival].burst)
                            {
                                smallestArrival = j;
                            }
                        }
                    }
                }
            }
            FCFSwt(smallestArrival);
            FCFSta(smallestArrival);
            timeElapsed += procArray[smallestArrival].burst;
        }
    }
    FindAvgWtTa();
    printf("\nFCFS Scheduling Algorithm:\n");
    Display();
}

void SJFwt(int index)
{
    procArray[index].wt = timeElapsed - procArray[index].arrival;
    procArray[index].finished = 1;
}

void SJFta(int index)
{
    procArray[index].ta = procArray[index].wt + procArray[index].burst;
    procArray[index].finished = 1;
}

void SJF()
{
    int i, j, smallestBurst;

    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            procArray[i].wt = 0;
            SJFta(i);
            timeElapsed += procArray[i].burst;
        }
        else
        {
            smallestBurst = 0;
            for (j = 1; j < n; j++)
            {
                if (procArray[j].finished == 0 && procArray[j].arrival <= timeElapsed)
                {
                    if (smallestBurst == 0)
                    {
                        smallestBurst = j;
                    }
                    else
                    {
                        if (procArray[j].burst < procArray[smallestBurst].burst)
                        {
                            smallestBurst = j;
                        }
                        else if (procArray[j].burst == procArray[smallestBurst].burst)
                        {
                            if (j < smallestBurst)
                            {
                                smallestBurst = j;
                            }
                        }
                    }
                }
            }
            SJFwt(smallestBurst);
            SJFta(smallestBurst);
            timeElapsed += procArray[smallestBurst].burst;
        }
    }

    FindAvgWtTa();
    printf("\nSJF Scheduling Algorithm:\n");
    Display();
}

void Pwt(int index)
{
    procArray[index].wt = timeElapsed - procArray[index].arrival;
    procArray[index].finished = 1;
}

void Pta(int index)
{
    procArray[index].ta = procArray[index].wt + procArray[index].burst;
    procArray[index].finished = 1;
}

void Priority()
{
    int i, j, highestPriority;

    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            procArray[i].wt = 0;
            Pta(i);
            timeElapsed += procArray[i].burst;
        }
        else
        {
            highestPriority = 0;
            for (j = 1; j < n; j++)
            {
                if (procArray[j].finished == 0 && procArray[j].arrival <= timeElapsed)
                {
                    if (highestPriority == 0)
                    {
                        highestPriority = j;
                    }
                    else
                    {
                        if (procArray[j].priority < procArray[highestPriority].priority)
                        {
                            highestPriority = j;
                        }
                        else if (procArray[j].priority == procArray[highestPriority].priority)
                        {
                            if (j < highestPriority)
                            {
                                highestPriority = j;
                            }
                        }
                    }
                }
            }
            Pwt(highestPriority);
            Pta(highestPriority);
            timeElapsed += procArray[highestPriority].burst;
        }
    }

    FindAvgWtTa();
    printf("\nPriority(non-preemptive) Scheduling Algorithm:\n");
    Display();
}

int RRCompletionChecker()
{
    int i, flag = 1;

    for (i = 0; i < n; i++)
    {
        if (procArray[i].rt > 0)
        {
            flag = 0;
            break;
        }
    }

    return flag;
}

void RRtawt(int index)
{
    if (procArray[index].rt <= tq)
    {
        timeElapsed += procArray[index].rt;
        procArray[index].rt = 0;
        procArray[index].ta = timeElapsed - procArray[index].arrival;
        procArray[index].wt = procArray[index].ta - procArray[index].burst;
        procArray[index].queueno += n;
    }
    else
    {
        timeElapsed += tq;
        procArray[index].rt = procArray[index].rt - tq;
        procArray[index].queueno += n;
    }
}

void RoundRobin()
{
    int i, smallestQ, completed;

    do
    {
        smallestQ = -1;
        for (i = 0; i < n; i++)
        {
            if (procArray[i].rt != 0 && procArray[i].arrival <= timeElapsed)
            {
                if(smallestQ==-1)
                {
                    smallestQ=i;
                }
                else if(procArray[i].queueno < procArray[smallestQ].queueno)
                {
                    smallestQ = i;
                }
            }
        }
        RRtawt(smallestQ);
        completed = RRCompletionChecker();
    } while (!completed);

    FindAvgWtTa();
    printf("\nRound Robin Scheduling Algorithm:\n");
    Display();
}

void Reset()
{
    int i;

    for (i = 0; i < n; i++)
    {
        procArray[i].wt = 0;
        procArray[i].ta = 0;
        procArray[i].finished = 0;
        procArray[i].queueno = 0;
        procArray[i].rt = procArray[i].burst;
    }

    avgwt = avgta = timeElapsed = tq = 0;
}

void AssignQueueNo()
{
    int i;

    for (i = 0; i < n; i++)
    {
        procArray[i].queueno = i + 1;
    }
}

void main()
{
    int choice;
    timeElapsed = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    InputProcesses();

    while (1)
    {
        printf("\nMENU:\n");
        printf("1.FCFS(non-preemptive)\n");
        printf("2.SJF(non-preemptive)\n");
        printf("3.Round Robin(preemptive)\n");
        printf("4.Priority(non-preemptive)\n");
        printf("5.Exit\n");

        printf("\nEnter a choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            SortArrival(1);
            FCFS();
            break;

        case 2:
            SortArrival(2);
            SJF();
            break;

        case 3:
            printf("\nEnter the time quantum for the CPU: ");
            scanf("%d", &tq);
            SortArrival(1);
            AssignQueueNo();
            RoundRobin();
            break;

        case 4:
            SortArrival(4);
            Priority();
            break;

        case 5:
            exit(0);

        default:
            printf("Please enter a valid choice!\n");
            break;
        }
        Reset();
    }
}