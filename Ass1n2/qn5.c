#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocateMemory(char ***names, int** age, int n){
    *names = (char **)malloc(n * sizeof(char *));
    *age = (int *)malloc(n * sizeof(int));

    for (int i=0; i<n ; i++){
        (*names)[i] = (char *)malloc(33 * sizeof(char));
    }
}

void collectData(char **names, int* age, int n){
    for (int i=0; i<n; i++){
        printf("Enter the details of person %d: \n", i+1);
        printf("Enter name (max 32 char): ");
        getchar();
        scanf("%[^\n]", names[i]);
        printf("Enter age: ");
        scanf("%d", &age[i]);
        printf("\n");
    }
}

void sortData(char **names, int *age, int n){
    int flag;
    int tempAge; char* tempName;
    for (int i=0; i < n-1; i++){
        flag = 0;
        for (int j=0; j < n-i-1; j++){
            if (age[j] > age[j+1]){
                tempAge = age[j];
                age[j] = age[j+1];
                age[j+1] = tempAge;

                tempName = names[j];
                names[j] = names[j+1];
                names[j+1] = tempName;

                flag = 1;
            }
        }

        if (!flag){
            break;
        }
    }
}

void displayData(char** names, int* age, int n){
    printf("\nThe details of persons in ascending order of age: \n");
    for (int i=0; i<n; i++){
        printf("Name: %s -> Age: %d\n", names[i], age[i]);
    }
}

int main(){
    char **names;
    int *age;
    int n;

    printf("Enter number of records you want: \n");
    scanf("%d", &n);

    allocateMemory(&names, &age, n);

    collectData(names, age, n);

    sortData(names, age, n);

    displayData(names, age, n);

    return 0;
    
}