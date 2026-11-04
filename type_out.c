#include <stdio.h>
#include "head file/template.h"

<<<<<<< HEAD
void out(int total, Student stu[]){
    for(int i=0;i<total;i++)
        printf("(学号:%s 姓名:%s 分数:%.2f)\n", stu[i].id, stu[i].name, stu[i].score );
=======
void out(int total, Student stu[])
{
    for (int i = 0; i < total; i++)
        printf("(ID:%s 姓名：%s 成绩：%.2f)\n", stu[i].id, stu[i].name, stu[i].score);
>>>>>>> 8f08cc56d650f198db8e6cf493b78ca15ed29f92
}