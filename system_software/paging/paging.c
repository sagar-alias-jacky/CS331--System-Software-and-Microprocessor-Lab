#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct process
{
    int pid;
    int size;
};

// Processes
struct process procs[20];
// Content of each index represents a frame that is allocated to a process. PID is stored in the index
int frames[500];
// Stores size of memory in KB
int mem_size;
// Stores size of each frame in KB
int frame_size;
// Stores total frames available in memory
int tot_frames;
// Stores the remaining frames
int remain_frames;
// Stores total internal fragmentation in KB
int tot_int_frag = 0;
// Stores no. of processes
int proc_count = 0;

void create()
{
    int proc_id, proc_size, count, rand_frame, no_of_frames;

    if (remain_frames == 0)
    {
        printf("Not enough frames available!\n");
        return;
    }

    printf("Enter process ID: ");
    scanf("%d", &proc_id);

    printf("Enter size of process P%d: ", proc_id);
    scanf("%d", &proc_size);

    if (proc_size % frame_size == 0)
    {
        no_of_frames = proc_size / frame_size;
        procs[proc_count].pid = proc_id;
        procs[proc_count].size = proc_size;
    }
    else
    {
        no_of_frames = proc_size / frame_size + 1;

        if (no_of_frames > remain_frames)
        {
            printf("Not enough frames available to allocate P%d!\n", proc_id);
            return;
        }

        procs[proc_count].pid = proc_id;
        procs[proc_count].size = proc_size;
        tot_int_frag += frame_size - (proc_size % frame_size);
    }

    printf("No. of frames required for P%d: %d\n", procs[proc_count].pid, no_of_frames);

    count = 0;

    do
    {
        // Choose random frame
        rand_frame = rand() % tot_frames;

        // Check availability of frame
        if (frames[rand_frame] == -1)
        {
            frames[rand_frame] = procs[proc_count].pid;
            count++;
            remain_frames--;
        }
    } while (count < no_of_frames);

    proc_count++;
}

void delete ()
{
    int i, val, flag;

    printf("Enter process ID to delete: ");
    scanf("%d", &val);

    flag = 0;

    for (i = 0; i < proc_count; i++)
    {
        if (procs[i].pid == val)
        {
            flag = 1;
            // Deleting process by making its ID 0
            procs[i].pid = -1;
            break;
        }
    }

    if (flag == 0)
    {
        printf("Process not found!\n");
        return;
    }

    // Decreasing internal fragmentation value if process does not completely fit in a frame
    if (procs[i].size % frame_size != 0)
    {
        remain_frames += procs[i].size / frame_size + 1;
        tot_int_frag -= frame_size - (procs[i].size % frame_size);
    }
    else
        remain_frames += procs[i].size % frame_size;

    for (i = 0; i < tot_frames; i++)
    {
        if (frames[i] == val)
            frames[i] = -1;
    }
}

void display()
{
    printf("\n%-20s%-20s%-20s\n", "Process", "Size (KB)", "Frames");

    for (int i = 0; i < proc_count; i++)
    {
        if (procs[i].pid != -1)
        {
            printf("P%-20d%-20d", procs[i].pid, procs[i].size);

            for (int j = 0; j < tot_frames; j++)
            {
                if (frames[j] == procs[i].pid)
                    printf("%d ", j);
            }

            printf("\n");
        }
    }

    printf("Remaining frames: %d\n", remain_frames);
    printf("Total internal fragmentation: %d KB\n", tot_int_frag);
}

void main()
{
    int choice;
    srand(time(NULL));
    printf("Sagar Paul\t41\n");

    printf("Enter memory size: ");
    scanf("%d", &mem_size);

    printf("Enter frame size: ");
    scanf("%d", &frame_size);

    tot_frames = mem_size / frame_size;
    remain_frames = tot_frames;
    printf("Total frames: %d\n", tot_frames);

    // Unallocated frames are set as -1
    for (int i = 0; i < 500; i++)
        frames[i] = -1;

    while (1)
    {
        printf("\n\tMENU\n");
        printf("1. Insert process\n2. Delete process\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create();
            display();
            break;
        case 2:
            delete ();
            display();
            break;
        case 3:
            exit(0);
        }
    }
}