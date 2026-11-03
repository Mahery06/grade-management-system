#include <stdio.h>
#include "head file/student.h"

void aggregate(int total, Student std[])
{
    int count = 0;
    float min = 101, max = 0, sum = 0;
    for (int i = 0; i < total; i++)
    {
        sum += std[i].score;

        if (std[i].score < min)
            min = std[i].score;
        if (std[i].score > max)
            max = std[i].score;
    }

    float ave = sum / total;

    printf("\nThe highest score is %.2f\n", max);
    printf("The lowest score is %.2f\n", min);
    printf("The average score is %.2f\n", ave);

    for (int i = 0; i < total; i++)
        if (std[i].score >= 60)
            count++;

    printf("The rate of students who acquire score higher than 60.00 is %.2f%%.\n", (float)count / total * 100);
}