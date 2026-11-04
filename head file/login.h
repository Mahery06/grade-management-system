#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (role == ROLE_ADMIN)
        return "Administrator";
    if (role == ROLE_USER)
        return "Regular User";
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

    for (i = 0; i < 3; i++)
    {
        printf("用户名： ");
        if (scanf("%31s", name) != 1)
            return ROLE_FAIL;

        printf("密码： ");
        if (scanf("%31s", pass) != 1)
            return ROLE_FAIL;

        if (strcmp(name, ADMIN_NAME) == 0 && strcmp(pass, ADMIN_PASS) == 0)
        {
            printf("Login successful: Administrator, all functions are available.\n");
            return ROLE_ADMIN;
        }
        if (strcmp(name, USER_NAME) == 0 && strcmp(pass, USER_PASS) == 0)
        {
            printf("Login successful: Regular user, query access only.\n");
            return ROLE_USER;
        }

        printf("用户名或密码错误。还剩 %d 次尝试机会。\n\n", 2 - i);
    }

    return ROLE_FAIL;
}

static void __attribute__((constructor)) loginOnce(void)
{
    g_role = login();

    if (g_role == ROLE_FAIL)
    {
        printf("失败的登录尝试次数过多。程序将退出。\n");
        exit(1);
    }
}

#endif