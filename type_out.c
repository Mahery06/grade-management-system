#include <stdio.h>
#include "head file/template.h"

void out(int total, Student stu[])
{
    for (int i = 0; i < total; i++)
        printf("(ID:%s 姓名：%s 成绩：%.2f)\n", stu[i].id, stu[i].name, stu[i].score);
}