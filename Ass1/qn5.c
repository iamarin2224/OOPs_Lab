#include <stdio.h>
#include <stdlib.h>

void allocateMemory(char **name, int* arr){
    printf("Enter number of records: \n");
    int n; scanf("%d", &n);

    name = (char **)malloc(n * sizeof(char *));
    arr = (int *)malloc(n * sizeof(int));
}

int main(){
    char **name;
    int *arr;
}