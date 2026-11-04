#include<stdio.h>
#include"head file/template.h"

void out(int total, Student stu[]){
    for(int i=0;i<total;i++)
        printf("(学号:%s 姓名:%s 分数:%.2f)\n", stu[i].id, stu[i].name, stu[i].score );
}