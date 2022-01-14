#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file
{
    char filename[20];
    struct file *next;
    char parent_directory[20];
};

struct directory
{
    char dirname[20];
    struct file *flstart;
    struct directory *dlstart;
    struct directory *next;
};

struct file *slds = NULL;
struct directory *tlds = NULL;
char rootdir[20];
struct directory *root = NULL;
struct directory *dir_location = NULL;
struct file *file_location = NULL;

void heirarchical_display(struct directory *ptr)
{
    struct directory *temp = ptr;

    while (temp != NULL)
    {
        printf("\nDirectory: %s\n", temp->dirname);

        if (temp->dlstart == NULL)
            printf("\tDirectories in %s: Empty\n", temp->dirname);
        else
        {
            printf("\tDirectories in %s:\n", temp->dirname);
            struct directory *dir_ptr = temp->dlstart;
            while (dir_ptr != NULL)
            {
                printf("\t\t%s\n", dir_ptr->dirname);
                dir_ptr = dir_ptr->next;
            }
        }

        int flag = 0;

        printf("\tFiles in %s: ", temp->dirname);
        struct file *file_ptr = temp->flstart;
        while (file_ptr != NULL)
        {
            if (strcmp(file_ptr->filename, "") != 0)
            {
                printf("\n\t\t%s", file_ptr->filename);
                flag = 1;
            }
            file_ptr = file_ptr->next;
        }
        if (flag != 1)
            printf("Empty\n");
        else
            printf("\n");

        heirarchical_display(temp->dlstart);

        temp = temp->next;
    }
}

struct directory *search_parent(struct directory *ptr, char str[20])
{
    struct directory *temp = ptr;

    while (temp != NULL)
    {
        if (strcmp(str, temp->dirname) == 0)
            dir_location = temp;
        else
            search_parent(temp->dlstart, str);

        temp = temp->next;
    }
}

void heirarchical_create_directory(struct directory *root)
{
    int choice;
    char str[20];

    printf("Enter name of parent directory: ");
    scanf("%[^\n]", str);
    getchar();

    /*
    Initialize directory location as NULL
    Search for parent
    If parent is found, directory location becomes a non-NULL value 
    */
    dir_location = NULL;
    search_parent(root, str);

    if (dir_location == NULL)
    {
        printf("Parent directory not found.\n");
        return;
    }
    else
    {
        // Check if current directory does not have any subdirectory list
        if (dir_location->dlstart == NULL)
        {
            struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));

            printf("Enter name of the new directory: ");
            scanf("%[^\n]", str);
            strcpy(newnode->dirname, str);

            newnode->flstart = NULL;
            newnode->dlstart = NULL;
            newnode->next = NULL;

            dir_location->dlstart = newnode;
        }
        // Subdirectory list exists, add subdirectory to end of list
        else
        {
            struct directory *temp;
            temp = dir_location->dlstart;

            // Check if duplicate directory exists
            while (temp != NULL)
            {
                if (strcmp(str, temp->dirname) == 0)
                {
                    printf("Directory with similar name found. Directory creation failed.\n");
                    return;
                }
                temp = temp->next;
            }

            struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));

            printf("Enter name of the new directory: ");
            scanf("%[^\n]", str);
            strcpy(newnode->dirname, str);

            newnode->flstart = NULL;
            newnode->dlstart = NULL;
            newnode->next = NULL;

            temp = dir_location->dlstart;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
        }
    }
    printf("New directory %s successfully created!", str);
}

void heirarchical_create_file(struct directory *root)
{
    int choice;
    char str[20];

    printf("Enter name of parent directory: ");
    scanf("%[^\n]", str);
    getchar();
    /*
    Initialize directory location as NULL
    Search for parent
    If parent is found, directory location becomes a non-NULL value 
    */
    dir_location = NULL;
    search_parent(root, str);

    if (dir_location == NULL)
    {
        printf("Parent directory not found.\n");
        return;
    }
    else
    {
        // Check if current directory does not have any file list
        if (dir_location->flstart == NULL)
        {
            struct file *newnode = (struct file *)malloc(sizeof(struct file));

            printf("Enter name of the file: ");
            scanf("%[^\n]", str);
            strcpy(newnode->filename, str);
            newnode->next = NULL;

            dir_location->flstart = newnode;
        }
        // File list exists, add file to end of list
        else
        {
            struct file *temp;
            temp = dir_location->flstart;

            // Check if duplicate file exists
            while (temp != NULL)
            {
                if (strcmp(str, temp->filename) == 0)
                {
                    printf("File with similar name found. File creation failed.\n");
                    return;
                }
                temp = temp->next;
            }

            struct file *newnode = (struct file *)malloc(sizeof(struct file));

            printf("Enter name of the file: ");
            scanf("%[^\n]", str);
            strcpy(newnode->filename, str);
            newnode->next = NULL;

            temp = dir_location->flstart;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
        }
    }
    printf("New file %s successfully created!\n", str);
}

