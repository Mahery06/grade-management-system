#include<stdio.h>
#include<string.h>
#include"head file/student.h"
#include"head file/read_write.h"

int modify(int total, Student stu[]){
    float score;
    int count=3;
    while(count--){

        char id[11]={0};
        printf("请输入您需要修改的学生学号：");
        scanf("%s",id);

        for(int i=0; i<total;i++){
        if(! strcmp(id, stu[i].id)){
            printf("请输入最新的分数: ");
            scanf("%f", &score);
            stu[i].score = score;
            _writeIn(total, stu);
            return 1;
        }
    }
    printf("未找到此同学，请核对您的输入并再次输入。您还有 %d 次机会！", count);
    }
    return 0;
    
}