#include <stdio.h>
#include <stdlib.h>

//Defining the student structure
typedef struct student{
    int roll;
    char name[33];
    int score;
}student;

//Function to allocate space to the array with datatype as struct students
void allocateMemory(student** arr, int n){
    (*arr) = (student *)malloc(n * sizeof(student));
}

//Main sort function
//The third parameter is a pointer to a function, it serves as a placeholder to the comparision function of our choice
void mySort(student* arr, int n, int (*compare)(student a, student b)){
    student temp; //Declaration of temp variable
    
    //Bubble Sort Algorithm
    int flag = 0;
    for (int i=0; i<n-1; i++){
        flag = 0;
        for (int j=0; j<n-i-1; j++){
            //Use of the given comaprision function to check whether in sorted order
            if (!(compare(arr[j], arr[j+1]))){
                //Swap if the adjacent elements are not in sorted order
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

                flag = 1;   //Set flag as 1
            }
        }
        //flag = 0 implies array is already sorted, so we can stop further sorting
        if (!flag) break;  
    }
}

//Various comparision function based on need

// for score in ascending order
int scoreAsc(student a, student b){
    if (a.score <= b.score){
        return 1;
    }
    return 0;
}

// for score in ascending order
int scoreDesc(student a, student b){
    if (a.score >= b.score){
        return 1;
    }
    return 0;
}

// for roll in descending order
int rollAsc(student a, student b){
    if (a.roll <= b.roll){
        return 1;
    }
    return 0;
}

// for roll in descending order
int rollDesc(student a, student b){
    if (a.roll >= b.roll){
        return 1;
    }
    return 0;
}

//Function for initial collection of data
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

//Function to display the data
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

//Free Allocated Memory
void freeMemory(student** arr){
    free(*arr);
}

int main(){
    int n;
    printf("Enter number of records you want: ");
    scanf("%d", &n);

    //Declare array of struct students, then allocate space and collect data
    student* arr;
    allocateMemory(&arr, n);
    collectData(arr, n);

    while(1){
    //Menu to let user decide the sorting criteria
        printf("\
            Enter your choice: \n\
            1. Sort according to *ROLL* in *ASCENDING* order \n\
            2. Sort according to *ROLL* in *DESCENDING* order \n\
            3. Sort according to *SCORE* in *ASCENDING* order \n\
            4. Sort according to *SCORE* in *DESCENDING* order \n\
        ");
        
        int choice;
        scanf("%d", &choice);
        
        //Implementation of the sorting, by using the required comparison function

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

        printf("\n");
        printf("Press 0 to exit, any other key to continue: \n");
        int code;
        scanf("%d", &code);

        if (code == 0) break;
        else continue;
    }

    return 0;
}