void heirarchical_search_file(struct directory *ptr, char str[20])
{
    struct directory *temp = ptr;

    while (temp != NULL)
    {
        struct file *file_ptr = temp->flstart;
        while (file_ptr != NULL)
        {
            if (strcmp(file_ptr->filename, str) == 0)
            {
                printf("File found!\n");
                file_location = file_ptr;
            }

            file_ptr = file_ptr->next;
        }

        heirarchical_search_file(temp->dlstart, str);

        temp = temp->next;
    }
}

void heirarchical_delete_file(struct directory *ptr, char str[20])
{
    file_location = NULL;
    // File location will be a non-NULL value if search is successful
    heirarchical_search_file(ptr, str);

    if (file_location != NULL)
    {
        strcpy(file_location->filename, "");
        printf("File deleted successfully!\n");
    }
    else
        printf("File not found!\n");
}

void slds_create()
{
    if (slds == NULL)
    {
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        printf("\nEnter the name of the file: ");
        scanf("%[^\n]", newnode->filename);
        slds = newnode;
        newnode->next = NULL;
        printf("New file %s created successfully!\n", newnode->filename);
    }
    else
    {
        struct file *temp;
        temp = slds;
        char filename[20];
        printf("\nEnter the name of the file: ");
        scanf("%[^\n]", filename);

        // Check if duplicate file exists
        while (temp != NULL)
        {
            if (strcmp(filename, temp->filename) == 0)
            {
                printf("A file with this name already exists. File creation failed!\n");
                return;
            }
            temp = temp->next;
        }
        struct file *ptr;
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        strcpy(newnode->filename, filename);
        ptr = slds;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newnode;
        newnode->next = NULL;
        printf("New file %s created successfully!\n", newnode->filename);
    }
}

void slds_delete()
{
    if (slds == NULL)
        printf("\nThe root directory is empty!\n");
    else
    {
        char filename[20], found = 0;
        struct file *ptr;
        struct file *preptr;
        ptr = slds;
        preptr = slds;
        printf("\nEnter the name of the file which is to be deleted: ");
        scanf("%[^\n]", filename);
        for (; ptr != NULL;)
        {
            if (strcmp(ptr->filename, filename) == 0)
            {
                found = 1;
                break;
            }
            preptr = ptr;
            ptr = ptr->next;
        }
        if (found == 1)
        {
            if (ptr == slds)
            {
                if (slds->next == NULL)
                {
                    slds = NULL;
                    free(ptr);
                }
                else
                {
                    slds = ptr->next;
                    free(ptr);
                }
            }
            else
            {
                preptr->next = ptr->next;
                free(ptr);
            }
            printf("File %s deleted successfully!\n", filename);
        }
        else
        {
            printf("There is no file named %s\n", filename);
        }
    }
}

void slds_search()
{
    if (slds == NULL)
        printf("\nThe root directory is empty!\n");
    else
    {
        char filename[20], found = 0;
        struct file *ptr;
        ptr = slds;
        printf("\nEnter the name of the file which is to be searched: ");
        scanf("%[^\n]", filename);
        for (; ptr != NULL;)
        {
            if (strcmp(ptr->filename, filename) == 0)
            {
                found = 1;
                break;
            }
            ptr = ptr->next;
        }
        if (found == 1)
        {
            printf("The file %s exists in the root directory!\n", filename);
        }
        else
        {
            printf("The file %s does not exist in the root directory!\n", filename);
        }
    }
}

