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

// 显示管理员主菜单
void showAdminMainMenu() {
    int choice;

    // 初始化学生系统
    initializeSystem();

    do {
        system("cls");
        printf("\n");
        printf("==============================================================\n");
        printf("|                    学生成绩管理系统                        |\n");
        printf("==============================================================\n");
        printf("登录用户：%s (管理员)\n", getCurrentUsername());
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
            system("cls");
        }
    } while (choice != 0);
}

// 显示普通用户主菜单
void showUserMainMenu() {
    int choice;

    // 初始化学生系统
    initializeSystem();

    do {
        system("cls");
        printf("\n");
        printf("==============================================================\n");
        printf("|                    学生成绩管理系统                        |\n");
        printf("==============================================================\n");
        printf("登录用户：%s (普通用户)\n", getCurrentUsername());
        printf("\n");
        printf("====================== 功能主菜单 ============================\n");
        printf("                                                            \n");
        printf("              1. 显示所有学生      2. 查找学生              \n");
        printf("              3. 统计信息          4. 从文件加载数据        \n");
        printf("              0. 退出系统                                   \n");
        printf("                                                            \n");
        printf("==============================================================\n");
        printf("\n");
        printf("请选择操作 (0-4): ");
        scanf("%d", &choice);
        // 消耗输入缓冲区剩余字符
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                displayAllStudents();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                calculateStatistics();
                break;
            case 4: {
                // 从文件加载数据（普通用户专用）
                char filename[100];
                printf("\n═══════════════════════════════════════════════\n");
                printf("                从文件加载数据\n");
                printf("═══════════════════════════════════════════════\n");
                printf("请输入要加载的文件名: ");
                scanf("%s", filename);
                loadFromFile(filename);
                printf("\n按回车键继续...");
                getchar();  // 吸收之前的换行符
                getchar();  // 等待用户按回车
                break;
            }
            case 0:
                printf("\n正在退出系统...\n");
                Sleep(1000);
                break;
            default:
                printf("\n无效选择！请选择 0-4 之间的数字。\n");
        }

        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
            system("cls");
        }
    } while (choice != 0);
}

// 根据用户权限显示相应的菜单
void showMainMenu() {
    if (isAdmin()) {
        showAdminMainMenu(); // 管理员看到完整菜单
    } else {
        showUserMainMenu();  // 普通用户看到受限菜单
    }
}

int main() {
    // 显示登录菜单
    showLoginMenu();

    // 登录成功后根据权限显示相应的主菜单
    showMainMenu();

    freeUserList();  // 程序结束前释放链表内存
    return 0;
}