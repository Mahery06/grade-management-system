#include <stdio.h>
#include "head file/student.h"
#include "head file/read_write.h"
#include "head file/login.h"

int main()
{

    int total = 0;
    int req = 0;

    while (1)
    {
        printf("========== 欢迎使用学生成绩管理系统！！ ==========\n ");
        printf("请选择您需要的操作：\n1. 查询学生信息 \n2. 插入学生信息\n3.删除学生信息\n4. 显示全部学生信息\n5. 学生信息排序\n6.学生成绩统计\n");
        printf("请输入选项(1-6):");
        scanf("%d", &req);

        Student student[MAX_STUDENTS];
        _abstract(&total, student);
        Student result[MAX_STUDENTS];

        if ((req == 2 || req == 3 || req == 5 || req == 6) && !canModify())
        {
            printf("权限不足：普通用户只能查询；添加和删除操作仅对管理员开放。\n");
        }
        // Search Module
        else if (req == 1)
        {
            int ans;

            int n = 0;
            printf("请选择您的具体请求：\n1. 按ID查询.\n2. 按姓名查询.\n3. 按成绩查询.\n");
            scanf("%d", &req);

            Student student[MAX_STUDENTS];
            _abstract(&total, student);
            Student result[MAX_STUDENTS];

            if ((req == 2 || req == 3 || req == 5 || req == 6) && !canModify())
            {
                printf("操作成功!😄\n\n");
                printf("查询结果如下:\n");
                for (int i = 0; i < n; i++)
                    printf("(ID:%s 姓名:%s 成绩:%.2f)\n", result[i].id, result[i].name, result[i].score);

                printf("是否需要AI定制报告?(Y/N):");
                char wantReport;
                scanf(" %c", &wantReport);
                if (wantReport == 'Y' || wantReport == 'y')
                    tailored_report(result, n);
            }
            // Search Module
            else if (req == 1)
            {
                int ans;

                printf("请输入新学生的ID、姓名和成绩(用空格分隔):\n");
                printf("请输入:");
                scanf("%s%s%lf", item.id, item.name, &item.score);

                scanf("%d", &req);

                Student student[MAX_STUDENTS];
                _abstract(&total, student);
                Student result[MAX_STUDENTS];

                if ((req == 2 || req == 3 || req == 5 || req == 6) && !canModify())
                {
                    printf("权限不足：普通用户只能查询；添加和删除操作仅对管理员开放。\n");
                }
                else
                    printf("操作失败!😭\n");
            }

            // Print Module
            else if (req == 4)
                out(total, student);

            // Sort Module
            else if (req == 5)
            {
                printf("请选择您的具体请求？ \n1. 按成绩排序.\n2. 按ID排序.\n");
                printf("请输入：");
                scanf("%d", &req);
                if (req == 1)
                    sortByScore(student, total, result);
                else if (req == 2)
                    sortById(student, total, result);
                else
                {
                    int ans;

                    int n = 0;
                    printf("请选择您的具体请求：\n1. 按ID查询.\n2. 按姓名查询.\n3. 按成绩查询.\n");
                    scanf("%d", &req);
                    if (req == 1)
                        ans = searchById(student, total, &n, result);
                    else if (req == 2)
                        ans = searchByName(student, total, &n, result);
                    else
                        ans = searchByScore(student, total, &n, result);

                    if (ans == -1)
                        printf("操作失败!😭\n");
                    else
                    {
                        printf("操作成功!😄\n\n");
                        printf("查询结果如下:\n");
                        for (int i = 0; i < n; i++)
                            printf("(ID:%s 姓名:%s 成绩:%.2f)\n", result[i].id, result[i].name, result[i].score);

                        printf("是否需要AI定制报告?(Y/N)");
                        char wantReport;
                        scanf(" %c", &wantReport);
                        if (wantReport == 'Y' || wantReport == 'y')
                            tailored_report(result, n);
                    }
                }
                // Insert Module
                else if (req == 2)
                {
                    Student item;

                    printf("请输入新学生的ID、姓名和成绩(用空格分隔):\n");

                    scanf("%s%s%lf", item.id, item.name, &item.score);

                    insertStudent(student, &total, item);
                }

                // Delete Module
                else if (req == 3)
                {
                    int ans = deleteStudent(student, &total);
                    if (ans == 1)
                    {
                        printf("操作成功!😄\n");
                        _writeIn(total, student);
                    }
                    else
                        printf("操作失败!😭\n");
                }

                // Print Module
                else if (req == 4)
                    out(total, student);

                // Sort Module
                else if (req == 5)
                {
                    printf("请选择您的具体请求？ \n1. 按成绩排序.\n2. 按ID排序.\n");
                    scanf("%d", &req);
                    if (req == 1)
                        sortByScore(student, total, result);
                    else if (req == 2)
                        sortById(student, total, result);
                    else
                    {
                        printf("非法输入\n");
                        continue;
                    }
                    out(total, result);
                }

                // Aggregate Module
                else if (req == 6)
                    aggregate(total, student);

                printf("是否需要继续?(Y/N)");
                char cont;
                scanf(" %c", &cont);
                if (cont == 'N' || cont == 'n')
                    break;
            }

            // Aggregate Module
            else if (req == 6)
                aggregate(total, student);

            printf("是否需要继续?(Y/N):");
            char cont;
            scanf(" %c", &cont);
            if (cont == 'N' || cont == 'n')
                break;
        }
    }
