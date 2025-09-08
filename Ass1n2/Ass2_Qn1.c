#include <stdio.h>
#include <stdlib.h>

// Structure that represents a Student record in the file
typedef struct Student{
    int roll;           // Unique roll number
    char name[33];      // Name (up to 32 chars + null)
    int score[5];       // Scores in 5 subjects
    int flag;           // Used for deletion: 1 = active, 0 = deleted
}Student;

/* ------------------ Search Functions ------------------ */

// Search record by roll (only active students considered)
// Returns the position of record in file (1-based index), else 0
int searchRecord(char fn[], int roll){
    FILE* fp;
    fp = fopen(fn, "r");
    Student stu;
    int k = 0;

    while (fread(&stu, sizeof(Student), 1, fp)){
        k++;
        if (stu.roll == roll && stu.flag!=0){
            fclose(fp);
            return k;   // return the position in file
        }
    }

    fclose(fp);
    return 0;
}

// Similar to above but ignores the flag (used for retrieving deleted records)
int searchRecordNoFlag(char fn[], int roll){
    FILE* fp;
    fp = fopen(fn, "r");
    Student stu;
    int k = 0;

    while (fread(&stu, sizeof(Student), 1, fp)){
        k++;
        if (stu.roll == roll){
            fclose(fp);
            return k;
        }
    }

    fclose(fp);
    return 0;
}

/* ------------------ Display Functions ------------------ */

// Display all student records that are not deleted
void displayAll(char fn[]){
    FILE* fp;
    fp = fopen(fn, "r");
    Student stu;

    int numRecords = 0; // flag to track if any valid records were displayed


    if (feof(fp)){
        printf("The file is empty, nothing to display\n");
        return;
    }

    else{
        printf("The record of students are as follows: \n");

        // keep reading until file ends
        while (fread(&stu, sizeof(Student), 1, fp)){

            if (stu.flag == 0) continue; // skip deleted records

            else{
                printf("Roll-> %d || Name-> %s || Score: %d, %d, %d, %d, %d\n",
                       stu.roll, stu.name,
                       stu.score[0], stu.score[1], stu.score[2],
                       stu.score[3], stu.score[4]);
                numRecords = 1; // mark that at least one valid record was found
            } 
        }

        // if no valid record was displayed, tell the user
        if (!numRecords){
            printf("The file is empty, nothing to display\n");
            return;
        }
    }

    fclose(fp);
}

// Shows details of a specific student with given roll
void displaySearched(char fn[], int roll){
    FILE* fp;
    fp = fopen(fn, "r");
    Student stu;

    int k = searchRecord(fn, roll);

    if (k==0){
        printf("The given roll doesn't exists!\n");
        return;
    }
    else{
        printf("Record found: \n");
        fseek(fp, (k-1)*sizeof(Student), 0); // move to exact record
        fread(&stu, sizeof(Student), 1, fp);

        printf("Roll-> %d || Name-> %s || Score: %d, %d, %d, %d, %d\n",
               stu.roll, stu.name,
               stu.score[0], stu.score[1], stu.score[2],
               stu.score[3], stu.score[4]);
    }

    fclose(fp);
}

/* ------------------ Writing and Adding ------------------ */

// Overwrite file and write n fresh records
void writeRecords(char fn[], int n){
    FILE* fp;
    fp = fopen(fn, "w");   // opening in write mode clears old data
    Student stu;

    int i = 1;
    while (i <= n){

        printf("Enter the details of Student %d: \n", i);

        // Input roll
        printf("Enter roll: ");
        scanf("%d", &stu.roll);

        // check for duplicate roll number
        int k = searchRecord(fn, stu.roll);
        if (k!=0){
            printf("Roll already exists, can't have same roll...\n");
            continue;
        }

        // Input name
        printf("Enter name: ");
        getchar(); // to consume leftover newline
        scanf("%[^\n]", stu.name);

        // Input scores
        printf("Enter the score obtained in 5 subjects-> \n");
        for (int i=0; i<5; i++){
            printf("Subject %d: ", i+1);
            scanf("%d", &stu.score[i]);
        }

        stu.flag = 1;   // mark as active

        // Write record into file
        fwrite(&stu, sizeof(Student), 1, fp);
        fflush(fp);

        i++;
        printf("\n");
    }

    fclose(fp);
}

