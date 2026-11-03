#include <stdio.h>
#include "head file/student.h"
#include "head file/read_write.h"

int main()
{

    int total = 0;
    int req = 0;
    Student student[MAX_STUDENTS] = {0};
    Student result[MAX_STUDENTS] = {0};

    _abstract(&total, student);

    while (1)
    {
        printf("What's your request?\n1. Search Data. \n2. Insert Data.\n3. Delete Data.\n4. Print Data.\n5. Sort Data.\n");
        if (scanf("%d", &req) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            continue;
        }

        // Search Module
        if (req == 1)
        {
            int ans;

            int n = 0;
            int option;
            printf("What's your specific request?\n1. Search by ID.\n2. Search by Name.\n3. Search by Score.\n");
            if (scanf("%d", &option) != 1)
                break;
            if (option == 1)
                ans = searchById(student, total, &n, result);
            else if (option == 2)
                ans = searchByName(student, total, &n, result);
            else if (option == 3)
                ans = searchByScore(student, total, &n, result);
            else
            {
                printf("Invalid option.\n");
                continue;
            }
            if (ans == -1)
            {
                printf("Operation Unsuccessful!😭\n");
            }
            else
            {
                printf("Operation Successful!😄\nThe searched content shows below:\n");
                out(n, result);
            }
        }
        // Insert Module
        else if (req == 2)
        {
            Student item = {0};
            printf("Please type in the ID, name, score of the new student. (Divided by spaces)\n");
            if (scanf("%19s%39s%lf", item.id, item.name, &item.score) != 3)
            {
                printf("Invalid student input.\n");
                break;
            }
            if (item.score < 0 || item.score > 100)
            {
                printf("Invalid score.\n");
                continue;
            }
            int ans = insertStudent(student, &total, item);
            if (ans == 1)
                printf("Operation Successful!\n");
            else if (ans == 0)
                printf("ID already exists.\n");
            else
                printf("Storage Maximal!\n");
        }

        // Delete Module
        else if (req == 3)
        {
            int ans = deleteStudent(student, &total);
            if (ans == 1)
            {
                printf("Operation Successful!😄\n");
                _writeIn(total, student);
            }
            else
                printf("Operation Unsuccessful!😭\n");
        }

        // Print Model
        else if (req == 4)
            out(total, student);

        // Sort Model
        else if (req == 5)
        {
            int option;
            printf("What's your specific request? \n1. Sort by score.\n2. Sort by ID.\n");
            if (scanf("%d", &option) != 1)
                break;
            if (option == 1)
                sortByScore(student, total, result);
            else if (option == 2)
                sortById(student, total, result);
            else
            {
                printf("Invalid option.\n");
                continue;
            }
            out(total, result);
        }
        else
        {
            printf("Invalid request.\n");
            continue;
        }

        printf("Do you want to continue?(Y/N)");
        char cont;
        if (scanf(" %c", &cont) != 1 || cont == 'N' || cont == 'n')
            break;
    }
    printf("Goodbye!✋️");
    return 0;
}
