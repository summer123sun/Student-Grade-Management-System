//
// Created by summer on 2025/10/11.
//
#include  <stdio.h>
#include <string.h>
#include " studen.h"

//全局变量定义
Student students[MAX_STUDENTS];
int studentCount = 0;

//初始化系统
void initializeSystem() {
    studentCount = 0;
    printf("===学生成绩管理系统初始化完成===\n");
    printf("系统可以存储最多 %d 名学生信息\n",MAX_STUDENTS);
}

//添加学生
void addStudent() {
    if (studentCount >= MAX_STUDENTS)
    {
        printf("错误：学生数量已达到上限%d!\n",MAX_STUDENTS);
        return;
    }

    Student newStudent;

    printf("\n--- 添加新学生---\n");

    //输入学号
    printf("请输入学号:");
    scanf("%d",&newStudent.id);

    // 检查学号是否重复
    for (int i = 0; i<studentCount;i++) {
        if (students[i].id == newStudent.id) {
            printf("错误：学号%d已存在！\n",newStudent.id);
        }
    }
    //输入姓名
    printf("请输入姓名:");
    scanf("%s",newStudent.name);

    //输入成绩
    printf("请输入成绩：");
    scanf("%f",&newStudent.score);

    //验证成绩范围
    if (newStudent.score < 0 || newStudent.score >100) {
        printf("错误：成绩应在0-100之间\n");
        return;
    }

    //添加到数组
    students[studentCount++] = newStudent;
    studentCount++;
    printf("成功添加学生：%s(学号：%d,成绩：%.lf\n"
        ,newStudent.name,newStudent.id,newStudent.score);
}
