#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Stores bitmask value
char bitmask[4];
// Stores the binary equivalent of the complete bitmask
char binary_mask[13];

// Finds corresponding binary equivalent of bitmask
void convert_binary(char bitmask[4])
{
    strcpy(binary_mask, "");

    for (int i = 0; i < strlen(bitmask); i++)
    {
        switch (bitmask[i])
        {
            case '0':
                strcat(binary_mask, "0000");
                break;
            case '1':
                strcat(binary_mask, "0001");
                break;
            case '2':
                strcat(binary_mask, "0010");
                break;
            case '3':
                strcat(binary_mask, "0011");
                break;
            case '4':
                strcat(binary_mask, "0100");
                break;
            case '5':
                strcat(binary_mask, "0101");
                break;
            case '6':
                strcat(binary_mask, "0110");
                break;
            case '7':
                strcat(binary_mask, "0111");
                break;
            case '8':
                strcat(binary_mask, "1000");
                break;
            case '9':
                strcat(binary_mask, "1001");
                break;
            case 'A':
                strcat(binary_mask, "1010");
                break;
            case 'B':
                strcat(binary_mask, "1011");
                break;
            case 'C':
                strcat(binary_mask, "1100");
                break;
            case 'D':
                strcat(binary_mask, "1101");
                break;
            case 'E':
                strcat(binary_mask, "1110");
                break;
            case 'F':
                strcat(binary_mask, "1111");
                break;
        }
    }
}

void main()
{
    printf("Sagar Paul\t41\n\n");

    // Stores starting address to which program is to be relocated
    int start;
    // Stores the address of text record
    int address;
    // Stores opcode read from text record
    int opcode;
    // Stores the final address after relocation
    int final_addr;
    // Stores the length of the text record
    int text_rec_len;
    // Stores starting address of record
    char rec_addr[6];
    // Stores length of record
    char length[10];
    // Stores the first column of the record (H/T/E)
    char col_one[10];
    // Stores address present in object code
    char obj_addr[10];
    // Stores the program name read from the input file
    char prog_name[10];

    FILE *fp = fopen("reloc_input.txt", "r");

    printf("Enter starting address : ");
    scanf("%x", &start);
    fscanf(fp, "%s", col_one);

    printf("\nLocation\tObject Code");

    while (strcmp(col_one, "E") != 0)
    {
        if (strcmp(col_one, "H") == 0)
        {
            fscanf(fp, "%s", prog_name);
            fscanf(fp, "%x", &rec_addr);
            fscanf(fp, "%x", &length);
            fscanf(fp, "%s", col_one);
        }

        if (strcmp(col_one, "T") == 0)
        {
            fscanf(fp, "%x", &address);
            fscanf(fp, "%x", &text_rec_len);
            fscanf(fp, "%s", bitmask);

            address += start;

            convert_binary(bitmask);

            for (int i = 0; i < 10; i++)
            {
                fscanf(fp, "%x", &opcode);
                fscanf(fp, "%s", &obj_addr);

                if (binary_mask[i] == '0')
                    final_addr = (int)strtol(obj_addr, NULL, 16);
                else
                    final_addr = (int)strtol(obj_addr, NULL, 16) + start;

                printf("\n%x\t\t%x%04x", address, opcode, final_addr);
                address += 3;

                if (obj_addr[strlen(obj_addr) - 1] == '$')
                    break;
            }

            fscanf(fp, "%s", col_one);
        }
    }
    
    fclose(fp);
}