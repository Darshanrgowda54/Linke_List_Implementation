#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char* Name;
    char* Address;
    int Id;
    struct student* ptr;
};

void swapStudentsByName(struct student** head, char* name1, char* name2) {
    if (strcmp(name1, name2) == 0) {
        printf("The names are the same; no swap needed.\n");
        return;
    }

    struct student *prev1 = NULL, *curr1 = *head;
    struct student *prev2 = NULL, *curr2 = *head;

    while (curr1 && strcmp(curr1->Name, name1) != 0) {
        prev1 = curr1;
        curr1 = curr1->ptr;
    }
    while (curr2 && strcmp(curr2->Name, name2) != 0) {
        prev2 = curr2;
        curr2 = curr2->ptr;
    }

    if (!curr1 || !curr2) {
        printf("One or both students not found.\n");
        return;
    }

    if (prev1) {
        prev1->ptr = curr2;
    } else {
        *head = curr2;
    }

    if (prev2) {
        prev2->ptr = curr1;
    } else {
        *head = curr1;
    }

    struct student* temp = curr1->ptr;
    curr1->ptr = curr2->ptr;
    curr2->ptr = temp;
    printf("Students %s and %s swapped successfully.\n", name1, name2);
}

void displayStudents(struct student* head) {
    struct student* temp = head;
    int pos = 1;

    printf("Student Details:\npos\tId\tName\t\tAddress\n");
    while (temp != NULL) {
        printf("%d\t%d\t%s\t\t%s\n", pos++, temp->Id, temp->Name, temp->Address);
        temp = temp->ptr;
    }
}

void addStudent(struct student** head, int* count) {
    struct student* newnode = (struct student*)malloc(sizeof(struct student));
    newnode->Name = (char*)malloc(50 * sizeof(char));
    newnode->Address = (char*)malloc(100 * sizeof(char));

    printf("Enter name: ");
    scanf("%s", newnode->Name);
    printf("Enter ID: ");
    scanf("%d", &newnode->Id);
    printf("Enter Address: ");
    scanf("%s", newnode->Address);

    newnode->ptr = NULL;

    if (*head == NULL) {
        *head = newnode;
    } else {
        struct student* temp = *head;
        while (temp->ptr != NULL) {
            temp = temp->ptr;
        }
        temp->ptr = newnode;
    }
    (*count)++;
}

struct student* cloneList(struct student* head) {
    struct student* newHead = NULL;
    struct student* newTail = NULL;
    struct student* temp = head;

    while (temp != NULL) {
        struct student* newNode = (struct student*)malloc(sizeof(struct student));
        newNode->Name = strdup(temp->Name);      // Duplicate the name
        newNode->Address = strdup(temp->Address); // Duplicate the address
        newNode->Id = temp->Id;
        newNode->ptr = NULL;

        if (newHead == NULL) {
            newHead = newNode;
        } else {
            newTail->ptr = newNode;
        }
        newTail = newNode;
        temp = temp->ptr;
    }
    return newHead;
}

void sortByName(struct student* head) {
    struct student *temp1, *temp2;
    for (temp1 = head; temp1 != NULL; temp1 = temp1->ptr) {
        for (temp2 = temp1->ptr; temp2 != NULL; temp2 = temp2->ptr) {
            if (strcmp(temp1->Name, temp2->Name) > 0) {
                char* tempName = temp1->Name;
                temp1->Name = temp2->Name;
                temp2->Name = tempName;

                char* tempAddress = temp1->Address;
                temp1->Address = temp2->Address;
                temp2->Address = tempAddress;

                int tempId = temp1->Id;
                temp1->Id = temp2->Id;
                temp2->Id = tempId;
            }
        }
    }
}

void sortByID(struct student* head) {
    struct student *temp1, *temp2;
    for (temp1 = head; temp1 != NULL; temp1 = temp1->ptr) {
        for (temp2 = temp1->ptr; temp2 != NULL; temp2 = temp2->ptr) {
            if (temp1->Id > temp2->Id) {
                char* tempName = temp1->Name;
                temp1->Name = temp2->Name;
                temp2->Name = tempName;

                char* tempAddress = temp1->Address;
                temp1->Address = temp2->Address;
                temp2->Address = tempAddress;

                int tempId = temp1->Id;
                temp1->Id = temp2->Id;
                temp2->Id = tempId;
            }
        }
    }
}

void displaySortedByName(struct student* head) {
    struct student* sortedHead = cloneList(head);
    sortByName(sortedHead);
    displayStudents(sortedHead);

    // Free memory allocated for the sorted list copy
    struct student* temp;
    while (sortedHead != NULL) {
        temp = sortedHead;
        sortedHead = sortedHead->ptr;
        free(temp->Name);
        free(temp->Address);
        free(temp);
    }
}

void displaySortedByID(struct student* head) {
    struct student* sortedHead = cloneList(head);
    sortByID(sortedHead);
    displayStudents(sortedHead);

    // Free memory allocated for the sorted list copy
    struct student* temp;
    while (sortedHead != NULL) {
        temp = sortedHead;
        sortedHead = sortedHead->ptr;
        free(temp->Name);
        free(temp->Address);
        free(temp);
    }
}

int main() {
    struct student* head = NULL;
    int choice, count = 0;

    while (1) {
        printf("Enter \n1 to Add Student\n2 to Swap Students by Name\n3 to Display\n");
        printf("4 to Display Sorted by Name\n5 to Display Sorted by ID\n6 to Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addStudent(&head, &count);
            break;

        case 2: {
            char name1[50], name2[50];
            printf("Enter the first student's name to swap: ");
            scanf("%s", name1);
            printf("Enter the second student's name to swap: ");
            scanf("%s", name2);
            swapStudentsByName(&head, name1, name2);
            break;
        }

        case 3:
            displayStudents(head);
            break;

        case 4:
            displaySortedByName(head);
            break;

        case 5:
            displaySortedByID(head);
            break;

        case 6:
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    }

    return 0;
}