// Append one new record to existing file
void addRecord(char fn[]){
    FILE* fp;
    fp = fopen(fn, "a");   // append mode
    Student stu;

    printf("Enter the details of the New Student: \n");

    printf("Enter roll: ");
    scanf("%d", &stu.roll);

    // check duplicate roll
    int k = searchRecord(fn, stu.roll);
    if (k!=0){
        printf("Roll already exists!\n");
        return;
    }

    // Input rest details
    printf("Enter name: ");
    getchar();
    scanf("%[^\n]", stu.name);
    
    printf("Enter the score obtained in 5 subjects-> \n");
    for (int i=0; i<5; i++){
        printf("Subject %d: ", i+1);
        scanf("%d", &stu.score[i]);
    }

    stu.flag = 1;

    fwrite(&stu, sizeof(Student), 1, fp);

    fclose(fp);

    printf("\n");
}

/* ------------------ Edit Functions ------------------ */

// Edit only the name of a student
void editName(char fn[], int roll){
    FILE* fp;
    fp = fopen(fn, "r+");  // open in read+write mode
    Student stu;

    int k = searchRecord(fn, roll);

    if (k==0){
        printf("The given roll doesn't exists!\n");
        return;
    }
    else{
        // move to the record
        fseek(fp, (k-1)*sizeof(Student), 0);
        fread(&stu, sizeof(Student), 1, fp);
        fseek(fp, -1*sizeof(Student), 1);

        printf("Enter new name: ");
        getchar();
        scanf("%[^\n]", stu.name);

        // overwrite updated record
        fwrite(&stu, sizeof(Student), 1, fp);
    }

    fclose(fp);
}

// Edit one subject's score
void editScore(char fn[], int roll){
    FILE* fp;
    fp = fopen(fn, "r+");
    Student stu;

    int k = searchRecord(fn, roll);

    if (k==0){
        printf("The given roll doesn't exists!\n");
        return;
    }
    else{
        fseek(fp, (k-1)*sizeof(Student), 0);
        fread(&stu, sizeof(Student), 1, fp);
        fseek(fp, -1*sizeof(Student), 1);

        int i;
        printf("Which subject's score you want to change: ");
        scanf("%d", &i);
        printf("\n");

        if (i>5 || i<=0){
            printf("Invalid Input!...Exiting...\n");
            return;
        }

        printf("Enter new score: ");
        scanf("%d", &stu.score[i-1]);

        fwrite(&stu, sizeof(Student), 1, fp);
    }

    fclose(fp);
}

/* ------------------ Delete and Retrieve ------------------ */

// Temporary delete: just mark the flag = 0
void tempDelete(char fn[], int roll){
    FILE* fp;
    fp = fopen(fn, "r+");
    Student stu;

    int k = searchRecord(fn, roll);

    if (k==0){
        printf("The given roll doesn't exists!\n");
        return;
    }
    else{
        fseek(fp, (k-1)*sizeof(Student), 0);
        fread(&stu, sizeof(Student), 1, fp);
        fseek(fp, -1*sizeof(Student), 1);

        stu.flag = 0;   // mark as deleted

        printf("Data deletion completed\n");

        fwrite(&stu, sizeof(Student), 1, fp);
    }

    fclose(fp);
}

// Undo a temporary delete (set flag back to 1)
void retrieveDeleted(char fn[], int roll){
    FILE* fp;
    fp = fopen(fn, "r+");
    Student stu;

    int k = searchRecordNoFlag(fn, roll);

    fseek(fp, (k-1)*sizeof(Student), 0);
    fread(&stu, sizeof(Student), 1, fp);

    if (k==0){
        printf("The given roll doesn't exists!\n");
        return;
    }
    else if (stu.flag != 0){
        printf("The record is not deleted!\n");
        return;
    }
    else{
        // move to record and update flag
        fseek(fp, (k-1)*sizeof(Student), 0);
        fread(&stu, sizeof(Student), 1, fp);
        fseek(fp, -1*sizeof(Student), 1);

        stu.flag = 1;

        printf("Data retrieved successfully\n");

        fwrite(&stu, sizeof(Student), 1, fp);
    }

    fclose(fp);
}

