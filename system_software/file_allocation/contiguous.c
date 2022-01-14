#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct file
{
    char name[20];
    int no_of_blocks;
    int start;
} files[20];

// Stores number of total blocks
int total_blocks;
// Stores number of remaining blocks as they are allocated to files
int remaining_free_blocks;
// Stores the number of files
int file_count = 0;

void create_file()
{
    printf("Enter file name: ");
    scanf("%s", files[file_count].name);

    printf("Enter no. of blocks: ");
    scanf("%d", &files[file_count].no_of_blocks);

    printf("Enter starting block: ");
    scanf("%d", &files[file_count].start);

    // If nob > remaining blocks available
    if (files[file_count].no_of_blocks > remaining_free_blocks)
    {
        printf("Not enough blocks available!\n");
        files[file_count].start = -1;
        return;
    }

    for (int i = 0; i < file_count; i++)
    {
        if (files[i].start != -1)
        {
            // Check if other files have used similar starting block
            if (files[file_count].start == files[i].start)
            {
                printf("Starting block already allocated!\n");
                files[file_count].start = -1;
                return;
            }

            // Check if the blocks required by file is already allocated to any other file
            if (files[file_count].start >= files[i].start && files[file_count].start <= files[i].start + files[i].no_of_blocks - 1 || files[file_count].start + files[file_count].no_of_blocks - 1 >= files[i].start && files[file_count].start + files[file_count].no_of_blocks - 1 <= files[i].start + files[i].no_of_blocks - 1)
            {
                printf("Blocks already allocated!\n");
                files[file_count].start = -1;
                return;
            }
        }
    }

    // Check if the blocks of the file are non contiguous
    // eg: total blocks = 20; start = 17, no of blocks = 5
    if (files[file_count].start + files[file_count].no_of_blocks > total_blocks)
    {
        printf("Contiguous blocks not available!\n");
        files[file_count].start = -1;
        return;
    }

    remaining_free_blocks -= files[file_count].no_of_blocks;
}

void display()
{
    printf("\n");
    printf("%-20s%-20s%-20s\n", "Name of file", "No. of blocks", "Blocks allocated");

    for (int i = 0; i < file_count; i++)
    {
        printf("%-20s%-20d", files[i].name, files[i].no_of_blocks);

        if (files[i].start == -1)
            printf("%-20s\n", "Not allocated");
        else
        {
            for (int j = files[i].start; j < files[i].start + files[i].no_of_blocks; j++)
                printf("%d ", j);
            printf("\n");
        }
    }
}

void main()
{
    int choice;

    printf("Sagar Paul\t41\n");
    printf("Enter the total no. of blocks: ");
    scanf("%d", &total_blocks);

    remaining_free_blocks = total_blocks;

    for (int i = 0; i < 20; i++)
        files[i].start = -1;

    while (1)
    {
        printf("\nMENU:\n");
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