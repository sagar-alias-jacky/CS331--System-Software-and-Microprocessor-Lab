#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    printf("Sagar Paul\t41\n\n");
    // Stores starting address of program
    int start_addr;
    // Location counter
    int locctr;
    // Stores the length of the instruction
    int length;
    // Stores the label received from input file
    char label[20];
    // Stores the opcode received from input file
    char opcode[20];
    // Stores operand received from input file
    char operand[20];
    // File pointers to input program, optab, symtab, intermediate file, and length file
    FILE *input_ptr, *optab_ptr, *symtab_ptr, *intermed_ptr, *length_ptr;
    // Open input and output files
    input_ptr = fopen("input.txt", "r");
    symtab_ptr = fopen("symtab.txt", "w");
    intermed_ptr = fopen("intermediate.txt", "w");
    length_ptr = fopen("length.txt", "w");
    // feof() returns non-zero value when end-of-file has reached
    while (feof(input_ptr) == 0)
    {
        // Read next line from input file
        fscanf(input_ptr, "%s %s %s", label, opcode, operand);
        // If label is present, add it to symtab
        if (strcmp(label, "-") != 0 && strcmp(opcode, "START") != 0 && strcmp(opcode, "END") != 0)
            fprintf(symtab_ptr, "%s %x\n", label, locctr);
        // If opcode = START, set starting address and locctr as operand
        if (strcmp(opcode, "START") == 0)
        {
            length = 0;
            start_addr = (int)strtol(operand, NULL, 16);
            locctr = start_addr;
        }
        // If opcode = END, write length of program to length file
        else if (strcmp(opcode, "END") == 0)
        {
            length = 0;
            fprintf(length_ptr, "%x", locctr - start_addr);
        }
        // If opcode = BYTE, set length of the instruction = length of operand
        else if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'X')
                length = (strlen(operand) - 3) / 2;
            if (operand[0] == 'C')
                length = strlen(operand) - 3;
        }
        // If opcode = WORD, set length of instruction = 3
        else if (strcmp(opcode, "WORD") == 0)
            length = 3;
        // If opcode = RESB, set length of instruction = operand
        else if (strcmp(opcode, "RESB") == 0)
            length = (int)strtol(operand, NULL, 16);
        // If opcode = RESW, set length of instruction = 3 * operand
        else if (strcmp(opcode, "RESW") == 0)
            length = 3 * (int)strtol(operand, NULL, 16);
        // Search optab for opcode
        else
        {
            // Check if current line is a 4 byte instruction (opcode starts with '+')
            if (opcode[0] == '+')
                length = 4;
            else
                length = 3;
            // Stores the opcode searched from optab
            char opc[20];
            // Stores the value of opcode from optab
            char value[10];
            // Set to 1 if matching opcode in optab is found
            int flag = 0;
            // Search for opcode in optab
            optab_ptr = fopen("optab.txt", "r");
            while (feof(optab_ptr) == 0)
            {
                fscanf(optab_ptr, "%s %s", opc, value);
                char temp[20] = "+";
                strcat(temp, opc);
                if (strcmp(opcode, opc) == 0 || strcmp(opcode, temp) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            fclose(optab_ptr);
            if (flag == 0)
            {
                printf("Invalid opcode.\n");
                break;
            }
        }
        // Write to intermediate file
        fprintf(intermed_ptr, "%x %d %s %s %s\n", locctr, length, label, opcode, operand);
        printf("%x %d %s %s %s\n", locctr, length, label, opcode, operand);
        // Increment locctr with the calculated length of instruction
        locctr += length;
    }
    printf("\nLength of program: %x", locctr - start_addr);
    fclose(input_ptr);
    fclose(symtab_ptr);
    fclose(intermed_ptr);
    fclose(length_ptr);
}