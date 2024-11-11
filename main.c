#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    char* Name;
    char* Address;
    int Id;
    struct student* ptr;
};

void saveToFile(struct student* head, const char* filename)
{
    FILE* file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("Unable to open file for saving");
        return;
    }

    struct student* current = head;
    while (current != NULL) {
        fprintf(file, "%d %s %s\n", current->Id, current->Name, current->Address);
        current = current->ptr;
    }
    fclose(file);
    printf("List saved to %s.\n", filename);
}

void displayFileContent(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open file for reading");
        return;
    }

    int id;
    char name[50];
    char address[100];
    printf("File Content:\nId\tName\t\tAddress\n");
    while (fscanf(file, "%d %s %s", &id, name, address) == 3)
    {
        printf("%d\t%s\t\t%s\n", id, name, address);
    }
    fclose(file);
}

struct student* loadFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open file for loading");
        return NULL;
    }

    struct student* head = NULL;
    struct student* temp = NULL;

    while (!feof(file)) {
        struct student* newnode = (struct student*)malloc(sizeof(struct student));
        newnode->Name = (char*)malloc(50 * sizeof(char));
        newnode->Address = (char*)malloc(100 * sizeof(char));

        if (fscanf(file, "%d %s %s", &newnode->Id, newnode->Name, newnode->Address) == 3) {
            newnode->ptr = NULL;
            if (head == NULL) {
                head = newnode;
                temp = newnode;
            } else {
                temp->ptr = newnode;
                temp = newnode;
            }
        } else {
            free(newnode->Name);
            free(newnode->Address);
            free(newnode);
            break;
        }
    }
    fclose(file);
    printf("List loaded from %s.\n", filename);
    return head;
}

void swapStudentsByName(struct student* head, char* name1, char* name2)
{
    if (strcmp(name1, name2) == 0)
    {
        printf("The names are the same; no swap needed.\n");
        return;
    }
    struct student *prev1 = NULL, *curr1 = head;
    struct student *prev2 = NULL, *curr2 = head;
    while (curr1 && strcmp(curr1->Name, name1) != 0)
    {
        prev1 = curr1;
        curr1 = curr1->ptr;
    }
    while (curr2 && strcmp(curr2->Name, name2) != 0)
    {
        prev2 = curr2;
        curr2 = curr2->ptr;
    }
    if (!curr1 || !curr2)
    {
        printf("One or both students not found.\n");
        return;
    }
    if (prev1)
    {
        prev1->ptr = curr2;
    }
    else
    {
        head = curr2;
    }
    if (prev2)
    {
        prev2->ptr = curr1;
    }
    else
    {
        head = curr1;
    }
    struct student* temp = curr1->ptr;
    curr1->ptr = curr2->ptr;
    curr2->ptr = temp;
    printf("Students %s and %s swapped successfully.\n", name1, name2);
}
void sortStudentsByName(struct student* head)
{
    if (head == NULL)
    {
        return;
    }
    struct student* i = head;
    while (i->ptr != NULL)
    {
        struct student* j = i->ptr;
        while (j != NULL)
        {
            if (strcmp(i->Name, j->Name) > 0)
            {
                char* tempName = i->Name;
                char* tempAddress = i->Address;
                int tempId = i->Id;

                i->Name = j->Name;
                i->Address = j->Address;
                i->Id = j->Id;

                j->Name = tempName;
                j->Address = tempAddress;
                j->Id = tempId;
            }
            j = j->ptr;
        }
        i = i->ptr;
    }
    printf("Students sorted by name.\n");
}
void sortStudentsById(struct student* head)
{
    if (head == NULL)
        return;
    struct student* i = head;
    while (i->ptr != NULL)
    {
        struct student* j = i->ptr;
        while (j != NULL)
        {
            if (i->Id > j->Id)
            {
                char* tempName = i->Name;
                char* tempAddress = i->Address;
                int tempId = i->Id;

                i->Name = j->Name;
                i->Address = j->Address;
                i->Id = j->Id;

                j->Name = tempName;
                j->Address = tempAddress;
                j->Id = tempId;
            }
            j = j->ptr;
        }
        i = i->ptr;
    }
    printf("Students sorted by ID.\n");
}


