#include<stdio.h>
#include"head file/student.h"

void aggregate(int total, Student std[]){
    int count1 = 0, count2 = 0;
    float min = 101, max = 0, sum = 0;
    for(int i=0; i<total; i++){
        sum += std[i].score;

        if(std[i].score < min) min = std[i].score;
        if(std[i].score > max) max = std[i].score;
    }

    float ave = sum/total; 

    printf("\nThe highest score is %.2f\n", max);
    printf("The lowest score is %.2f\n",  min);
    printf("The average score is %.2f\n", ave);

    for(int i=0; i<total; i++) 
        if (std[i].score > ave) count1++;
        if (std[i].score < 60) count2++;
    
    printf("The number of students who acquire score higher than the average one is %d.\n",count1);
    printf("The number of students who acquire score lower than 60.00 is %d.\n",count2);
    

}