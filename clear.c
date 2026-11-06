#include<stdio.h>
#include<windows.h>
void askClear(int *bol, char choice){
    
    if (choice == 'Y' || choice == 'y') 
    {
        printf("即将返回上一界面！\n");
        Sleep(3000);
        system("cls");
        *bol = 1;
    }
    if (choice == 'N' || choice == 'n') {
        printf("即将返回主菜单！\n");
        Sleep(3000);
        system("cls");
        *bol = 0;
        }
}