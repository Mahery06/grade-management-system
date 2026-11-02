#include<stdio.h>
#include<string.h>
#include"head file/student.h"
#include"head file/read_write.h"

void sortByScore(
    const Student students[],
    int count,
    Student *sorted
) {
    int i, j;

    // 先复制数组，避免改变原数组的学号顺序
    memcpy(sorted, students, count * sizeof(Student));

    for (i = 0; i < count - 1; i++) {

        int best = i;

        // 在剩余学生中寻找最高成绩
        for (j = i + 1; j < count; j++) {
            if (sorted[j].score > sorted[best].score) {
                best = j;
            }
        }

        // 交换整个学生结构体
        if (best != i) {
            Student temp = sorted[i];
            sorted[i] = sorted[best];
            sorted[best] = temp;
        }
    }
    _writeIn(count,sorted);
}