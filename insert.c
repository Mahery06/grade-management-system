#include<stdio.h>
#include"student.h"

int insertStudent(Student students[], int *count, Student item) {
    int left = 0;
    int right = *count;
    int i, pos;

    // 判断数组是否已满
    if (*count >= MAX_STUDENTS) {
        return -1;
    }

    // 二分查找插入位置
    while (left < right) {
        int mid = left + (right - left) / 2;

        if (strcmp(students[mid].id, item.id) < 0) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    pos = left;

    // 检查学号是否重复
    if (pos < *count&&
        strcmp(students[pos].id, item.id) == 0) {
        return 0;
    }

    // 后面的学生向后移动
    for (i = *count; i > pos; i--) {
        students[i] = students[i - 1];
    }

    // 插入新学生
    students[pos] = item;

    // 学生总人数加一
    (*count)++;

    return 1;
}