void slds_display()
{
    struct file *ptr;
    ptr = slds;
    if (slds == NULL)
        printf("\nThe root directory is empty!\n");
    else
    {
        printf("\n%s(root directory):\n", rootdir);
        while (ptr != NULL)
        {
            printf("%s", ptr->filename);
            printf("      ");
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void single_level()
{
    int choice;
    printf("\nEnter the name of the root directory: ");
    scanf("%[^\n]", &rootdir);
    printf("Root directory %s created successfully!\n", rootdir);
    while (1)
    {
        printf("\nMenu:\n1.Create file\n2.Delete file\n3.Search file\n4.Display files\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            slds_create();
            break;
        case 2:
            slds_delete();
            break;
        case 3:
            slds_search();
            break;
        case 4:
            slds_display();
            break;
        case 5:
            printf("\n");
            return;
        default:
            printf("\nPlease enter a valid choice.");
        }
    }
}

void tlds_create_directory()
{
    char directory_name[20];

    if (tlds == NULL)
    {
        struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));
        newnode->next = NULL;
        newnode->dlstart = NULL;
        newnode->flstart = NULL;

        printf("Enter name of the directory: ");
        scanf("%[^\n]", directory_name);

        strcpy(newnode->dirname, directory_name);

        tlds = newnode;
    }
    else
    {
        struct directory *ptr;
        struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));

        printf("Enter name of the directory: ");
        scanf("%[^\n]", directory_name);
        newnode->next = NULL;
        newnode->dlstart = NULL;
        newnode->flstart = NULL;

        ptr = tlds;
        while (ptr != NULL)
        {
            if (strcmp(directory_name, ptr->dirname) == 0)
            {
                printf("Directory with similar name found. Directory creation failed!\n");
                return;
            }
            ptr = ptr->next;
        }

        ptr = tlds;
        while (ptr->next != NULL)
            ptr = ptr->next;

        strcpy(newnode->dirname, directory_name);
        ptr->next = newnode;

        printf("New directory %s created successfully!\n", directory_name);
    }
}

void tlds_create_file()
{
    int flag = 0;
    char pdir[20];
    char filename[20];
    struct directory *ptr1;

    printf("Enter parent directory of file: ");
    scanf("%[^\n]", pdir);
    getchar();
    ptr1 = tlds;
    while (ptr1 != NULL)
    {
        if (strcmp(pdir, ptr1->dirname) == 0)
        {
            flag = 1;
            break;
        }
        ptr1 = ptr1->next;
    }

    if (flag == 0)
    {
        printf("Parent directory not found!\n");
        return;
    }

    if (ptr1->flstart == NULL)
    {
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        newnode->next = NULL;

        printf("Enter the name of the file: ");
        scanf("%[^\n]", filename);

        strcpy(newnode->filename, filename);

        ptr1->flstart = newnode;
    }
    else
    {
        struct file *ptr;
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        newnode->next = NULL;

        printf("Enter name of the file: ");
        scanf("%[^\n]", filename);

        ptr = ptr1->flstart;
        while (ptr != NULL)
        {
            if (strcmp(filename, ptr->filename) == 0)
            {
                printf("File with this name already exists. File creation failed!\n");
                return;
            }
            ptr = ptr->next;
        }

        ptr = ptr1->flstart;
        while (ptr->next != NULL)
            ptr = ptr->next;

        strcpy(newnode->filename, filename);
        ptr->next = newnode;

        printf("New file %s created successfully!\n", filename);
    }
}

void tlds_delete()
{
    char filename[20], found = 0;
    struct file *ptr;
    struct file *preptr;
    struct directory *ptr1;

    printf("Enter name of the file to be deleted: ");
    scanf("%[^\n]", filename);

    ptr1 = tlds;
    while (ptr1 != NULL)
    {
        preptr = ptr = ptr1->flstart;

        while (ptr != NULL)
        {
            if (strcmp(ptr->filename, filename) == 0)
            {
                found = 1;
                break;
            }
            preptr = ptr;
            ptr = ptr->next;
        }

        if (found == 1)
            break;

        ptr1 = ptr1->next;
    }

    if (found == 1)
    {
        if (ptr == ptr1->flstart)
        {
            if (ptr1->flstart->next == NULL)
            {
                ptr1->flstart = NULL;
                free(ptr);
            }
            else
            {
                ptr1->flstart = ptr->next;
                free(ptr);
            }
        }
        else
        {
            preptr->next = ptr->next;
            free(ptr);
        }
        printf("File %s deleted successfully!\n", filename);
    }
    else
        printf("File named %s not found!\n", filename);
}

void tlds_search()
{
    struct file *ptr;
    struct directory *ptr1;
    char str[20];

    printf("Enter the name of the file to be searched: ");
    scanf("%[^\n]", str);

    if (tlds == NULL)
        printf("The root directory is empty!\n");
    else
    {
        ptr1 = tlds;

        while (ptr1 != NULL)
        {
            ptr = ptr1->flstart;

            while (ptr != NULL)
            {
                if (strcmp(ptr->filename, str) == 0)
                {
                    printf("File %s found!\n", str);
                    return;
                }
                ptr = ptr->next;
            }
            ptr1 = ptr1->next;
        }

        printf("File %s not found!\n", str);
    }
}

