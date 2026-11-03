#include <stdio.h>
#include <stdlib.h>
#include "head file/template.h"

int type()
{

    FILE *ptr;
    ptr = fopen("student.dat", "wb");
    if (ptr == NULL)
    {
        printf("Could not find the file.\n");
        return 1;
    }
    Student group[] = {
        {"B25090001", "ZhangSan", 86.5}, {"B25090002", "LiSi", 92.0}, {"B25090003", "WangWu", 78.0}, {"B25090004", "ZhaoLiu", 63.0}, {"B25090005", "ChenYi", 98.0}, {"B25090006", "LinEr", 70.5}, {"B25090007", "SunQi", 88.0}, {"B25090008", "ZhouBa", 55.0}, {"B25090009", "WuJiu", 90.0}, {"B25090010", "ZhengShi", 82.0}, {"B25090011", "FengYi", 76.0}, {"B25090012", "ChuEr", 61.0}, {"B25090013", "WeiSan", 95.5}, {"B25090014", "JiangSi", 84.0}, {"B25090015", "ShenWu", 69.0}, {"B25090016", "HanLiu", 91.0}, {"B25090017", "YangQi", 73.5}, {"B25090018", "ZhuBa", 80.0}, {"B25090019", "QinJiu", 89.5}, {"B25090020", "YouShi", 67.0}};
    size_t n = sizeof(group) / sizeof(group[0]);
    size_t written = fwrite(group, sizeof(Student), n, ptr);
    int closeResult = fclose(ptr);
    return (written == n && closeResult == 0) ? 0 : 1;
}
