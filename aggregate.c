#include<stdio.h>
#include"head file/student.h"

void aggregate(int total, Student std[]){
    int count = 0; 
    float min = 101, max = 0, sum = 0;
    for(int i=0; i<total; i++){
        sum += std[i].score;

        if(std[i].score < min) min = std[i].score;
        if(std[i].score > max) max = std[i].score;
    }

    float ave = sum/total; 

    printf("\n最高分是 %.2f\n", max);
    printf("最低分是 %.2f\n",  min);
    printf("平均分是 %.2f\n", ave);

    for(int i=0; i<total; i++)
        if (std[i].score >= 60) count++;

    printf("分数在 60.00 分以上的学生比例为 %.2f%%。\n", (float)count/total*100);
    

}