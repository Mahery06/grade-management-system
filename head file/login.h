#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ADMIN_NAME "admin"
#define ADMIN_PASS "123456"
#define USER_NAME "user"
#define USER_PASS "123456"

#define ROLE_FAIL 0
#define ROLE_USER 1
#define ROLE_ADMIN 2

static int g_role = ROLE_FAIL;

__attribute__((unused)) static const char *roleName(int role)
{
    if (role == ROLE_ADMIN) return "管理员";
    if (role == ROLE_USER)  return "普通用户";
    return "未登录";
}

static int canModify(void)
{
    return g_role == ROLE_ADMIN;
}

static int login(void)
{
    char name[32];
    char pass[32];
    int i;

    printf("\n========== 学生成绩管理系统 ==========\n");

    for (i = 0; i < 3; i++) {
        printf("用户名：");
        if (scanf("%31s", name) != 1) return ROLE_FAIL;

        printf("密码：");
        if (scanf("%31s", pass) != 1) return ROLE_FAIL;

        if (strcmp(name, ADMIN_NAME) == 0 && strcmp(pass, ADMIN_PASS) == 0) {
            printf("登录成功：你好，管理员。\n");
            printf("登录中……");
            Sleep(3000);
            system("cls");
            return ROLE_ADMIN;
        }
        if (strcmp(name, USER_NAME) == 0 && strcmp(pass, USER_PASS) == 0) {
            printf("登录成功：你好，普通用户。\n");
            printf("登录中……");
            Sleep(3000);
            system("cls");
            return ROLE_USER;
        }

        printf("\033[31m用户名或密码错误。剩余 %d 次机会。\033[0m\n\n", 2 - i);
    }

    return ROLE_FAIL;
}

static void __attribute__((constructor)) loginOnce(void)
{
    SetConsoleOutputCP(65001);   /* 控制台输出用 UTF-8，避免中文乱码 */
    SetConsoleCP(65001);         /* 控制台输入用 UTF-8 */

    g_role = login();

    if (g_role == ROLE_FAIL) {
        printf("\033[31m登录失败次数过多，程序即将退出。\033[0m\n");
        exit(1);
    }
}

#endif