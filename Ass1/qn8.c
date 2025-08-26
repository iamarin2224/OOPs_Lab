#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    int roll;
    char* name;
    int score;
}student;

void allocateMemory(student** arr, int n){
    (*arr) = (student *)malloc(n * sizeof(student));

    for (int i=0; i<n; i++){
        (*arr)[i].name = (char *)malloc(33 * sizeof(char));
    }
}

void mySort(student* arr, int n, int (*compare)(student a, student b)){
    int flag = 0;
    student temp;
    for (int i=0; i<n-1; i++){
        flag = 0;
        for (int j=0; j<n-i-1; j++){
            if (!(compare(arr[j], arr[j+1]))){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

                flag = 1;
            }
        }
        if (!flag) break;
    }
}

int scoreAsc(student a, student b){
    if (a.score <= b.score){
        return 1;
    }
    return 0;
}

int scoreDesc(student a, student b){
    if (a.score >= b.score){
        return 1;
    }
    return 0;
}

int rollAsc(student a, student b){
    if (a.roll <= b.roll){
        return 1;
    }
    return 0;
}

int rollDesc(student a, student b){
    if (a.roll >= b.roll){
        return 1;
    }
    return 0;
}

void collectData(student* arr, int n){
    for (int i=0; i<n; i++){
        printf("Enter the details of person %d-> \n", i+1);
        printf("Enter roll: ");
        scanf("%d", &arr[i].roll);
        getchar();
        printf("Enter name (max 32 char): ");
        scanf("%[^\n]", arr[i].name);
        printf("Enter score: ");
        scanf("%d", &arr[i].score);
        getchar();
        printf("\n");
    }
}

void displayData(student* arr, int n){
    printf("The list of students is: \n");
    for(int i=0; i<n; i++){
        printf("\n");
        printf("Student %d: \n", i);
        printf("Roll: %d\n", arr[i].roll);
        printf("Name: %s\n", arr[i].name);
        printf("Score: %d\n", arr[i].score);
        printf("\n");
    }
}

int main(){
    int n;
    printf("Enter number of records you want: ");
    scanf("%d", &n);

    student* arr;

    allocateMemory(&arr, n);

    collectData(arr, n);

    printf("\
        Enter your choice: \n\
        1. Sort according to *ROLL* in *ASCENDING* order \n\
        2. Sort according to *ROLL* in *DESCENDING* order \n\
        3. Sort according to *SCORE* in *ASCENDING* order \n\
        4. Sort according to *SCORE* in *DESCENDING* order \n\
    ");
    
    int choice;
    scanf("%d", &choice);

    if (choice == 1){
        mySort(arr, n, rollAsc);
        displayData(arr, n);
    }

    else if (choice == 2){
        mySort(arr, n, rollDesc);
        displayData(arr, n);
    }

    else if (choice == 3){
        mySort(arr, n, scoreAsc);
        displayData(arr, n);
    }

    else if (choice == 4){
        mySort(arr, n, scoreDesc);
        displayData(arr, n);
    }

    else{
        printf("Invalid Input!...Exiting\n");
    }

    return 0;
}