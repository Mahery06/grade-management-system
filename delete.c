
#include <stdio.h>
#include "head file/student.h"

// 函数deleteStudent为int型，成功返回1，失败返回0
int deleteStudent(
    Student students[],
    int *count)
{
    int n = 0;
    int i;

    // 存储查询到的学生
    Student result[1];

    // 1. 调用查询模块，获取学生下标
    int pos = searchById(students, *count, &n, result);

    // 2. 判断学生是否存在
    if (pos < 0)
    {
        return 0;
    }

    // 3. 将后续学生依次向前移动
    for (i = pos; i < *count - 1; i++)
    {
        students[i] = students[i + 1];
    }

    // 4. 更新学生总人数
    (*count)--;

    return 1;
}
