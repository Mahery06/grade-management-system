#include <stdio.h>
#include "head file/student.h"
#include "head file/read_write.h"
#include "head file/login.h"

int main()
{
    int total = 0;
    int req = 0;
    int ctrl = 1;
    while (ctrl) {
        Student student[MAX_STUDENTS];
        Student result[MAX_STUDENTS];
        _abstract(&total, student);

        if(g_role == 2){
            printf("========== 欢迎使用成绩管理系统！！ ==========\n");
            printf("请问您需要什么操作？\n"
                "\033[33m1. 查询数据\033[0m\n"
                "\033[33m2. 插入数据\033[0m\n"
                "\033[33m3. 删除数据\033[0m\n"
                "\033[33m4. 打印数据\033[0m\n"
                "\033[33m5. 排序数据\033[0m\n"
                "\033[33m6. 统计汇总\033[0m\n"
                "\033[33m7. 修改数据\033[0m\n"
                "\033[33m8. 学业预警\033[0m\n"
            );

            while(1){
                printf("请输入：");
                scanf("%d", &req);
                if(req > 8){
                printf("\033[31m错误信息! 请重新输入。\033[0m\n");
                continue;
                }
                break;
            }
        }

        if(g_role == 1){
            printf("========== 欢迎使用成绩管理系统！！ ==========\n");
            printf("请问您需要什么操作？\n"
                "\033[33m1. 查询数据\033[0m\n"
                "\033[33m2. 学业规划报告\033[0m\n");

            while(1){
                printf("请输入：");
                scanf("%d", &req);
                if(req > 2){
                printf("\033[31m1错误信息! 请重新输入。\033[0m\n");
                continue;
                }
                break;
            }
            if (req == 2 ) req = 9;
        }

        // Search Module
        if (req == 1) {
            int bol =1;
            while(bol){
                searchMenu(total, student);

                printf("需要继续进行查询操作吗？\n请输入(Y/N): ");
                char choice;
                scanf(" %c", &choice);
                askClear(&bol, choice);
            }
            

        }
        // Insert Module
        else if (req == 2) {
            int bol = 1;
            while(bol){
            Student item;
            printf("请输入新学生的学号、姓名、分数（用空格分隔）\n");
            printf("请输入：");
            scanf("%s%s%lf", item.id, item.name, &item.score);

            int ok = insertStudent(student, &total, item);
            if (ok == 1)
                printf("\033[32m插入成功！\033[0m\n\n");
            else if (ok == 0)
                printf("\033[31m插入失败：学号已存在！\033[0m\n\n");
            else{
                printf("\033[35m插入失败：学生人数已满！\n即将返回主菜单!\033[0m\n\n");

                bol = 0;

                Sleep(3000);
                system("cls");
                continue;
            }
                
                
            printf("需要继续进行插入操作吗？\n请输入(Y/N): ");
            char choice;
            scanf(" %c", &choice);
            askClear(&bol, choice);
            }
            
        }
        // Delete Module
        else if (req == 3) {
            int bol = 1;
            while(bol){
                int ok = deleteStudent(student, &total);
                if (ok) {
                    _writeIn(total, student);
                    printf("\033[32m删除成功！\033[0m\n\n");
                }
                else {
                    printf("\033[31m删除失败~\033[0m\n\n");
                }

            printf("需要继续进行修改操作吗？\n请输入(Y/N): ");
            char choice;
            scanf(" %c", &choice);
            askClear(&bol, choice);
            }
        }

        // Print Module
        else if (req == 4) {
            out(total, student);
            getchar();
            printf("按回车键继续...\n");
            getchar();
            system("cls");
        }

        // Sort Module
        else if (req == 5) {
            int bol = 1;
            while(bol){
                 int choice;
                printf("请选择排序方式？\n\033[33m1. 按分数排序\n2. 按学号排序\033[0m\n");
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
            
            printf("需要继续进行修改操作吗？\n请输入(Y/N): ");
            char c;
            scanf(" %c", &c);
            askClear(&bol, c);       
            }
           
        }

        // Aggregate Module
        else if (req == 6) {
            aggregate(total, student);
            getchar();
            printf("按回车键继续...\n");
            getchar();
            printf("即将返回主菜单！\n");
            Sleep(3000);
            system("cls");
        }

        // Modify Module
        else if (req == 7) {
            int bol = 1;
            while(bol){
                int ans = modify(total, student);
            if (ans)
                printf("\033[32m修改成功！\033[0m\n\n");
            else
                printf("\033[31m修改失败\033[0m\n\n");
            
            printf("需要继续进行修改操作吗？\n请输入(Y/N): ");
            char choice;
            scanf(" %c", &choice);
            askClear(&bol, choice);
            }
            
        }

        // Warning Module
        else if (req == 8) {
            warningMenu(student, total);
            getchar();
            printf("按回车键继续...\n");
            getchar();
            printf("即将返回主菜单！\n");
            Sleep(3000);
            system("cls");
        }

        // 学业规划报告
        else if (req == 9) {
            
            tailored_report(total, student);
            printf("\n");
            
            getchar();
            printf("按回车键继续...\n");
          
            getchar();
            printf("即将返回主菜单！\n");
            Sleep(3000);
            system("cls");
            
        }

       
        printf("是否需要退出系统？\n");

        while(1){
            printf("请输入(Y/N):");
            char ch;
            scanf(" %c",&ch);
            if(ch == 'y' || ch == 'Y') {ctrl = 0;break;}
            else if (ch == 'N' || ch == 'n') {system("cls");break;}
            else{
                printf("请正确输入需要！\n");
            }
        }
        
    }

    printf("再见！✋️");
    Sleep(3000);
    return 0;
}
