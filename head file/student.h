#ifndef STUDENT_H
#define STUDENT_H
#include "template.h"

// Search Module
int searchById(Student stu[],int total, int *n,Student result[]);


// 多条件查询流程（学号 / 姓名 / 分数，可选区间）
void searchMenu(int total, Student stu[]);



// Insert Module
int insertStudent(
    Student students[],
    int *count,
    Student item);

// Delete Module
int deleteStudent(
    Student students[],
    int *count);

// Print Model
void out(int total, Student stu[]);

// Sort Module
void sortByScore(
    const Student students[],
    int count,
    Student sorted[]);

void sortById(
    const Student students[],
    int count,
    Student sorted[]);

//  Aggregate Module
void  aggregate(
    int total, 
    Student std[]
);


// Modify Module
int modify(
    int total, 
    Student stu[]);

// 学业预警模块
void warningMenu(const Student students[], int count);

// 学业规划报告
void tailored_report(int total, Student stu[]);

#endif


