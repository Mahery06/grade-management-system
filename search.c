#include <stdio.h>
#include <string.h>
#include "head file/template.h"

int searchById(Student stu[], int total, int *n, Student result[])
{
    char key[ID_LENGTH];
    int low = 0, high = total - 1, mid, found = -1;
    int i, j;
    Student tmp;

    /*二分查找前先进行升序排序*/
    for (i = 0; i < total - 1; i++)
    {
        for (j = 0; j < total - 1 - i; j++)
        {
            if (strcmp(stu[j].id, stu[j + 1].id) > 0)
            {
                tmp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = tmp;
            }
        }
    }

    printf("Please enter the student ID you want to query: ");
    scanf("%19s", key);

    while (low <= high)
    {
        mid = (low + high) / 2;
        int cmp = strcmp(stu[mid].id, key);
        if (cmp == 0)
        {
            found = mid;
            break;
        }
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    if (found != -1)
    {
        result[0] = stu[found];
        *n = 1;
        return found;
    }

    *n = 0;

    printf("No such person found! Student ID %s does not exist.\n", key);
    return -1;
}

int searchByName(Student stu[], int total, int *n, Student result[])
{
    char key[NAME_LENGTH];
    int i, count = 0;

    printf("Please enter the student NAME you want to query: ");
    scanf("%19s", key);

    for (i = 0; i < total && count < MAX_RESULT; i++)
    {
        if (strcmp(stu[i].name, key) == 0)
        {
            result[count] = stu[i];
            count++;
        }
    }

    if (count == 0)
    {
        printf("No such person found! Student Name %s does not exist.\n", key);
        return -1;
    }

    *n = count;
    return 1;
}

int searchByScore(Student stu[], int total, int *n, Student result[])
{
    double m;
    int i, count = 0;

    printf("Please enter the upper score limit m :");
    scanf("%lf", &m);

    for (i = 0; i < total && count < MAX_RESULT; i++)
    {
        if (stu[i].score < m)
        {
            result[count] = stu[i]; 

            count++;
        }
    }

    if (count == 0)
    {
        printf("No students have a score lower than %.2f.\n", m);
        return -1;
    }
    *n = count;

    return 1;
}