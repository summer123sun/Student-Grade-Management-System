#include <stdio.h>
#include " studen.h"

//显示菜单
void displayMenu() {
    printf("\n===学生成绩管理系统===\n");
    printf("1. 添加学生\n");
    printf("2. 显示所有学生\n");
    printf("3. 查找学生\n");
    printf("4. 修改学生信息\n");
    printf("5. 删除学生\n");
    printf("6. 统计信息\n");
    printf("0. 退出系统\n");
    printf("请选择操作 (0-6): ");
}

int main(void) {
    int choice;

    //初始化系统
    initializeSystem();

    do {
        displayMenu();
        scanf("%d",&choice);

        switch(choice) {
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
            case 0:
                printf("感谢使用学生成绩管理系统！再见！\n");
                break;
            default:
                printf("无效选择，请重新输入！\n");
        }
    } while (choice != 0);


    return 0;
}