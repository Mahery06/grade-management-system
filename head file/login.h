#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ADMIN_NAME "admin"
#define ADMIN_PASS "123456"
#define USER_NAME  "user"
#define USER_PASS  "123456"

#define ROLE_FAIL  0
#define ROLE_USER  1
#define ROLE_ADMIN 2

static int g_role = ROLE_FAIL;

__attribute__((unused))
static const char *roleName(int role)
{
    if (role == ROLE_ADMIN) return "管理员";
    if (role == ROLE_USER)  return "普通用户";
    return "未登录";
}


static int canModify(void)
{
    return g_role == ROLE_ADMIN;
}

/* ?????3 ?��??? */
static int login(void)
{
    char name[32];
    char pass[32];
    int i;

    printf("\n========== 学生成绩管理系统 ==========\n");

    for (i = 0; i < 3; i++) {
        printf("用户名: ");
        if (scanf("%31s", name) != 1) return ROLE_FAIL;

        printf("密码: ");
        if (scanf("%31s", pass) != 1) return ROLE_FAIL;

        if (strcmp(name, ADMIN_NAME) == 0 && strcmp(pass, ADMIN_PASS) == 0) {
            printf("登录成功：管理员，可使用全部功能。\n");
            return ROLE_ADMIN;
        }
        if (strcmp(name, USER_NAME) == 0 && strcmp(pass, USER_PASS) == 0) {
            printf("登陆成功：普通用户，可以查询。\n");
            return ROLE_USER;
        }

        printf("用户名或密码错误，还剩 %d 次机会\n\n", 2 - i);
    }

    return ROLE_FAIL;
}

static void __attribute__((constructor)) loginOnce(void)
{
    g_role = login();

    if (g_role == ROLE_FAIL) {
        printf("登录失败次数过多，程序退出。\n");
        exit(1);
    }
}

#endif