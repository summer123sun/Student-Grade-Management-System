#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "student.h"
#include "user.h"

// 显示初始菜单（登录/注册）
void showLoginMenu() {
    int choice;
    int isRunning = 1;

    // 初始化用户系统
    initUserSystem();
    loadUsersFromFile(); // 尝试加载已保存的用户

    while (isRunning) {
        system("cls");
        printf("\n\n");
        printf("==============================================================\n");
        printf("|                    学生成绩管理系统                        |\n");
        printf("==============================================================\n");
        printf("\n");
        printf("====================== 系统登录菜单 ==========================\n");
        printf("                                                            \n");
        printf("              1. 登录系统                                   \n");
        printf("              2. 注册账号                                   \n");
        printf("              0. 退出程序                                   \n");
        printf("                                                            \n");
        printf("==============================================================\n");
        printf("\n");
        printf("请选择操作 (0-2): ");

        // 修正：移除%d前的空格
        scanf("%d", &choice);

        // 消耗输入缓冲区剩余字符（包括换行符）
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                if (loginUser()) {
                    isRunning = 0; // 登录成功，退出循环
                }
                break;
            case 2:
                registerUser();
                break;
            case 0:
                printf("\n感谢使用，再见！\n");
                exit(0);
            default:
                printf("\n无效选择，请重新输入！\n");
                system("pause");
        }
    }
}

// 显示主菜单（学生管理）
void showMainMenu() {
    int choice;

    // 初始化学生系统
    initializeSystem();

    do {
        system("cls");
        printf("\n");
        printf("==============================================================\n");
        printf("|                    学生成绩管理系统                        |\n");
        printf("==============================================================\n");
        printf("\n");
        printf("====================== 功能主菜单 ============================\n");
        printf("                                                            \n");
        printf("              1. 添加学生      2. 显示所有学生              \n");
        printf("              3. 查找学生      4. 修改学生信息              \n");
        printf("              5. 删除学生      6. 统计信息                  \n");
        printf("              7. 文件操作      0. 退出系统                  \n");
        printf("                                                            \n");
        printf("==============================================================\n");
        printf("\n");
        printf("请选择操作 (0-7): ");

        scanf("%d", &choice);

        // 消耗输入缓冲区剩余字符
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                calculateStatistics();
                break;
            case 7:
                fileOperationsMenu();
                break;
            case 0:
                printf("\n正在退出系统...\n");
                Sleep(1000);
                break;
            default:
                printf("\n无效选择！请选择 0-7 之间的数字。\n");
        }

        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }
    } while (choice != 0);
}

int main() {
    // 显示登录菜单
    showLoginMenu();

    // 登录成功后显示学生管理主菜单
    showMainMenu();

    return 0;
}