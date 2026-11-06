#include <stdio.h>
#include<string.h>
#include "head file/student.h"

void p(int n){
    for(int i=0; i< n; i++) printf("█");
    printf("\n\n");
}

void aggregate(int total, Student stu[])
{
    int count = 0;
    float min = 101, max = 0, sum = 0;
    int arr[4][8] = {0}; //记录22、23、24、25届的分布情况
    int count_2022=0, count_2023=0, count_2024 = 0, count_2025=0;
    for (int i = 0; i < total; i++)
    {
        sum += stu[i].score;

        if (stu[i].score < min)
            min = stu[i].score;
        if (stu[i].score > max)
            max = stu[i].score;
        
        if(strstr(stu[i].id, "22")){
            if(stu[i].score>=0 && stu[i].score<60) arr[0][0]++;
            if(stu[i].score>=60 && stu[i].score<70) arr[0][1]++;
            if(stu[i].score>=70 && stu[i].score<75) arr[0][2]++;
            if(stu[i].score>=75 && stu[i].score<80) arr[0][3]++;
            if(stu[i].score>=80 && stu[i].score<85) arr[0][4]++;
            if(stu[i].score>=85 && stu[i].score<90) arr[0][5]++;
            if(stu[i].score>=90 && stu[i].score<95) arr[0][6]++;
            if(stu[i].score>=95 && stu[i].score <= 100) arr[0][7]++;
            count_2022++;
        }

        if(strstr(stu[i].id, "23")){
            if(stu[i].score>=0 && stu[i].score<60) arr[1][0]++;
            if(stu[i].score>=60 && stu[i].score<70) arr[1][1]++;
            if(stu[i].score>=70 && stu[i].score<75) arr[1][2]++;
            if(stu[i].score>=75 && stu[i].score<80) arr[1][3]++;
            if(stu[i].score>=80 && stu[i].score<85) arr[1][4]++;
            if(stu[i].score>=85 && stu[i].score<90) arr[1][5]++;
            if(stu[i].score>=90 && stu[i].score<95) arr[1][6]++;
            if(stu[i].score>=95 && stu[i].score <= 100) arr[1][7]++;
            count_2023++;
        }

        if(strstr(stu[i].id, "24")){
            if(stu[i].score>=0 && stu[i].score<60) arr[2][0]++;
            if(stu[i].score>=60 && stu[i].score<70) arr[2][1]++;
            if(stu[i].score>=70 && stu[i].score<75) arr[2][2]++;
            if(stu[i].score>=75 && stu[i].score<80) arr[2][3]++;
            if(stu[i].score>=80 && stu[i].score<85) arr[2][4]++;
            if(stu[i].score>=85 && stu[i].score<90) arr[2][5]++;
            if(stu[i].score>=90 && stu[i].score<95) arr[2][6]++;
            if(stu[i].score>=95 && stu[i].score <= 100) arr[2][7]++;
            count_2024++;
        }
        
        if(strstr(stu[i].id, "25")){
            if(stu[i].score>=0 && stu[i].score<60) arr[3][0]++;
            if(stu[i].score>=60 && stu[i].score<70) arr[3][1]++;
            if(stu[i].score>=70 && stu[i].score<75) arr[3][2]++;
            if(stu[i].score>=75 && stu[i].score<80) arr[3][3]++;
            if(stu[i].score>=80 && stu[i].score<85) arr[3][4]++;
            if(stu[i].score>=85 && stu[i].score<90) arr[3][5]++;
            if(stu[i].score>=90 && stu[i].score<95) arr[3][6]++;
            if(stu[i].score>=95 && stu[i].score <= 100) arr[3][7]++;
            count_2025++;
        }

    }

    float ave = sum / total;

    printf("\n最高分是 %.2f\n", max);
    printf("最低分是 %.2f\n",  min);
    printf("平均分是 %.2f\n", ave);

    for(int i=0; i<total; i++)
        if (stu[i].score >= 60) count++;

    printf("及格率为 %.2f%% \n", (float)count / total * 100);

    
    
    printf("以下是各个年级的分数分布情况：\n\n");

    printf("2022级:\n");
    if(count_2022 == 0) printf("\033[31mNA!暂无22级学生数据\033[0m\n");
    else{
        printf(" 0--60 分 ");
        p(arr[0][0]*100/count_2022);
        printf("60--70 分 ");
        p(arr[0][1]*100/count_2022);
        printf("70--75 分 ");
        p(arr[0][2]*100/count_2022);
        printf("75--80 分 ");
        p(arr[0][3]*100/count_2022);
        printf("80--85 分 ");
        p(arr[0][4]*100/count_2022);
        printf("85--90 分 ");
        p(arr[0][5]*100/count_2022);
        printf("90--95 分 ");
        p(arr[0][6]*100/count_2022);
        printf("95--100分 ");
        p(arr[0][7]*100/count_2022);
    }
    printf("2023级:\n");
    if(count_2023 == 0) printf("\033[31mNA!暂无23级学生数据\033[0m\n");
    else{
        printf(" 0--60 分 ");
        p(arr[1][0]*100/count_2023);
        printf("60--70 分 ");
        p(arr[1][1]*100/count_2023);
        printf("70--75 分 ");
        p(arr[1][2]*100/count_2023);
        printf("75--80 分 ");
        p(arr[1][3]*100/count_2023);
        printf("80--85 分 ");
        p(arr[1][4]*100/count_2023);
        printf("85--90 分 ");
        p(arr[1][5]*100/count_2023);
        printf("90--95 分 ");
        p(arr[1][6]*100/count_2023);
        printf("95--100分 ");
        p(arr[1][7]*100/count_2023);
    }
    printf("2024级:\n");
    if(count_2024 == 0) printf("\033[31mNA!暂无24级学生数据\033[0m\n");
    else{
        printf(" 0--60 分 ");
        p(arr[2][0]*100/count_2024);
        printf("60--70 分 ");
        p(arr[2][1]*100/count_2024);
        printf("70--75 分 ");
        p(arr[2][2]*100/count_2024);
        printf("75--80 分 ");
        p(arr[2][3]*100/count_2024);
        printf("80--85 分 ");
        p(arr[2][4]*100/count_2024);
        printf("85--90 分 ");
        p(arr[2][5]*100/count_2024);
        printf("90--95 分 ");
        p(arr[2][6]*100/count_2024);
        printf("95--100分 ");
        p(arr[2][7]*100/count_2024);
    }
    printf("2025级:\n");
    if(count_2025 == 0) printf("\033[31mNA!暂无25级学生数据\033[0m\n");
    else{
        printf(" 0--60 分 ");
        p(arr[3][0]*100/count_2025);
        printf("60--70 分 ");
        p(arr[3][1]*100/count_2025);
        printf("70--75 分 ");
        p(arr[3][2]*100/count_2025);
        printf("75--80 分 ");
        p(arr[3][3]*100/count_2025);
        printf("80--85 分 ");
        p(arr[3][4]*100/count_2025);
        printf("85--90 分 ");
        p(arr[3][5]*100/count_2025);
        printf("90--95 分 ");
        p(arr[3][6]*100/count_2025);
        printf("95--100分 ");
        p(arr[3][7]*100/count_2025);
    }
    

}