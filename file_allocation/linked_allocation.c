#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct file
{
    char name[20];
    int no_of_blocks;
    int blocks[20];
} files[20];

int total_blocks;
int remaining_free_blocks;
int file_count = 0;
int avail_blcks[500];

void create_file()
{
    int rand_arr_index, item;

    printf("Enter file name: ");
    scanf("%s", files[file_count].name);

    printf("Enter no. of blocks: ");
    scanf("%d", &files[file_count].no_of_blocks);

    // If nob > remaining blocks available
    if (files[file_count].no_of_blocks > remaining_free_blocks)
    {
        printf("Not enough blocks available!\n");
        return;
    }
    else
    {
        for (int i = 0; i < files[file_count].no_of_blocks; i++)
        {
            // Generate a random index and use this index to select a block number from avail_blcks[]
            rand_arr_index = rand() % remaining_free_blocks;
            item = avail_blcks[rand_arr_index];
            // The chosen block number is set to -1 in avail_blcks[] so that it is not chosen again
            avail_blcks[rand_arr_index] = -1;

            // Sorting avail_blcks[] (descending) so that -1 is not chosen in next file creation
            for (int a = 0; a < remaining_free_blocks; a++)
            {
                for (int b = a + 1; b < remaining_free_blocks; b++)
                {
                    if (avail_blcks[a] < avail_blcks[b])
                    {
                        int temp = avail_blcks[a];
                        avail_blcks[a] = avail_blcks[b];
                        avail_blcks[b] = temp;
                    }
                }
            }

            files[file_count].blocks[i] = item;
            remaining_free_blocks--;
        }
    }
}

void display()
{
    printf("\n");
    printf("%-20s%-20s%-20s\n", "Name of file", "No. of blocks", "Blocks allocated");

    for (int i = 0; i < file_count; i++)
    {
        printf("%-20s%-20d", files[i].name, files[i].no_of_blocks);

        if (files[i].blocks[0] == -1)
            printf("%-20s\n", "Not allocated");
        else
        {
            for (int j = 0; j < files[i].no_of_blocks; j++)
                printf("%d ", files[i].blocks[j]);
            printf("\n");
        }
    }

    printf("Remaining blocks: %d\n", remaining_free_blocks);
}

void main()
{
    int choice;

    srand(time(NULL));

    printf("Sagar Paul\t41\n");
    printf("Enter total no. of blocks: ");
    scanf("%d", &total_blocks);

    remaining_free_blocks = total_blocks;

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            files[i].blocks[j] = -1;

    // Generating block numbers which is used for random selection (contains total blocks - 1, total blocks - 2, ..., 2, 1, 0)
    for (int i = total_blocks - 1; i >= 0; i--)
        avail_blcks[i] = i;

    while (1)
    {
        printf("\nMENU\n");
        printf("1. Create file\n2. Display file allocation details\n3. Exit\nEnter a choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_file();
            file_count++;
            display();
            break;
        case 2:
            display();
            break;
        case 3:
            exit(0);
        default:
            printf("\nPlease enter a valid choice!\n");
        }
    }
}