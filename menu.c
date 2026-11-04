#include<stdio.h>
#include"head file/student.h"
#include"head file/read_write.h"
#include"head file/login.h"

int main(){

    int total=0;
    int req = 0;
    

    while(1){
    printf("========== 欢迎使用成绩管理系统！！ ==========\n ");
    printf("请问您需要什么操作？\n1. 查询数据\n2. 插入数据\n3. 删除数据\n4. 打印数据\n5. 排序数据\n6. 统计汇总\n7. 修改数据\n8. 学业预警\n9. 学业规划报告\n");
    printf("请输入：");
    scanf("%d",&req);

    Student student[MAX_STUDENTS];
    _abstract(&total, student);
    Student result[MAX_STUDENTS];

    if((req == 2 || req == 3 || req == 5 || req == 6 || req ==7 ) && !canModify()){
        printf("权限不足\n");
    }
     // Search Module
    else if(req == 1)
        searchMenu(total, student);
       
    // Insert Module
    else if(req == 2) {
        Student item;

        printf("请输入新学生的学号、姓名、分数（用空格分隔）\n");
        printf("请输入：");
        scanf("%s%s%lf", item.id, item.name, &item.score);

        insertStudent(student, &total, item);
    
    }

    // Delete Module
    else if(req == 3){ int ans = deleteStudent(student, &total);
            if (ans == 1)
            {
                printf("操作成功！😄\n");
                _writeIn(total, student);
            }
            else
                printf("操作失败！😭\n");}


    // Print Module
    else if(req==4)out(total,student);

    // Sort Module
    else if(req==5){
        printf("请选择排序方式？\n1. 按分数排序\n2. 按学号排序\n");
        printf("请输入：");
        scanf("%d",&req);
        if (req == 1) sortByScore(student, total, result);
        else if (req == 2)
                sortById(student, total, result);
        else
            {
                printf("无效选项。\n");
                continue;
            }
            out(total, result);
        }

    // Aggregate Module
    else if (req == 6) aggregate(total, student);
    
    else if (req == 7) {
        
        int ans = modify(total, student);
        if (ans) printf("修改成功！\n");
        else printf("修改失败~\n");
    }

    else if(req == 8)
    {
        warningMenu(student, total);
    }

     // 学业规划报告
    else if(req == 9) tailored_report(total, student);

    printf("您需要继续操作吗？(Y/N):");
    char cont;
    scanf(" %c", &cont);
    if(cont == 'N' || cont == 'n') break;
    }

    printf("再见！✋️");
    return 0;

}
