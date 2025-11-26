#ifndef STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDENT_H
#define STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDENT_H

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

//学生结构体
typedef struct{
    int id;                                 //学号
    char name[MAX_NAME_LENGTH];             //姓名
    char className[MAX_NAME_LENGTH];        //班级
    float chinese;    // 语文成绩
    float math;       // 数学成绩
    float english;    // 英语成绩
    float music;      // 音乐成绩
    float physical;   // 体育成绩
    float total;      // 总分（可选）
    float average;    // 平均分（可选）
} Student;

// 学生数组和计数器
extern Student students[MAX_STUDENTS];
extern int studentCount;  // 修正：与student.c保持一致

//函数声明
void initializeSystem();
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void calculateStatistics();
void displayScoreStatus(float score);
void displayStudentDetail(int index);
void searchById();
void updateSubjectScore(int index, const char* subjectName, float* subjectScore);
void calculateBasicStatistics();
void calculateSubjectStatistics();
void calculateScoreDistribution();
void displayRankings();
void calculateClassStatistics();
void saveToFile(const char* filename);
void loadFromFile(const char* filename);
void fileOperationsMenu();

#endif