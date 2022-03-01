#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    printf("Sagar Paul\t41\n\n");

    // Stores program length read from length.txt file
    int prog_len;
    // Stores starting address of program read from header record
    char start_addr[10];

    // Components of a line read from intermediate file
    char loc[10];
    int length;
    char label[10];
    char opcode[10];
    char operand[10];

    // Stores the opcode and its machine equivalent while search optab
    char opc[10];
    char val[10];

    // Stores the symbol name and its address when it is searched in symtab
    char sym_name[10]; 
    char sym_addr[10];

    // Stores the length of the object code part (in bytes) in the text record
    int objc_len;
    // Stores the length of the complete text record (in bytes)
    int text_rec_len = 0;
    // Stores the starting address of the text record
    int text_rec_addr;

    /*Components of text record. Max total size of object codes in text record = 9 bytes*/
    // Stores 'T[starting address]'
    char text_header[10];
    // Stores the complete object code part of text record
    char obj_code[100];
    // Object code is appended as each line is read. After the text record is full, it is copied to obj_code
    char temp_objc[100];

    FILE *finter = fopen("intermediate.txt", "r");
    FILE *foptab = fopen("optab.txt", "r");
    FILE *fsymtab = fopen("symtab.txt", "r");
    FILE *flength = fopen("length.txt", "r");
    FILE *fobject = fopen("pass2_objectcode.txt", "w");

    fscanf(finter, "%s %d %s %s %s", loc, &length, label, opcode, operand);
    
    // Create header record
    if (strcmp(opcode, "START") == 0)
    {
        // Get starting address from intermediate file
        strcpy(start_addr, operand);
        // Set starting address of first text record
        text_rec_addr = (int)strtol(start_addr, NULL, 16);
        // Get program length from intermediate file
        fscanf(flength, "%x", &prog_len);
    }
    printf("H^%s^%06x^%06x\n", label, (int)strtol(start_addr, NULL, 16), prog_len);
    fprintf(fobject, "H^%s^%06x^%06x\n", label, (int)strtol(start_addr, NULL, 16), prog_len);

    // Create text record header
    snprintf(text_header, sizeof(text_header), "T^%06x", (int)strtol(start_addr, NULL, 16));
    strcpy(obj_code, "");

    /*
    The intermediate file is read line by line. The object code is stored intially in temp_obj and appended to obj_code as each line is read.
    Once the text record is full, obj_code is printed as the complete object code of current text rec. A new text record is created.
    obj_code is reset and the value currently held by temp_obj is added as object code for new text record. This is repeted until "END" rec.
    obj_len keeps track of the length of the object code to check if it exceeds the text rec limit.
    Max total size of object codes in text record = 9 bytes
    */
    while (strcmp(opcode, "END") != 0)
    {
        fscanf(finter, "%s %d %s %s %s", loc, &length, label, opcode, operand);

        // Clear all object code details
        objc_len = 0;
        strcpy(temp_objc, "");
 
        // Search optab for opcode
        while (!feof(foptab))
        {
            fscanf(foptab, "%s %s", opc, val);

            char newopc[20] = "+"; 
            strcat(newopc, opc); 

            // Opcode found
            if (strcmp(opcode, opc) == 0 || strcmp(opcode, newopc) == 0)
            {
                // Search symtab for operand
                while (!feof(fsymtab))
                {
                    fscanf(fsymtab, "%s%s", sym_name, sym_addr);

                    // Operand found. Concatenate machine code and address as object code
                    if (strcmp(operand, sym_name) == 0)
                    {
                        snprintf(temp_objc, sizeof(temp_objc), "^%s%s", val, sym_addr);
                        objc_len = 3;

                        break;
                    }
                }

                break;
            }
        }

        // If opcode = BYTE, object code = hex equivalent of each character
        if (strcmp(opcode, "BYTE") == 0) 
        {
            char op_val[5];

            strcpy(temp_objc, "^");

            for (int i = 2; i < strlen(operand) - 1; i++)
            {
                itoa(operand[i], op_val, 16);
                strcat(temp_objc, op_val);
                objc_len++;
            }               
        }
        
        // If opcode = WORD, object code = operand
        if (strcmp(opcode, "WORD") == 0)
        {
            strcpy(temp_objc, "");
            snprintf(temp_objc, sizeof(temp_objc), "^%06x", (int)strtol(operand, NULL, 16));
            objc_len = 3;
        }

        // If object code of current line fits in text record, append object code and increment current size of text record
        if (text_rec_len + objc_len <= 9) 
        {
            text_rec_len += objc_len;
            strcat(obj_code, temp_objc);
        }
        // Else (object code doesn't fit) print current text record and add the object code to a new text record
        else
        {
            printf("%s^%02x%s\n", text_header, text_rec_len, obj_code);
            fprintf(fobject, "%s^%02x%s\n", text_header, text_rec_len, obj_code);
            // Set address and length of new text record
            text_rec_addr += text_rec_len;
            text_rec_len = objc_len;
            // Create new text record with new starting address
            snprintf(text_header, sizeof(text_header), "T^%06x", text_rec_addr);
            // Copy current object code to object code of new text record
            strcpy(obj_code, temp_objc);
        }

        // Reset file pointer to beginning of optab
        fseek(foptab, SEEK_SET, 0);
    }
    printf("%s^%02x%s\n", text_header, text_rec_len, obj_code);
    fprintf(fobject, "%s^%02x%s\n", text_header, text_rec_len, obj_code);
    printf("E^00%s", start_addr);
    fprintf(fobject, "E^00%s\n", start_addr);

    fclose(finter);
    fclose(foptab);
    fclose(fsymtab);
    fclose(flength);
    fclose(fobject);
}
