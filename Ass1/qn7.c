#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    int roll;
    char* name;
    int score;
}student;

typedef struct Node{
    student record;
    struct Node* next;
}Node;

Node* createNode(){
    student stu;

    printf("Enter deatils of the student-> \n");

    printf("Enter roll: ");
    scanf("%d", &stu.roll);

    stu.name = (char *)malloc(33 * sizeof(char));
    printf("Enter name (max 32 characters): ");
    getchar();
    scanf("%[^\n]", stu.name);

    printf("Enter score: ");
    scanf("%d", &stu.score);

    printf("\n");

    Node* newNode = (Node *)malloc(sizeof(Node));

    newNode->record = stu;
    newNode->next = NULL;

    return newNode;

}

Node* createLL(int n){
    Node* head = createNode();
    Node* current = head;

    for (int i=1; i<n; i++){
        current->next = createNode();
        current = current->next;
    }

    return head;
}

void addStudent(Node* head){
    Node* newNode = createNode();

    Node* current = head;

    while(current->next != NULL){
        current = current->next;
    }

    current->next = newNode;
}

Node* deleteStudent(Node** head, int givenRoll){
    if ((*head)->record.roll == givenRoll){
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);

        return *head;
    }

    Node* current = *head;
    Node* prev = NULL;
    while(current != NULL){
        if (current->record.roll == givenRoll){
            prev->next = current->next;
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    if (current == NULL){
        printf("Please enter valid roll!\n");
        return *head;
    }

    return *head;
}

void displayData(Node* head){
    printf("The list of students is: \n");
    Node* current = head;
    int i = 1;
    while(current != NULL){
        printf("\n");
        printf("Student %d: \n", i);
        printf("Roll: %d\n", current->record.roll);
        printf("Name: %s\n", current->record.name);
        printf("Score: %d\n", current->record.score);
        printf("\n");
        current = current->next;
        i++;
    }
}

int main(){
    int n;
    printf("Enter number of record you want to enter: ");
    scanf("%d", &n);

    Node* LL = createLL(n);

    printf("\n Enter your choice: \n");
    int choice;

    while(1){
        printf("\
        Enter your choice: \n\
        0. To exit\n\
        1. Add new record \n\
        2. Delete given record \n\
        3. Display data \n\
        ");

        scanf("%d", &choice);

        if (choice == 0) break;

        else if (choice == 1){
            addStudent(LL);
        }

        else if (choice == 2){
            int roll;
            printf("Enter roll to delete: ");
            scanf("%d", &roll);
            LL = deleteStudent(&LL, roll);
        }

        else if (choice == 3){
            displayData(LL);
        }

        else{
            printf("Please enter valid choice!\n");
        }
    }

    return 0;
}