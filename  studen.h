//
// Created by summer on 2025/10/11.
//

#ifndef STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDEN_H
#define STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDEN_H

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

//学生结构体
typedef struct{
    int id;                                 //学号
    char name[MAX_NAME_LENGTH];             //姓名
    double score;                           //成绩
} Student;

// 学生数组和计数器
extern Student students[];
extern int student_count;

//函数声明
void initializeSystem();
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void calculateStatistics();






#endif //STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDEN_H