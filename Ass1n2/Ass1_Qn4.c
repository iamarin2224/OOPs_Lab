#include <stdio.h>
#include <stdlib.h>

/* ------------------ Functions for getting dimensions ------------------ */

//Function to get the size of 1D array
void getDimForOneD(int* n){
    printf("Enter the size of the 1D array: ");
    scanf("%d", n);
    printf("\n");
}

//Function to get the rows and coloumns of 2D array
void getDimForTwoD(int* r, int* c){
    printf("Enter number of rows for the 2D array: ");
    scanf("%d", r);
    printf("\n");
    printf("Enter number of cols for the 2D array: ");
    scanf("%d", c);
    printf("\n");
}

/* ------------------ Functions for allocating space ------------------ */

//Function to allocate space for a 1D array
void allocateOneD(int** arr, int n){
    (*arr) = (int *)malloc(n * sizeof(int));
}

//Function to allocate space for a 2D array implemented as Array of pointers
void allocateTwoDArrPtrs(int* arr[], int r, int c){
    for (int i=0; i<r; i++){
        arr[i] = (int *)malloc(c * sizeof(int));
    }
}

//Function to allocate space for a 2D array implemented as pointer to pointer
void allocateTwoDPtrPtr(int*** arr, int r, int c){
    (*arr) = (int **)malloc(r * sizeof(int *));
    for (int i=0; i<r; i++){
        (*arr)[i] = (int *)malloc(c * sizeof(int));
    }
}

//Function to allocate space for a 2D array implemented as pointer to pointer, with single malloc statement
void allocateTwoDPtrPtrSingleMalloc(int*** arr, int r, int c){
    (*arr) = (int **)malloc(r*sizeof(int *) + r*c*sizeof(int));
    for (int i=0; i<r; i++){
        (*arr)[i] = (int *)(((*arr)+r)) + (i*c);
    }
}

/* ------------------ Functions for accepting values ------------------ */

//Function to get the values of 1D array
void acceptValuesForOneD(int* arr, int n){
    printf("Enter %d values for the 1D array: ", n);
    for (int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("\n");
}

//Function to get the values of 2D array
void acceptValuesForTwoD(int** arr, int r, int c){
    printf("Enter %dx%d values for the 2D array: \n", r, c);
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    printf("\n");
}

/* ------------------ Functions for printing values ------------------ */

//Function to print the values of 1D array
void printValuesForOneD(int* arr, int n){
    printf("The array is: ");
    for (int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//Function to print the values of 2D array
void printValuesForTwoD(int** arr, int r, int c){
    printf("The array is: \n");
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* ------------------ Functions to free allocated space ------------------ */

//Function to free the space allocated to 1D array
void freeOneD(int** arr){
    free(*arr);
}

//Function to free the space allocated to 2D array implemented as Array of pointers
void freeTwoDArrPtrs(int* arr[], int r){
    for (int i=0; i<r; i++){
        free(arr[i]);
    }
}

//Function to free the space allocated to 2D array implemented as pointer to pointer
void freeTwoDPtrPtr(int*** arr, int r){
    for (int i=0; i<r; i++){
        free((*arr)[i]);
    }
    free(*arr);
}

//Function to free the space allocated to 2D array implemented as pointer to pointer, with single malloc statement
void freeTwoDPtrPtrSingleMalloc(int*** arr){
    free(*arr);
}

/* ------------------ Main Program ------------------ */

int main(){

    // Display a simple menu for the user to choose the type of array to work with
    printf("\n Enter your choice: \n");
    printf("\
        1. Implement 1D Array \n\
        2. Implement 2D Array using *array of pointers* \n\
        3. Implement 2D Array using *pointer to pointer, double malloc* \n\
        4. Implement 2D Array using *pointer to pointer, single malloc*  \n\
        ");
    int choice;
    scanf("%d", &choice);
    
    //Declaration of variables for dimensions and arrays
    int n; int* oneDArr;
    int row, col; int** twoDArr;
    
/*
    Common sequence in all cases:
    1. Take dimensions from user
    2. Allocate memory
    3. Accept values
    4. Print values
    5. Free memory at the end
*/

    // Case 1: 1D array implementation
    if (choice == 1){
        getDimForOneD(&n);
        allocateOneD(&oneDArr, n);
        acceptValuesForOneD(oneDArr, n);
        printValuesForOneD(oneDArr, n);
        freeOneD(&oneDArr);
    }

    // Case 2: 2D array using array of pointers
    else if (choice == 2){
        getDimForTwoD(&row, &col);
        int* twoDArr[row];  //Declare the array of pointers
        allocateTwoDArrPtrs(twoDArr, row, col);
        acceptValuesForTwoD(twoDArr, row, col);
        printValuesForTwoD(twoDArr, row, col);
        freeTwoDArrPtrs(twoDArr, row);
    }

    // Case 3: 2D array using pointer-to-pointer with two malloc calls
    else if (choice == 3){
        getDimForTwoD(&row, &col);
        allocateTwoDPtrPtr(&twoDArr, row, col);
        acceptValuesForTwoD(twoDArr, row, col);
        printValuesForTwoD(twoDArr, row, col);
        freeTwoDPtrPtr(&twoDArr, row);
    }

    // Case 4: 2D array using pointer-to-pointer with single malloc
    else if (choice == 4){
        getDimForTwoD(&row, &col);
        allocateTwoDPtrPtrSingleMalloc(&twoDArr, row, col);
        acceptValuesForTwoD(twoDArr, row, col);
        printValuesForTwoD(twoDArr, row, col);
        freeTwoDPtrPtrSingleMalloc(&twoDArr);
    }

    else{
        // Invalid choice entered by user
        printf("Please enter a valid choice! \n");
    }

    return 0;
}