//
// Created by summer on 2025/10/11.
//

#ifndef STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDENT_H
#define STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDENT_H

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

//学生结构体
typedef struct{
    int id;                                 //学号
    char name[MAX_NAME_LENGTH];             //姓名
    char className[MAX_NAME_LENGTH];    //班级
    float chinese;    // 语文成绩
    float math;       // 数学成绩
    float english;    // 英语成绩
    float music;      // 音乐成绩
    float physical;   // 体育成绩
    float total;      // 总分（可选）
    float average;    // 平均分（可选）
} Student;

// 学生数组和计数器
extern Student students[];
extern int student_count;

//函数声明
void initializeSystem();                    // 初始化系统（清空学生数组、计数器等）
void addStudent();                          // 新增一名学生并录入成绩
void displayAllStudents();                  // 列表显示所有学生信息
void searchStudent();                       // 按姓名/学号模糊搜索学生
void updateStudent();                       // 修改指定学生的基本信息或成绩
void deleteStudent();                       // 删除指定学生记录
void calculateStatistics();                 // 汇总并显示各类统计信息
void displayScoreStatus(float score);       // 根据分数显示“优秀/良好/及格/不及格”状态
void displayStudentDetail(int index);       // 打印序号为index的学生完整详情
void searchById();                          // 按学号精确查找学生
void updateSubjectScore(int index, const char* subjectName, float* subjectScore); // 修改某学生单科成绩
void calculateBasicStatistics();            // 计算平均分、最高分、最低分等基础统计
void calculateSubjectStatistics();          // 计算各单科平均分、最高分、最低分
void calculateScoreDistribution();          // 统计各分数段人数及百分比
void displayRankings();                     // 按总分/平均分排序并显示排行榜
void calculateClassStatistics();            // 计算班级整体指标（标准差、及格率等）
void saveToFile(const char* filename);      // 将当前数据持久化到指定文件
void loadFromFile(const char* filename);    // 从指定文件读取数据到内存
void fileOperationsMenu();                  // 文件操作子菜单（保存/加载/备份等）
const char* getCurrentTime();               // 获取当前系统时间字符串
int fileExists(const char* filename);       // 判断指定文件是否存在
void displayMenu();                         // 显示主菜单








#endif //STUDENT_GRADE_MANAGEMENT_SYSTEM_STUDENT_H