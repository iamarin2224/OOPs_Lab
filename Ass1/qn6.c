#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person{
    char* name;
    int age;
}person;

void allocateMemory(person **arr, int n){
    (*arr) = (person *)malloc(n * sizeof(person));

    for (int i=0; i<n; i++){
        ((*arr)[i]).name = (char *)malloc(33 * sizeof(char));
    }
};

void collectData(person *arr, int n){
    for (int i=0; i<n; i++){
        printf("Enter the details of person %d: \n", i+1);
        printf("Enter name (max 32 char): ");
        getchar();
        scanf("%[^\n]", arr[i].name);
        printf("Enter age: ");
        scanf("%d", &arr[i].age);
        printf("\n");
    }
}

void sortData(person *arr, int n){
    int flag;
    person temp;
    for (int i=0; i<n-1; i++){
        flag = 0;
        for (int j=0; j<n-i-1; j++){
            if (arr[j].age > arr[j+1].age){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

                flag = 1;
            }
        }

        if (!flag) break;
    }
}

void displayData(person *arr, int n){
    printf("\nThe details of persons in ascending order of age: \n");
    for (int i=0; i<n; i++){
        printf("Name: %s -> Age: %d\n", arr[i].name, arr[i].age);
    }
}

int main(){
    int n;

    printf("Enter the number of records you want: ");
    scanf("%d", &n);

    person* arr;

    allocateMemory(&arr, n);

    collectData(arr, n);

    sortData(arr, n);
    
    displayData(arr, n);

    return 0;
}