void tlds_display()
{
    struct directory *ptr1;
    struct file *ptr2;

    printf("\nTwo-level directory structure:\n");
    printf("%-38s[root]\n", rootdir);

    ptr1 = tlds;

    while (ptr1 != NULL)
    {
        printf("\t-%-29s[directory]\n", ptr1->dirname);

        ptr2 = ptr1->flstart;

        while (ptr2 != NULL)
        {
            printf("\t\t-%-21s[file]\n", ptr2->filename);
            ptr2 = ptr2->next;
        }

        ptr1 = ptr1->next;
    }
}

void two_level()
{
    int choice;
    printf("\nEnter the name of the root directory: ");
    scanf("%[^\n]", &rootdir);
    printf("Root directory %s created successfully!\n", rootdir);
    while (1)
    {
        printf("\nMenu:\n1.Create directory\n2.Create file\n3.Delete file\n4.Search file\n5.Display files\n6.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            tlds_create_directory();
            break;
        case 2:
            tlds_create_file();
            break;
        case 3:
            tlds_delete();
            break;
        case 4:
            tlds_search();
            break;
        case 5:
            tlds_display();
            break;
        case 6:
            printf("\n");
            return;
        default:
            printf("\nPlease enter a valid choice.");
        }
    }
}

void hierarchical()
{
    int choice;
    char str[20];
    root = (struct directory *)malloc(sizeof(struct directory));
    printf("\nEnter the name of the root directory: ");
    scanf("%[^\n]", &rootdir);
    strcpy(root->dirname, rootdir);
    root->flstart = NULL;
    root->dlstart = NULL;
    root->next = NULL;
    printf("Root directory %s created successfully!\n", rootdir);
    while (1)
    {
        printf("\nMenu:\n1.Create directory\n2.Create file\n3.Delete file\n4.Search file\n5.Display files\n6.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            heirarchical_create_directory(root);
            break;
        case 2:
            heirarchical_create_file(root);
            break;
        case 3:
            printf("Enter the name of the file to be deleted: ");
            scanf("%[^\n]", str);
            heirarchical_delete_file(root, str);
            break;
        case 4:
            printf("Enter the name of the file to be searched: ");
            scanf("%[^\n]", str);
            file_location = NULL;
            heirarchical_search_file(root, str);
            if (file_location == NULL)
                printf("File not found!\n");
            break;
        case 5:
            heirarchical_display(root);
            break;
        case 6:
            printf("\n");
            return;
        default:
            printf("\nPlease enter a valid choice.");
        }
    }
}

void reset(int choice)
{
    struct file *fileptr;
    struct file *filetemp;
    struct directory *dirptr;
    struct directory *dirptr2;
    struct directory *dirtemp;
    struct directory *dirtemp2;
    if(choice==1)
    {
        for (fileptr = slds; fileptr != NULL;)
        {
            filetemp = fileptr->next;
            free(fileptr);
            fileptr = filetemp;
        }
        struct file *slds = NULL;
    }
    else if(choice==2)
    {
        for (dirptr = tlds; dirptr != NULL;)
        {
            for (fileptr = dirptr->flstart; fileptr != NULL;)
            {
                filetemp = fileptr->next;
                free(fileptr);
                fileptr = filetemp;
            }
            dirtemp = dirptr->next;
            free(dirptr);
            dirptr = dirtemp;
        }
        struct directory *tlds = NULL;
    }
    else if(choice==3)
    {
        for (dirptr = root; dirptr != NULL;)
        {
            for (fileptr = dirptr->flstart; fileptr != NULL;)
            {
                filetemp = fileptr->next;
                free(fileptr);
                fileptr = filetemp;
            }
            for (dirptr2 = dirptr->dlstart; dirptr2 != NULL;)
            {
                dirtemp2 = dirptr2->next;
                free(dirptr2);
                dirptr2 = dirtemp2;
            }
            dirtemp = dirptr->next;
            free(dirptr);
            dirptr = dirtemp;
        }
        struct directory *root = NULL;
        // free(dir_location);
        // free(file_location);
        struct directory *dir_location = NULL;
        struct file *file_location = NULL;
    }
}

void main()
{
    int choice;
    printf("Sagar Paul\t41\n\n");
    while (1)
    {
        printf("Directory Structure Menu:\n1.Single Level\n2.Two-level\n3.Heirarchical\n4.Exit\n");
        printf("\nPlease enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            single_level();
            break;
        case 2:
            two_level();
            break;
        case 3:
            hierarchical();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\nPlease enter a valid choice!");
        }
        reset(choice);
    }
}
