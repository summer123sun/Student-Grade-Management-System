#include <stdio.h>
#include " student.h"

/**
 * 显示系统主菜单
 *
 * 功能说明：
 * 显示所有可用的功能选项
 * 用户通过输入数字选择相应功能
 */
void displayMenu() {
    printf("\n═══════════════════════════════════════════════\n");
    printf("            学生成绩管理系统\n");
    printf("═══════════════════════════════════════════════\n");
    printf("1. 添加学生\n");
    printf("2. 显示所有学生\n");
    printf("3. 查找学生\n");
    printf("4. 修改学生信息\n");
    printf("5. 删除学生\n");
    printf("6. 统计信息\n");
    printf("7. 文件操作（保存/加载）\n");  // 新增文件操作选项
    printf("0. 退出系统\n");
    printf("═══════════════════════════════════════════════\n");
    printf("请选择操作 (0-7): ");
}

/**
 * 程序主函数
 *
 * 功能说明：
 * 1. 初始化系统
 * 2. 显示主菜单并处理用户选择
 * 3. 循环运行直到用户选择退出
 * 4. 退出前提示保存数据
 */
int main() {
    int choice;  // 存储用户的选择

    // 系统初始化
    initializeSystem();
    printf("学生成绩管理系统已启动\n");
    printf("提示：您可以使用文件操作菜单来保存和加载数据\n");

    // 主循环：显示菜单并处理用户选择
    do {
        displayMenu();     // 显示菜单
        scanf("%d", &choice);  // 获取用户选择

        // 根据用户选择执行相应功能
        switch(choice) {
            case 1:
                addStudent();        // 添加学生
                break;
            case 2:
                displayAllStudents(); // 显示所有学生
                break;
            case 3:
                searchStudent();     // 查找学生
                break;
            case 4:
                updateStudent();     // 修改学生信息
                break;
            case 5:
                deleteStudent();     // 删除学生
                break;
            case 6:
                calculateStatistics(); // 统计信息
                break;
            case 7:
                fileOperationsMenu(); // 文件操作（新增）
                break;
            case 0:

                break;
            default:
                printf(" 无效选择，请输入 0-7 之间的数字！\n");
        }

    } while (choice != 0);  // 用户选择0时退出循环

    return 0;
}