// Show all records that are deleted
void displayDeleted(char fn[]){
    FILE* fp;
    fp = fopen(fn, "r");
    Student stu;

    int numRecords = 0; // flag to track if any deleted records were displayed

    if (feof(fp)){
        printf("The file is empty, nothing to display\n");
        return;
    }

    else{
        printf("The record of deleted students are as follows: \n");

        while (fread(&stu, sizeof(Student), 1, fp)){

            if (stu.flag == 1) continue; // skip active, show deleted

            else{
                printf("Roll-> %d || Name-> %s || Score: %d, %d, %d, %d, %d\n",
                       stu.roll, stu.name,
                       stu.score[0], stu.score[1], stu.score[2],
                       stu.score[3], stu.score[4]);
                numRecords = 1; // mark that at least one valid record was found
            } 
        }

        // if no deleted record was displayed, tell the user
        if (!numRecords){
            printf("There are no deleted files to display\n");
            return;
        }
    }

    fclose(fp);
}

// Permanently remove record by rewriting file without it
void permanentDelete(char fn[], int roll){
    FILE* fp; FILE* temp;
    fp = fopen(fn, "r+");
    temp = fopen("temp", "w");
    Student stu;

    int k = searchRecordNoFlag(fn, roll);

    if (k==0){
        printf("The given roll doesn't exists!\n");
        return;
    }
    else{
        // copy everything except the one to be deleted
        while (fread(&stu, sizeof(Student), 1, fp)){
            if(stu.roll != roll){
                fwrite(&stu, sizeof(Student), 1, temp);
            }
        }
    }

    printf("Data deleted PERMANENTLY\n");

    fclose(fp);
    fclose(temp);

    remove(fn);
    rename("temp", fn);    // rename temp as main file
}

/* ------------------ Main Program ------------------ */

int main(){

    char fn[] = "students";   // file name
    int choice;

    printf("\nEnter your choice: \n");

    while(1){
        // Menu-driven system
        printf("\
        0. Write records from start \n\
        1. Display all records \n\
        2. Search a record by roll \n\
        3. Add a record \n\
        4. Edit name \n\
        5. Edit score \n\
        6. Delete a record \n\
        7. Display deleted records \n\
        8. Retrieve a deleted record \n\
        9. Permanently delete a record \n\
        ");

        scanf("%d", &choice);
        
        int roll, n;

        switch (choice)
        {
        case 0:
            printf("Enter the number of initial records you want: ");
            scanf("%d", &n);
            printf("\n");

            writeRecords(fn, n);
            break;

        case 1:
            displayAll(fn);
            break;

        case 2:
            printf("Enter the roll you want to search for: ");
            scanf("%d", &roll);
            printf("\n");

            displaySearched(fn, roll);
            break;

        case 3:
            addRecord(fn);
            break;

        case 4:
            printf("Enter the roll you want to edit: ");
            scanf("%d", &roll);
            editName(fn, roll);
            break;

        case 5:
            printf("Enter the roll you want to edit: ");
            scanf("%d", &roll);
            editScore(fn, roll);
            break;

        case 6:
            printf("Enter the roll you want to delete: ");
            scanf("%d", &roll);
            tempDelete(fn, roll);
            break;

        case 7:
            displayDeleted(fn);
            break;

        case 8:
            printf("Enter the roll you want to retrieve: ");
            scanf("%d", &roll);
            retrieveDeleted(fn, roll);
            break;

        case 9:
            printf("Enter the roll you want to delete PERMANENTLY: ");
            scanf("%d", &roll);
            permanentDelete(fn, roll);
            break;
        
        default:
            printf("Please enter a valid choice! \n");
            break;
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
