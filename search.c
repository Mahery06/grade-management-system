/*
 * search.c - 查询模块
 *
 * 分层结构：
 *   1. 输入辅助函数      （健壮的按行输入）
 *   2. 条件模型          （最多 3 个条件，按 AND 组合）
 *   3. 查询引擎          （学号用二分查找，其他条件用顺序扫描）
 *   4. 界面层            （menu.c 调用 searchMenu；searchById 为备用接口）
 *
 * 查询条件：
 *   - 学号：精确值（二分查找）或闭区间 [idLow, idHigh]
 *   - 姓名：精确值（顺序扫描）
 *   - 分数：分数 < m（顺序扫描）或闭区间 [low, high]
 *
 * 组合规则：
 *   最多可选择 3 个不同的字段，所有条件按 AND 组合。
 *   输入完第一个条件后会询问是否继续输入其他信息，
 *   然后依次输入第二个和（可选的）第三个字段。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

#define SEARCH_MAX_CONDITIONS 3

/* ------------------------------------------------------------------ */
/* 条件模型                                                            */
/* ------------------------------------------------------------------ */

/*
 * 查询字段编号（0/1/2）。
 */
#define FIELD_ID    0
#define FIELD_NAME  1
#define FIELD_SCORE 2

typedef struct
{
    int field;                 /* 字段：学号 / 姓名 / 分数       */
    int isRange;               /* 0 = 单值，1 = 区间             */
    char id[ID_LENGTH];        /* 精确学号                       */
    char name[NAME_LENGTH];    /* 精确姓名                       */
    double score;              /* 分数上限：分数 < score         */
    char idLow[ID_LENGTH];     /* 学号区间起点（包含）           */
    char idHigh[ID_LENGTH];    /* 学号区间终点（包含）           */
    double low;                /* 分数区间下限（包含）           */
    double high;               /* 分数区间上限（包含）           */
} Condition;


typedef struct      /*为二分查找做准备，不能保证 原数组是按学号有序排列*/
{
    const Student *student;
    int index;
} IdEntry;

/* ------------------------------------------------------------------ */
/* 输入辅助函数                                                        */
/* ------------------------------------------------------------------ */

/*
 * menu.c 用 scanf() 读取菜单编号，会在 stdin 中留下换行符。
 * 切换到按行输入前先调用一次本函数清掉它。
 */
static void clearInputLine(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

/*
 * 读取一行，并去掉末尾换行符。
 * 返回 1 表示成功，0 表示 EOF，-1 表示该行超出缓冲区长度。
 */
static int readLine(char *buffer, int size)
{
    int len;
    int ch;

    if (fgets(buffer, size, stdin) == NULL)
        return 0;

    len = (int)strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[--len] = '\0';
    }
    else if (len == size - 1)
    {
        /* 缓冲区已满：该行可能还有后续字符。 */
        ch = getchar();
        if (ch != '\n' && ch != EOF)
        {
            clearInputLine();
            return -1;
        }
    }
    else if (!feof(stdin))
    {
        clearInputLine();
        return -1;
    }

    if (len > 0 && buffer[len - 1] == '\r')
        buffer[--len] = '\0';

    return 1;
}

/* 读取一个非空字符串。遇到 EOF 返回 0。 */
static int readText(char *buffer, int size, const char *prompt)
{
    int result;

    for (;;)
    {
        printf("%s", prompt);  /*请输入学号（姓名）*/

        result = readLine(buffer, size);
        if (result == 1)
        {
            if (buffer[0] != '\0')
                return 1;
            printf("输入不能为空。\n");
        }
        else if (result == 0)
        {
            return 0;
        }
        else
        {
            printf("输入过长（最多 %d 个字符）。\n", size - 1);
        }
    }
}

/* 读取一个整数。遇到 EOF 或输入非法时返回 0。 */
static int readInt(int *value)
{
    char line[64];
    char *end;
    long parsed;

    if (readLine(line, (int)sizeof line) != 1)
        return 0;

    parsed = strtol(line, &end, 10);/*字符串转换成二进制数*/
    while (*end == ' ' || *end == '\t')
        end++;

    if (end == line || *end != '\0')
        return 0;

    *value = (int)parsed;
    return 1;
}

/* 读取 0~100 之间的分数。遇到 EOF 返回 0。 */
static int readScore(double *value)
{
    char line[64];
    char *end;
    double parsed;

    for (;;)
    {
        int result = readLine(line, (int)sizeof line);

        if (result == 0)
            return 0;
        if (result < 0)
        {
            printf("输入过长。\n");
            continue;
        }

        parsed = strtod(line, &end);/*字符串转换成浮点数*/
        while (*end == ' ' || *end == '\t')
            end++;

        if (end != line && *end == '\0' && parsed >= 0.0 && parsed <= 100.0)
        {
            *value = parsed;
            return 1;
        }

        printf("请输入 0 到 100 之间的分数：");
    }
}

