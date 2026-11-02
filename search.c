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

    printf("请输入要查询的学号：");
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
        printf("学号：%s  姓名：%s  成绩：%.2f\n",
               result[0].id, result[0].name, result[0].score);
        *n = 1;
        return found;
    }

    *n = 0;

    printf("查无此人！学号 %s 不存在。\n", key);
    return -1;
}

int searchByName(Student stu[], int total, int *n, Student result[])
{
    char key[NAME_LENGTH];
    int i, count = 0;

    printf("请输入要查询的姓名：");
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
        printf("查无此人！姓名 %s 不存在。\n", key);
        return -1;
    }

    *n = count;
    return 1;
}

int searchByScore(Student stu[], int total, int *n, Student result[])
{
    double m;
    int i, count = 0;

    printf("请输入成绩上限 m:");
    scanf("%lf", &m);

    for (i = 0; i < total && count < MAX_RESULT; i++)
    {
        if (stu[i].score < m)
        {
            result[count] = stu[i]; /* ① 返回给调用者 */

            count++;
        }
    }

    if (count == 0)
    {
        printf("没有成绩小于 %.2f 的学生。\n", m);
        return -1;
    }
    *n = count;

    return 1;
}