#include"template.h"


// Search Module
int searchById(Student stu[],int total, int *n,Student result[]);

int searchByName(Student stu[],int total, int *n,Student result[]);

int searchByScore(Student stu[],int total, int *n,Student result[]);

// Insert Module
int insertStudent(
    Student students[],
    int *count,
    Student item);


// Delete Module
int deleteStudent(
    Student students[],
    int *count,
    const char *id);


// Save Module



// Print Model
void out(int total, Student stu[]);

// Sort Model

void sortByScore(
    const Student students[],
    int count,
    Student sorted[]);