/* 询问 Y/N。返回 1 = 是，0 = 否，-1 = EOF。 */
static int askYesNo(const char *prompt)
{
    char line[16];
    int result;

    for (;;)
    {
        printf("%s", prompt);

        result = readLine(line, (int)sizeof line);
        if (result == 0)
            return -1;
        if (result < 0)
        {
            printf("输入过长。\n");
            continue;
        }

        if (line[0] == 'Y' || line[0] == 'y')
            return 1;
        if (line[0] == 'N' || line[0] == 'n')
            return 0;

        printf("请回答 Y 或 N。\n");
    }
}

/* ------------------------------------------------------------------ */
/* 条件输入                                                            */
/* ------------------------------------------------------------------ */

/* 返回字段下标，遇到 EOF 返回 -1。 */
static int askField(int *usedMasks, int ordinal)
{
    int choice;

    for (;;)
    {
        printf("请选择第 %d 个查询信息：\n", ordinal);
        printf("1. 学号\n");
        printf("2. 姓名\n");
        printf("3. 分数\n");
        printf("输入：");

        if (!readInt(&choice))
        {
            if (feof(stdin))
                return -1;
            printf("输入无效，请输入 1、2 或 3。\n");
            continue;
        }

        if (choice < 1 || choice > 3)
        {
            printf("选项无效，请输入 1、2 或 3。\n");
            continue;
        }

        if (usedMasks[choice - 1])
        {
            printf("该信息已经使用过，请选择其他信息。\n");
            continue;
        }

        return choice - 1;
    }
}

/* 读取一个条件的取值。遇到 EOF 返回 0。 */
static int readCondition(Condition *condition, int field)
{
    memset(condition, 0, sizeof *condition);  /*系统自带的函数，用于初始化结构体，防止之前残留的数据影响*/
    condition->field = field;

    if (field == FIELD_ID)
    {
        int range = askYesNo("是否按学号区间查找？(Y/N)：");

        if (range < 0)
            return 0;

        condition->isRange = range;

        if (range)
        {
            for (;;)
            {
                if (!readText(condition->idLow, ID_LENGTH, "请输入起始学号："))
                    return 0;
                if (!readText(condition->idHigh, ID_LENGTH, "请输入结束学号："))
                    return 0;

                if (strcmp(condition->idLow, condition->idHigh) <= 0)
                    return 1;

                printf("起始学号不能大于结束学号。\n");
            }
        }

        return readText(condition->id, ID_LENGTH, "请输入学号：");
    }

    if (field == FIELD_NAME)
        return readText(condition->name, NAME_LENGTH, "请输入姓名：");

    /* 分数条件 */
    {
        int range = askYesNo("是否按分数区间查找？(Y/N)：");

        if (range < 0)
            return 0;

        condition->isRange = range;

        if (range)
        {
            for (;;)
            {
                printf("请输入分数下限：");
                if (!readScore(&condition->low))
                    return 0;

                printf("请输入分数上限：");
                if (!readScore(&condition->high))
                    return 0;

                if (condition->low <= condition->high)
                    return 1;

                printf("分数下限不能大于分数上限。\n");
            }
        }

        printf("请输入分数上限 m（查找分数 < m 的学生）：");
        return readScore(&condition->score);
    }
}

/* ------------------------------------------------------------------ */
/* 匹配与查询引擎                                                      */
/* ------------------------------------------------------------------ */

static int matchAll(const Student *student, const Condition conditions[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        const Condition *condition = &conditions[i];

        switch (condition->field)
        {
        case FIELD_ID:
            if (condition->isRange)
            {
                if (strcmp(student->id, condition->idLow) < 0 ||
                    strcmp(student->id, condition->idHigh) > 0)
                    return 0;
            }
            else if (strcmp(student->id, condition->id) != 0)
            {
                return 0;
            }
            break;

        case FIELD_NAME:
            if (strcmp(student->name, condition->name) != 0)
                return 0;
            break;

        case FIELD_SCORE:
            if (condition->isRange)
            {
                if (student->score < condition->low || student->score > condition->high)
                    return 0;
            }
            else if (student->score >= condition->score)
            {
                return 0;
            }
            break;

        default:
            return 0;
        }
    }

    return 1;
}

static int compareIdEntry(const void *left, const void *right)/*与下面qsort函数配合使用*/
{
    const IdEntry *a = (const IdEntry *)left;
    const IdEntry *b = (const IdEntry *)right;

    return strcmp(a->student->id, b->student->id);
}

