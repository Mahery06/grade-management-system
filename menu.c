#include <stdio.h>
#include "head file/student.h"
#include "head file/read_write.h"
#include "head file/login.h"

int main()
{
    int total = 0;
    int req = 0;

    while (1) {
        Student student[MAX_STUDENTS];
        Student result[MAX_STUDENTS];
        _abstract(&total, student);

        printf("========== 欢迎使用成绩管理系统！！ ==========\n");
        printf("请问您需要什么操作？\n1. 查询数据\n2. 插入数据\n3. 删除数据\n4. 打印数据\n5. 排序数据\n6. 统计汇总\n7. 修改数据\n8. 学业预警\n9. 学业规划报告\n");
        printf("请输入：");
        scanf("%d", &req);

        // 修改类操作需要管理员权限
        if ((req == 2 || req == 3 || req == 5 || req == 6 || req == 7) && !canModify()) {
            printf("权限不足\n");
        }
        // Search Module
        else if (req == 1) {
            searchMenu(total, student);
        }
        // Insert Module
        else if (req == 2) {
            Student item;
            printf("请输入新学生的学号、姓名、分数（用空格分隔）\n");
            printf("请输入：");
            scanf("%s%s%lf", item.id, item.name, &item.score);

            int ok = insertStudent(student, &total, item);
            if (ok == 1)
                printf("插入成功！😄\n");
            else if (ok == 0)
                printf("插入失败：学号已存在！😭\n");
            else
                printf("插入失败：学生人数已满！😭\n");
        }
        // Delete Module
        else if (req == 3) {
            int ok = deleteStudent(student, &total);
            if (ok) {
                _writeIn(total, student);
                printf("删除成功！\n");
            }
            else {
                printf("删除失败~\n");
            }
        }
        // Print Module
        else if (req == 4) {
            out(total, student);
        }
        // Sort Module
        else if (req == 5) {
            int choice;
            printf("请选择排序方式？\n1. 按分数排序\n2. 按学号排序\n");
            printf("请输入：");
            scanf("%d", &choice);

            if (choice == 1)
                sortByScore(student, total, result);
            else if (choice == 2)
                sortById(student, total, result);
            else
                printf("无效选项。\n");

            if (choice == 1 || choice == 2)
                out(total, result);
        }

        // Aggregate Module
        else if (req == 6) {
            aggregate(total, student);
        }

        // Modify Module
        else if (req == 7) {
            int ans = modify(total, student);
            if (ans)
                printf("修改成功！\n");
            else
                printf("修改失败~\n");
        }

        // Warning Module
        else if (req == 8) {
            warningMenu(student, total);
        }

        // 学业规划报告
        else if (req == 9) {
            tailored_report(total, student);
        }
        
        else {
            printf("无效选项。\n");
        }

        printf("您需要继续操作吗？(Y/N):");
        char cont;
        scanf(" %c", &cont);
        if (cont == 'N' || cont == 'n')
            break;
    }

    printf("再见！✋️");
    return 0;
}
