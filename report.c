#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head file/student.h"

void tailored_report(int total, Student stu[]) {

    
    int count=3;
    int idx = -1;
    while(count--){
        printf("同学，你好。你的学号是：");
        char id[10]={0};
        scanf("%s", id);
    
        for(int i=0; i<total; i++){
            if(! strcmp(id, stu[i].id)){
                idx = i;
                break;
            }
        }
        if(idx == -1) printf("错误！请重新输入信息。你还有 %d 次机会。\n", count );
        
    }
    if(! count){
        printf("错误超过最大限度。即将退出！\n");
        return;
    }
    
    char path[40]={0};
    char cont[1000]={0};
    char name[10]={0};
    strcpy(path, "report_resource/report");
   
        
    strcpy(name,stu[idx].name);
    if(stu[idx].score<60) strcat(path, "0-60.txt");
    else if(stu[idx].score>=60 && stu[idx].score<70) strcat(path, "60-70.txt");
    else if(stu[idx].score>=70 && stu[idx].score<75) strcat(path, "70-75.txt");
    else if(stu[idx].score>=75 && stu[idx].score<80) strcat(path, "75-80.txt");
    else if(stu[idx].score>=80 && stu[idx].score<85) strcat(path, "80-85.txt");
    else if(stu[idx].score>=85 && stu[idx].score<90) strcat(path, "85-90.txt");
    else if(stu[idx].score>=90 && stu[idx].score<95) strcat(path, "90-95.txt");
    else if(stu[idx].score>=95 && stu[idx].score<100) strcat(path, "95-100.txt");
  

        
    
    FILE* ptr;
    ptr = fopen(path, "r");
    fread(cont,1, 1000, ptr);
    fclose(ptr);
    printf("%s 同学,你的学业规划报告如下：\n",name);
    printf("%s\n", cont);
}
