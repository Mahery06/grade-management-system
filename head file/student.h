#ifndef STUDENT_H
#define STUDENT_H
#include "template.h"

// Search Module
int searchById(Student stu[], int total, int *n, Student result[]);

int searchByName(Student stu[], int total, int *n, Student result[]);

int searchByScore(Student stu[], int total, int *n, Student result[]);

void tailored_report(Student stu[],int n);

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
#endif