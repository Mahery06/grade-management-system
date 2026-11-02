#include <stdio.h>
#include <string.h>
#include "head file/student.h"

void sortById(
    const Student students[],
    int count,
    Student sorted[])
{
    memcpy(sorted, students, count * sizeof(Student));
    for (int i = 0; i < count - 1; i++)
    {
        int best = i;
        // 寻找剩余学号里学号最小的
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(sorted[j].id, sorted[best].id) < 0)
            {
                best = j;
            }
        }
        // 交换整个学生结构体
        if (best != i)
        {
            Student temp = sorted[i];
            sorted[i] = sorted[best];
            sorted[best] = temp;
        }
    }
    _writeIn(count, sorted);
}