/*
 * warning.c - 学业预警模块
 *
 * 规则：成绩低于 60 分即视为学业预警。
 * 本模块只读，不修改 student.dat。
 */

#include <stdio.h>
#include <string.h>

#include "head file/student.h"

#define WARNING_THRESHOLD 60.0

/* 判断一个学生是否处于学业预警状态 */
int isWarning(const Student *student)
{
    return student->score < WARNING_THRESHOLD;
}

/* 按成绩升序排列下标；同分时按学号升序 */
static void sortIndexByScore(const Student students[], int index[], int n)
{
    int i;
    int j;
    int best;

    for (i = 0; i < n - 1; i++)
    {
        best = i;

        for (j = i + 1; j < n; j++)
        {
            if (students[index[j]].score < students[index[best]].score ||
                (students[index[j]].score == students[index[best]].score &&
                 strcmp(students[index[j]].id, students[index[best]].id) < 0))
            {
                best = j;
            }
        }

        if (best != i)
        {
            int temp = index[i];
            index[i] = index[best];
            index[best] = temp;
        }
    }
}

void warningMenu(const Student students[], int count)
{
    int index[MAX_STUDENTS];
    int warningCount = 0;
    int i;
    double sum = 0.0;

    if (count > MAX_STUDENTS)
        count = MAX_STUDENTS;

    printf("\n========== 学业预警 ==========\n");
    printf("预警线：%.2f 分（成绩低于 %.2f 分即预警）\n\n",
           WARNING_THRESHOLD, WARNING_THRESHOLD);

    if (count <= 0)
    {
        printf("系统中没有学生记录。\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (isWarning(&students[i]))
        {
            index[warningCount++] = i;
            sum += students[i].score;
        }
    }

    if (warningCount == 0)
    {
        printf("全部 %d 名学生均达到 %.2f 分，没有预警学生。\n",
               count, WARNING_THRESHOLD);
        return;
    }

    sortIndexByScore(students, index, warningCount);

    printf("共 %d 名学生，预警 %d 人，预警率 %.2f%%。\n\n",
           count, warningCount,
           (double)warningCount / (double)count * 100.0);

    printf("学号\t\t姓名\t\t成绩\t     距及格线\n");
    printf("----------------------------------------------------------\n");

    for (i = 0; i < warningCount; i++)
    {
        const Student *s = &students[index[i]];

        printf("%s\t%s\t        %.2f\t      %.2f\n",
               s->id, s->name, s->score,
               WARNING_THRESHOLD - s->score);
    }

    printf("----------------------------------------------------------\n");
    printf("预警学生平均分：%.2f，最低分：%.2f\n",
           sum / warningCount, students[index[0]].score);
}