int main()
{
    int choice, count = 1,pos,pos1;
    struct student *head, *newnode, *temp, *temp1,*temp2,*temp3;
    char filename[] = "students.txt";
    head = NULL;
    while (1)
    {
        printf("Enter \n1 to Add Student\n2 to Swap Students by Name\n3 to Display\n4 toInsert student\n5 to delete student\n6 to Sort by Naame\n7 to Sort by ID\n8 to save to file(list - file)\n9 to Display file data\n10 to Sync(file - list)\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if(count)
            {
                newnode = (struct student*)malloc(sizeof(struct student));
                newnode->Name = (char*)malloc(50 * sizeof(char));
                printf("Enter name: ");
                scanf("%s", newnode->Name);
                printf("Enter ID: ");
                scanf("%d", &newnode->Id);
                newnode->Address = (char*)malloc(100 * sizeof(char));
                printf("Enter Address: ");
                scanf("%s", newnode->Address);
                newnode->ptr = NULL;
                if (head == NULL)
                {
                    head = newnode;
                    temp = newnode;
                }
                else
                {
                    temp->ptr = newnode;
                    temp = newnode;
                }
                count++;
            }
            break;
        case 2:
        {
            char name1[50], name2[50];
            printf("Enter the first student's name to swap: ");
            scanf("%s", name1);
            printf("Enter the second student's name to swap: ");
            scanf("%s", name2);
            swapStudentsByName(head, name1, name2);
            break;
        }
        case 3:
            printf("Student Details:\npos\tId\tName\t\tAddress\n");
            temp1 = head;
            if(head == 0)
            {
                printf("List is Empty\n");
            }
            int k = 1;
            while (temp1 != NULL)
            {
                printf("%d\t%d\t%s\t\t%s\n", k++, temp1->Id, temp1->Name, temp1->Address);
                temp1 = temp1->ptr;
            }
            break;

        case 4:
            printf("Enter position after which you want to insert\n");
            scanf("%d",&pos);
            if(pos > count)
            {
                printf("Enter Valid position\n");
            }
            else
            {
                temp2 = head;
                int i = 1;
                while(i < pos)
                {
                    temp2 = temp2->ptr;
                    i++;
                }
                newnode = (struct student*)malloc(sizeof(struct student));
                newnode->Name = (char*)malloc(50 * sizeof(char));
                printf("Enter name: ");
                scanf("%s", newnode->Name);
                printf("Enter ID: ");
                scanf("%d", &newnode->Id);
                newnode->Address = (char*)malloc(100 * sizeof(char));
                printf("Enter Address: ");
                scanf("%s", newnode->Address);
                newnode->ptr = temp2->ptr;
                temp2->ptr = newnode;

            }
            break;

        case 5:printf("Enter Position of student to delete\n");
            scanf("%d",&pos1);
            struct student *temp3,*nextnode;
            temp3 = head;
            int i = 1;
            while(i < pos1 - 1)
            {
                temp3 = temp3->ptr;
                i++;

            }
            nextnode = temp3->ptr;
            temp3->ptr = nextnode->ptr;
            free(nextnode);
            break;

        case 6:
            sortStudentsByName(head);
            break;

        case 7:
            sortStudentsById(head);
            break;

        case 8:
            saveToFile(head, filename);
            break;

        case 9:
            displayFileContent(filename);
            break;

        case 10:
            temp3 = head;
            while (temp3 != NULL) {
                struct student* next = temp3->ptr;
                free(temp3->Name);
                free(temp3->Address);
                free(temp3);
                temp3 = next;
            }
            head = loadFromFile(filename);
            break;

        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    }

    return 0;
}

















// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// struct student {
//     char* Name;
//     char* Address;
//     int Id;
//     struct student* ptr;
// };

// void swapStudentsByName(struct student** head, char* name1, char* name2) {
//     if (strcmp(name1, name2) == 0) {
//         printf("The names are the same; no swap needed.\n");
//         return;
//     }

//     struct student *prev1 = NULL, *curr1 = *head;
//     struct student *prev2 = NULL, *curr2 = *head;

//     while (curr1 && strcmp(curr1->Name, name1) != 0) {
//         prev1 = curr1;
//         curr1 = curr1->ptr;
//     }
//     while (curr2 && strcmp(curr2->Name, name2) != 0) {
//         prev2 = curr2;
//         curr2 = curr2->ptr;
//     }

//     if (!curr1 || !curr2) {
//         printf("One or both students not found.\n");
//         return;
//     }

//     if (prev1) {
//         prev1->ptr = curr2;
//     } else {
//         *head = curr2;
//     }

//     if (prev2) {
//         prev2->ptr = curr1;
//     } else {
//         *head = curr1;
//     }

//     struct student* temp = curr1->ptr;
//     curr1->ptr = curr2->ptr;
//     curr2->ptr = temp;
//     printf("Students %s and %s swapped successfully.\n", name1, name2);
// }

// void displayStudents(struct student* head) {
//     struct student* temp = head;
//     int pos = 1;

//     printf("Student Details:\npos\tId\tName\t\tAddress\n");
//     while (temp != NULL) {
//         printf("%d\t%d\t%s\t\t%s\n", pos++, temp->Id, temp->Name, temp->Address);
//         temp = temp->ptr;
//     }
// }

// void addStudent(struct student** head, int* count) {
//     struct student* newnode = (struct student*)malloc(sizeof(struct student));
//     newnode->Name = (char*)malloc(50 * sizeof(char));
//     newnode->Address = (char*)malloc(100 * sizeof(char));

//     printf("Enter name: ");
//     scanf("%s", newnode->Name);
//     printf("Enter ID: ");
//     scanf("%d", &newnode->Id);
//     printf("Enter Address: ");
//     scanf("%s", newnode->Address);

//     newnode->ptr = NULL;

//     if (*head == NULL) {
//         *head = newnode;
//     } else {
//         struct student* temp = *head;
//         while (temp->ptr != NULL) {
//             temp = temp->ptr;
//         }
//         temp->ptr = newnode;
//     }
//     (*count)++;
// }

// struct student* cloneList(struct student* head) {
//     struct student* newHead = NULL;
//     struct student* newTail = NULL;
//     struct student* temp = head;

//     while (temp != NULL) {
//         struct student* newNode = (struct student*)malloc(sizeof(struct student));
//         newNode->Name = strdup(temp->Name);
//         newNode->Address = strdup(temp->Address);
//         newNode->Id = temp->Id;
//         newNode->ptr = NULL;

//         if (newHead == NULL) {
//             newHead = newNode;
//         } else {
//             newTail->ptr = newNode;
//         }
//         newTail = newNode;
//         temp = temp->ptr;
//     }
//     return newHead;
// }

// void sortByName(struct student* head) {
//     struct student *temp1, *temp2;
//     for (temp1 = head; temp1 != NULL; temp1 = temp1->ptr) {
//         for (temp2 = temp1->ptr; temp2 != NULL; temp2 = temp2->ptr) {
//             if (strcmp(temp1->Name, temp2->Name) > 0) {
//                 char* tempName = temp1->Name;
//                 temp1->Name = temp2->Name;
//                 temp2->Name = tempName;

//                 char* tempAddress = temp1->Address;
//                 temp1->Address = temp2->Address;
//                 temp2->Address = tempAddress;

//                 int tempId = temp1->Id;
//                 temp1->Id = temp2->Id;
//                 temp2->Id = tempId;
//             }
//         }
//     }
// }

// void sortByID(struct student* head) {
//     struct student *temp1, *temp2;
//     for (temp1 = head; temp1 != NULL; temp1 = temp1->ptr) {
//         for (temp2 = temp1->ptr; temp2 != NULL; temp2 = temp2->ptr) {
//             if (temp1->Id > temp2->Id) {
//                 char* tempName = temp1->Name;
//                 temp1->Name = temp2->Name;
//                 temp2->Name = tempName;

//                 char* tempAddress = temp1->Address;
//                 temp1->Address = temp2->Address;
//                 temp2->Address = tempAddress;

//                 int tempId = temp1->Id;
//                 temp1->Id = temp2->Id;
//                 temp2->Id = tempId;
//             }
//         }
//     }
// }

// void displaySortedByName(struct student* head) {
//     struct student* sortedHead = cloneList(head);
//     sortByName(sortedHead);
//     displayStudents(sortedHead);

//     struct student* temp;
//     while (sortedHead != NULL) {
//         temp = sortedHead;
//         sortedHead = sortedHead->ptr;
//         free(temp->Name);
//         free(temp->Address);
//         free(temp);
//     }
// }

// void displaySortedByID(struct student* head) {
//     struct student* sortedHead = cloneList(head);
//     sortByID(sortedHead);
//     displayStudents(sortedHead);

//     struct student* temp;
//     while (sortedHead != NULL) {
//         temp = sortedHead;
//         sortedHead = sortedHead->ptr;
//         free(temp->Name);
//         free(temp->Address);
//         free(temp);
//     }
// }

// int main() {
//     struct student* head = NULL;
//     int choice, count = 0;

//     while (1) {
//         printf("Enter \n1 to Add Student\n2 to Swap Students by Name\n3 to Display\n");
//         printf("4 to Display Sorted by Name\n5 to Display Sorted by ID\n6 to Save to File\n");
//         printf("7 to Display File Data\n8 to Sync File to Linked List\n9 to Exit\n");
//         scanf("%d", &choice);

//         switch (choice) {
//         case 1:
//             addStudent(&head, &count);
//             break;

//         case 2: {
//             char name1[50], name2[50];
//             printf("Enter the first student's name to swap: ");
//             scanf("%s", name1);
//             printf("Enter the second student's name to swap: ");
//             scanf("%s", name2);
//             swapStudentsByName(&head, name1, name2);
//             break;
//         }

//         case 3:
//             displayStudents(head);
//             break;

//         case 4:
//             displaySortedByName(head);
//             break;

//         case 5:
//             displaySortedByID(head);
//             break;

//         case 6:
//             printf("Exiting program.\n");
//             return 0;

//         default:
//             printf("Invalid choice. Try again.\n");
//             break;
//         }
//     }

//     return 0;
// }


