/* 返回第一个学号 >= id 的位置。 */
static int lowerBoundById(const IdEntry entries[], int total, const char *id)    /*二分查找*/
{
    int low = 0;
    int high = total;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        if (strcmp(entries[mid].student->id, id) < 0)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

/*
 * 执行所有条件，把匹配学生的下标写入 matched[]。
 * 存在学号条件时，先按学号排序建立索引，再用二分查找缩小候选范围；
 * 否则对整个数组顺序扫描。返回匹配条数。
 */
static int runQuery(const Student students[], int total,
                    const Condition conditions[], int conditionCount,
                    int matched[], int capacity)
{
    int count = 0;
    int idCondition = -1;
    int i;

    for (i = 0; i < conditionCount; i++)
    {
        if (conditions[i].field == FIELD_ID)
            idCondition = i;
    }

    if (idCondition >= 0)
    {
        IdEntry entries[MAX_STUDENTS];
        const Condition *idCond = &conditions[idCondition];
        int pos;

        for (i = 0; i < total; i++)
        {
            entries[i].student = &students[i];
            entries[i].index = i;
        }

        qsort(entries, (size_t)total, sizeof entries[0], compareIdEntry);/*系统自带的排序函数，与上面的compareIdEntry函数配合使用*/

        pos = lowerBoundById(entries, total,
                             idCond->isRange ? idCond->idLow : idCond->id);

        for (; pos < total && count < capacity; pos++)
        {
            if (idCond->isRange)
            {
                if (strcmp(entries[pos].student->id, idCond->idHigh) > 0)
                    break;
            }
            else if (strcmp(entries[pos].student->id, idCond->id) != 0)
            {
                break;
            }

            if (matchAll(entries[pos].student, conditions, conditionCount))
                matched[count++] = entries[pos].index;
        }
    }
    else
    {
        /* 只有姓名/分数条件：顺序扫描。 */
        for (i = 0; i < total && count < capacity; i++)
        {
            if (matchAll(&students[i], conditions, conditionCount))
                matched[count++] = i;
        }
    }

    return count;
}

/* ------------------------------------------------------------------ */
/* 按学号精确查找（备用接口，当前工程未调用）                          */
/* ------------------------------------------------------------------ */

int searchById(Student stu[], int total, int *n, Student result[])
{
    char key[ID_LENGTH];
    int found = -1;

    *n = 0;

    if (total > MAX_STUDENTS)
        total = MAX_STUDENTS;

    if (!readText(key, ID_LENGTH, "\n请输入要查询的学号："))
        return -1;

    if (total > 0)
    {
        IdEntry entries[MAX_STUDENTS];
        int i;
        int pos;

        for (i = 0; i < total; i++)
        {
            entries[i].student = &stu[i];
            entries[i].index = i;
        }

        qsort(entries, (size_t)total, sizeof entries[0], compareIdEntry);

        pos = lowerBoundById(entries, total, key);
        if (pos < total && strcmp(entries[pos].student->id, key) == 0)
            found = entries[pos].index;
    }

    if (found < 0)
    {
        printf("未找到该学生！学号 %s 不存在。\n", key);
        return -1;
    }

    result[0] = stu[found];
    *n = 1;
    return found;
}

/* ----------------------------------------------------------------- */
/* 界面层：menu.c 使用的多条件查询                                      */
/* ------------------------------------------------------------------ */

void searchMenu(int total, Student stu[])
{
    int usedMasks[3]={0,0,0};
    Condition conditions[SEARCH_MAX_CONDITIONS];
    int matched[MAX_STUDENTS];
    Student result[MAX_STUDENTS];
    int conditionCount = 0;
    int field;
    int count;
    int i;

    if (total > MAX_STUDENTS)
        total = MAX_STUDENTS;

    if (total <= 0)
    {
        printf("系统中没有学生记录。\n");
        return;
    }

    /* 清掉 menu.c 中 scanf() 残留的换行符。 */
    clearInputLine();

    printf("\n========== 查询 ==========\n");

    field = askField(usedMasks, 1);
    if (field < 0)      /*退出查询*/
        return;

    if (!readCondition(&conditions[0], field))    /*读取失败*/
        return;

    usedMasks[field] = 1;  /*标记已使用的字段，防止重复使用*/
    conditionCount = 1;       /*已输入的条件数*/
    while (conditionCount < SEARCH_MAX_CONDITIONS)
    {
        int more = askYesNo("是否输入其他信息？(Y/N)：");

        if (more < 0)
            return;
        if (!more)
            break;

        field = askField(usedMasks, conditionCount + 1);
        if (field < 0)         /*退出查询*/
            return;

        if (!readCondition(&conditions[conditionCount], field))    /*读取失败*/
            return;

        usedMasks[field] = 1;  /*标记已使用的字段，防止重复使用*/
        conditionCount++;
    }

    count = runQuery(stu, total, conditions, conditionCount, matched, MAX_STUDENTS);

    /* runQuery(const Student students[], int total,
                    const Condition conditions[], int conditionCount,
                    int matched[], int capacity)*/
    if (count == 0)
    {
        printf("未找到符合条件的学生！\n");
        printf("操作失败！\n");
        return;
    }

    for (i = 0; i < count; i++)
        result[i] = stu[matched[i]];

    printf("操作成功！\n\n");
    printf("查询结果如下（共 %d 条）：\n", count);
    out(count, result);
}