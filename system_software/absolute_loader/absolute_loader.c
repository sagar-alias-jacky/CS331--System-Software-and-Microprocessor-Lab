#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    printf("Sagar Paul\t41\n\n");

    FILE *file;
    int i, j; 
    // Stores the starting address of each byte of object code
    int start_addr;
    // Stores the program name entered by the user
    char name[10];
    // Stores each line of object file
    char line[50];
    // Stores the address read from object file
    char temp[10];

    file = fopen("objectcode.txt", "r");
    fscanf(file, "%s", line);

    printf("Enter program name: ");
    scanf("%s", name);

    // Check if name of program matches with name in object file
    for (i = 2, j = 0; i < 8, j < strlen(name); i++, j++)
    {
        if (name[j] != line[i])
        {
            printf("Invalid program name.\n");
            return;
        }
    }

    printf("\nLocation\tObject code\n");
    do
    {
        fscanf(file, "%s", line);

        // If text record
        if (line[0] == 'T')
        {
            // Read starting address of object code
            for (i = 2, j = 0; i < 8, j < 6; i++, j++)
                temp[j] = line[i];
            temp[j] = '\0';

            start_addr = atoi(temp);

            // Move to column 12 (Starting of object codes)
            i = 12;

            // Read each byte of object code and print it
            while (line[i] != '$')
            {
                if (line[i] != '^')
                {
                    printf("00%d\t\t%c%c\n", start_addr, line[i], line[i + 1]);
                    start_addr++;
                    i += 2;
                }
                else
                    i++;
            }
        }

        // If end record
        if (line[0] == 'E')
        {
            printf("\nExecution address: ");
            for (i = 2; i < 8; i++)
                printf("%c", line[i]);
            break;
        }
    } while (!feof(file));

    fclose(file);
}
