#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

// 全局变量定义
Student students[MAX_STUDENTS];
int studentCount = 0;

// 初始化系统
void initializeSystem() {
    studentCount = 0;
    // 清空学生数组
    memset(students, 0, sizeof(students));
    printf("=== 学生成绩管理系统初始化完成 ===\n");
    printf("系统可以存储最多 %d 名学生信息\n", MAX_STUDENTS);
}

// 成绩验证辅助函数
float getValidScore(const char* subjectName) {
    float score;
    do {
        printf("%s成绩（0-100）: ", subjectName);
        scanf("%f", &score);
        if (score < 0 || score > 100) {
            printf("错误：成绩必须在0-100之间！\n");
        }
    } while (score < 0 || score > 100);
    return score;
}

// 计算学生的总分和平均分
void calculateStudentTotal(Student *student) {
    if (student == NULL) return;
    
    student->total = student->chinese + student->math + 
                    student->english + student->music + student->physical;
    student->average = student->total / 5.0;
}

// 添加学生
void addStudent() {
    char choice;
    do {
        system("cls");
        printf("\n=== 添加学生信息 ===\n");
        
        if (studentCount >= MAX_STUDENTS) {
            printf("错误：系统已达到最大学生数量限制！\n");
            system("pause");
            return;
        }
        
        Student newStudent;
        printf("请输入学号: ");
        scanf("%d", &newStudent.id);
        
        // 检查学号是否重复
        int idExists = 0;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].id == newStudent.id) {
                idExists = 1;
                break;
            }
        }
        if (idExists) {
            printf("错误：学号 %d 已存在！\n", newStudent.id);
            system("pause");
            continue;
        }
        
        printf("请输入姓名: ");
        scanf("%s", newStudent.name);
        
        printf("请输入班级: ");
        scanf("%s", newStudent.className);
        
        // 输入各科成绩
        newStudent.chinese = getValidScore("语文");
        newStudent.math = getValidScore("数学");
        newStudent.english = getValidScore("英语");
        newStudent.music = getValidScore("音乐");
        newStudent.physical = getValidScore("体育");
        
        // 计算总分和平均分
        calculateStudentTotal(&newStudent);
        
        // 添加到数组
        students[studentCount++] = newStudent;
        
        printf("成功添加学生：%s (学号：%d, 班级：%s)\n", 
               newStudent.name, newStudent.id, newStudent.className);
        
        printf("\n继续添加学生？(y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
}

// 显示所有学生信息
void displayAllStudents() {
    if (studentCount == 0) {
        printf("目前没有学生信息。\n");
        return;
    }
    
    printf("\n=== 所有学生信息 ===\n");
    printf("学生总数: %d\n", studentCount);
    
    // 打印表头
    printf("┌──────┬──────────────┬────────────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐\n");
    printf("│ 学号  │     姓名      │    班级    │ 语文   │ 数学 │ 英语  │ 音乐 │ 体育   │ 总分   │ 平均分 │\n");
    printf("├──────┼──────────────┼────────────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤\n");
    
    // 打印每个学生的信息
    for (int i = 0; i < studentCount; i++) {
        printf("│ %4d │ %-12s │  %-10s │ %4.1f │ %4.1f │ %4.1f │ %4.1f │ %4.1f │ %4.1f │ %5.1f │\n",
               students[i].id,
               students[i].name,
               students[i].className,
               students[i].chinese,
               students[i].math,
               students[i].english,
               students[i].music,
               students[i].physical,
               students[i].total,
               students[i].average);
    }
    
    printf("└──────┴──────────────┴────────────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘\n");
}

// 显示单个学生的详细信息
void displayStudentDetail(int index) {
    if (index < 0 || index >= studentCount) {
        printf("错误：无效的学生索引！\n");
        return;
    }
    
    Student *student = &students[index];
    
    printf("\n═══════════════════════════════════════════════\n");
    printf("               学生详细信息\n");
    printf("═══════════════════════════════════════════════\n");
    printf("  学号：%d\n", student->id);
    printf("  姓名：%s\n", student->name);
    printf("  班级：%s\n", student->className);
    printf("  语文：%.1f 分 ", student->chinese);
    displayScoreStatus(student->chinese);
    printf("  数学：%.1f 分 ", student->math);
    displayScoreStatus(student->math);
    printf("  英语：%.1f 分 ", student->english);
    displayScoreStatus(student->english);
    printf("  音乐：%.1f 分 ", student->music);
    displayScoreStatus(student->music);
    printf("  体育：%.1f 分 ", student->physical);
    displayScoreStatus(student->physical);
    printf("  总分：%.1f 分\n", student->total);
    printf("  平均分：%.1f 分\n", student->average);
    printf("═══════════════════════════════════════════════\n");
}

// 显示成绩状态（优秀/良好/及格/不及格）
void displayScoreStatus(float score) {
    if (score >= 90) {
        printf("(优秀)\n");
    } else if (score >= 80) {
        printf("(良好)\n");
    } else if (score >= 60) {
        printf("(及格)\n");
    } else {
        printf("(不及格)\n");
    }
}

// 按学号查找
void searchById() {
    int searchId;
    int foundIndex = -1;
    
    printf("请输入学号: ");
    scanf("%d", &searchId);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("未找到学号为 %d 的学生。\n", searchId);
        return;
    }
    
    displayStudentDetail(foundIndex);
}

// 按姓名查找（可能找到多个）
void searchByName() {
    char searchName[MAX_NAME_LENGTH];
    int foundCount = 0;
    int foundIndices[MAX_STUDENTS];  // 存储找到的学生索引
    
    printf("请输入姓名: ");
    scanf("%s", searchName);
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, searchName) == 0) {
            foundIndices[foundCount++] = i;
        }
    }
    
    if (foundCount == 0) {
        printf("未找到姓名为 %s 的学生。\n", searchName);
        return;
    }
    
    printf("\n找到 %d 个姓名为 %s 的学生:\n", foundCount, searchName);
    
    // 显示找到的所有学生
    for (int i = 0; i < foundCount; i++) {
        printf("\n--- 第 %d 个结果 ---\n", i + 1);
        displayStudentDetail(foundIndices[i]);
    }
}

// 查找学生
void searchStudent() {
    if (studentCount == 0) {
        printf("目前没有学生信息。\n");
        return;
    }
    
    int choice;
    printf("\n=== 查找学生 ===\n");
    printf("请选择查找方式:\n");
    printf("1. 按学号查找\n");
    printf("2. 按姓名查找\n");
    printf("请选择 (1-2): ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            searchById();
            break;
        case 2:
            searchByName();
            break;
        default:
            printf("无效选择！\n");
    }
}

// 修改学号
void updateStudentId(int index) {
    int newId;
    printf("请输入新的学号: ");
    scanf("%d", &newId);
    
    // 检查学号是否重复（排除自己）
    for (int i = 0; i < studentCount; i++) {
        if (i != index && students[i].id == newId) {
            printf("错误：学号 %d 已存在！\n", newId);
            return;
        }
    }
    
    students[index].id = newId;
    printf("学号修改成功！\n");
}

// 修改姓名
void updateStudentName(int index) {
    char newName[MAX_NAME_LENGTH];
    printf("请输入新的姓名: ");
    scanf("%s", newName);
    
    strcpy(students[index].name, newName);
    printf("姓名修改成功！\n");
}

// 修改班级
void updateStudentClass(int index) {
    char newClass[50];
    printf("请输入新的班级: ");
    scanf("%s", newClass);
    
    strcpy(students[index].className, newClass);
    printf("班级修改成功！\n");
}

// 修改科目成绩（通用函数）
void updateSubjectScore(int index, const char* subjectName, float* subjectScore) {
    float newScore = getValidScore(subjectName);
    *subjectScore = newScore;
    printf("%s成绩修改成功！\n", subjectName);
}

// 修改所有信息
void updateAllInfo(int index) {
    printf("\n--- 修改所有信息 ---\n");
    updateStudentId(index);
    updateStudentName(index);
    updateStudentClass(index);
    
    printf("\n--- 修改各科成绩 ---\n");
    updateSubjectScore(index, "语文", &students[index].chinese);
    updateSubjectScore(index, "数学", &students[index].math);
    updateSubjectScore(index, "英语", &students[index].english);
    updateSubjectScore(index, "音乐", &students[index].music);
    updateSubjectScore(index, "体育", &students[index].physical);
    
    // 重新计算总分和平均分
    calculateStudentTotal(&students[index]);
    printf("所有信息修改完成！\n");
}

// 修改学生信息
void updateStudent() {
    if (studentCount == 0) {
        printf("目前没有学生信息。\n");
        return;
    }
    
    int searchId, choice;
    int foundIndex = -1;
    
    printf("\n=== 修改学生信息 ===\n");
    printf("请输入要修改的学生学号: ");
    scanf("%d", &searchId);
    
    // 查找学生
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("未找到学号为 %d 的学生。\n", searchId);
        return;
    }
    
    // 显示当前信息
    printf("\n当前学生信息:\n");
    displayStudentDetail(foundIndex);
    
    // 修改菜单
    do {
        printf("\n请选择要修改的内容:\n");
        printf("1. 修改学号\n");
        printf("2. 修改姓名\n");
        printf("3. 修改班级\n");
        printf("4. 修改语文成绩\n");
        printf("5. 修改数学成绩\n");
        printf("6. 修改英语成绩\n");
        printf("7. 修改音乐成绩\n");
        printf("8. 修改体育成绩\n");
        printf("9. 修改所有信息\n");
        printf("0. 完成修改\n");
        printf("请选择 (0-9): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                updateStudentId(foundIndex);
                break;
            case 2:
                updateStudentName(foundIndex);
                break;
            case 3:
                updateStudentClass(foundIndex);
                break;
            case 4:
                updateSubjectScore(foundIndex, "语文", &students[foundIndex].chinese);
                break;
            case 5:
                updateSubjectScore(foundIndex, "数学", &students[foundIndex].math);
                break;
            case 6:
                updateSubjectScore(foundIndex, "英语", &students[foundIndex].english);
                break;
            case 7:
                updateSubjectScore(foundIndex, "音乐", &students[foundIndex].music);
                break;
            case 8:
                updateSubjectScore(foundIndex, "体育", &students[foundIndex].physical);
                break;
            case 9:
                updateAllInfo(foundIndex);
                break;
            case 0:
                printf("修改完成！\n");
                break;
            default:
                printf("无效选择！\n");
        }
        
        // 每次修改后重新计算总分和平均分
        if (choice >= 4 && choice <= 9) {
            calculateStudentTotal(&students[foundIndex]);
        }
    } while (choice != 0);
    
    printf("\n修改后的学生信息:\n");
    displayStudentDetail(foundIndex);
}

// 删除学生
void deleteStudent() {
    if (studentCount == 0) {
        printf("目前没有学生信息。\n");
        return;
    }
    
    int searchId, foundIndex = -1;
    
    printf("\n=== 删除学生信息 ===\n");
    printf("请输入要删除的学生学号: ");
    scanf("%d", &searchId);
    
    // 查找学生
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("未找到学号为 %d 的学生。\n", searchId);
        return;
    }
    
    // 显示要删除的学生完整信息
    printf("\n 即将删除以下学生信息:\n");
    displayStudentDetail(foundIndex);
    
    // 确认删除
    char confirm;
    printf("\n? 确定要删除该学生吗？此操作不可撤销！(y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        // 执行删除：将后面的元素前移
        for (int i = foundIndex; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;  // 学生总数减1
        printf("删除成功！当前剩余学生数: %d\n", studentCount);
    } else {
        printf("删除操作已取消。\n");
    }
}

// 基础统计（总分平均、最高、最低）
void calculateBasicStatistics() {
    if (studentCount == 0) return;
    
    float totalSum = 0;
    float maxTotal = students[0].total;
    float minTotal = students[0].total;
    int maxIndex = 0;
    int minIndex = 0;
    
    /* 遍历全部学生，累加总分并更新最高/最低 */
    for (int i = 0; i < studentCount; i++) {
        totalSum += students[i].total;
        
        if (students[i].total > maxTotal) {
            maxTotal = students[i].total;
            maxIndex = i;
        }
        
        if (students[i].total < minTotal) {
            minTotal = students[i].total;
            minIndex = i;
        }
    }
    
    printf("【基础统计信息】\n");
    printf("总分平均分: %.1f\n", totalSum / studentCount);
    printf("最高总分: %.1f (学号: %d, 姓名: %s)\n", 
           maxTotal, students[maxIndex].id, students[maxIndex].name);
    printf("最低总分: %.1f (学号: %d, 姓名: %s)\n", 
           minTotal, students[minIndex].id, students[minIndex].name);
    printf("\n");
}

// 单科详细统计
void calculateSubjectStatistics() {
    if (studentCount == 0) return;
    
    /* 内部结构体：保存单科的统计中间值 */
    typedef struct {
        float sum;
        float max;
        float min;
        int passCount;
        int maxIndex;
        int minIndex;
    } SubjectStats;
    
    /* 5 门课分别初始化 */
    SubjectStats chinese  = {0, 0, 100, 0, 0, 0};
    SubjectStats math     = {0, 0, 100, 0, 0, 0};
    SubjectStats english  = {0, 0, 100, 0, 0, 0};
    SubjectStats music    = {0, 0, 100, 0, 0, 0};
    SubjectStats physical = {0, 0, 100, 0, 0, 0};
    
    /* 遍历全部学生，收集单科数据 */
    for (int i = 0; i < studentCount; i++) {
        // 语文
        chinese.sum += students[i].chinese;
        if (students[i].chinese > chinese.max) {
            chinese.max = students[i].chinese;
            chinese.maxIndex = i;
        }
        if (students[i].chinese < chinese.min) {
            chinese.min = students[i].chinese;
            chinese.minIndex = i;
        }
        if (students[i].chinese >= 60) chinese.passCount++;
        
        // 数学
        math.sum += students[i].math;
        if (students[i].math > math.max) {
            math.max = students[i].math;
            math.maxIndex = i;
        }
        if (students[i].math < math.min) {
            math.min = students[i].math;
            math.minIndex = i;
        }
        if (students[i].math >= 60) math.passCount++;
        
        // 英语
        english.sum += students[i].english;
        if (students[i].english > english.max) {
            english.max = students[i].english;
            english.maxIndex = i;
        }
        if (students[i].english < english.min) {
            english.min = students[i].english;
            english.minIndex = i;
        }
        if (students[i].english >= 60) english.passCount++;
        
        // 音乐
        music.sum += students[i].music;
        if (students[i].music > music.max) {
            music.max = students[i].music;
            music.maxIndex = i;
        }
        if (students[i].music < music.min) {
            music.min = students[i].music;
            music.minIndex = i;
        }
        if (students[i].music >= 60) music.passCount++;
        
        // 体育
        physical.sum += students[i].physical;
        if (students[i].physical > physical.max) {
            physical.max = students[i].physical;
            physical.maxIndex = i;
        }
        if (students[i].physical < physical.min) {
            physical.min = students[i].physical;
            physical.minIndex = i;
        }
        if (students[i].physical >= 60) physical.passCount++;
    }
    
    printf("【单科统计信息】\n");
    printf("科目    平均分   最高分   最低分   及格率   最高分学生\n");
    printf("语文    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n", 
           chinese.sum/studentCount, chinese.max, chinese.min,
           (float)chinese.passCount/studentCount*100, 
           students[chinese.maxIndex].name);
    printf("数学    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n", 
           math.sum/studentCount, math.max, math.min,
           (float)math.passCount/studentCount*100, 
           students[math.maxIndex].name);
    printf("英语    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n", 
           english.sum/studentCount, english.max, english.min,
           (float)english.passCount/studentCount*100, 
           students[english.maxIndex].name);
    printf("音乐    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n", 
           music.sum/studentCount, music.max, music.min,
           (float)music.passCount/studentCount*100, 
           students[music.maxIndex].name);
    printf("体育    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n", 
           physical.sum/studentCount, physical.max, physical.min,
           (float)physical.passCount/studentCount*100, 
           students[physical.maxIndex].name);
    printf("\n");
}

// 分数段分布统计
void calculateScoreDistribution() {
    if (studentCount == 0) return;
    
    int excellent = 0, good = 0, medium = 0, pass = 0, fail = 0;
    
    printf("【分数段分布统计】\n");
    printf("分数段标准：优秀(90-100) 良好(80-89) 中等(70-79) 及格(60-69) 不及格(0-59)\n\n");
    
    /* 根据学生个人平均分进行划段 */
    for (int i = 0; i < studentCount; i++) {
        if (students[i].average >= 90) {
            excellent++;
        } else if (students[i].average >= 80) {
            good++;
        } else if (students[i].average >= 70) {
            medium++;
        } else if (students[i].average >= 60) {
            pass++;
        } else {
            fail++;
        }
    }
    
    printf("优秀: %d 人 (%.1f%%)\n", excellent, (float)excellent/studentCount*100);
    printf("良好: %d 人 (%.1f%%)\n", good, (float)good/studentCount*100);
    printf("中等: %d 人 (%.1f%%)\n", medium, (float)medium/studentCount*100);
    printf("及格: %d 人 (%.1f%%)\n", pass, (float)pass/studentCount*100);
    printf("不及格: %d 人 (%.1f%%)\n", fail, (float)fail/studentCount*100);
    printf("\n");
}

// 班级统计（预留函数）
void calculateClassStatistics() {
    printf("【班级统计】\n");
    printf("功能开发中...\n\n");
}

// 显示排名
void displayRankings() {
    if (studentCount == 0) return;
    
    printf("【成绩排名】\n");
    
    // 创建副本进行排序（不修改原数组）
    Student sortedStudents[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++) {
        sortedStudents[i] = students[i];
    }
    
    // 按总分降序排序（简单选择排序）
    for (int i = 0; i < studentCount - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < studentCount; j++) {
            if (sortedStudents[j].total > sortedStudents[maxIndex].total) {
                maxIndex = j;
            }
        }
        Student temp = sortedStudents[i];
        sortedStudents[i] = sortedStudents[maxIndex];
        sortedStudents[maxIndex] = temp;
    }
    
    // 显示前10名
    int showCount = (studentCount < 10) ? studentCount : 10;
    printf("前%d名学生:\n", showCount);
    printf("名次 学号    姓名        班级        总分   平均分\n");
    for (int i = 0; i < showCount; i++) {
        printf("%2d   %-6d  %-10s  %-10s  %5.1f  %5.1f\n", 
               i + 1,
               sortedStudents[i].id,
               sortedStudents[i].name,
               sortedStudents[i].className,
               sortedStudents[i].total,
               sortedStudents[i].average);
    }
}

// 主入口：计算并打印所有统计信息
void calculateStatistics() {
    /* 0. 保护：如果还没有录入任何学生，直接提示后返回 */
    if (studentCount == 0) {
        printf("目前没有学生信息。\n");
        return;
    }
    
    /* 1. 打印统一的顶部标题栏 */
    printf("\n═══════════════════════════════════════════════\n");
    printf("                学生成绩统计分析\n");
    printf("═══════════════════════════════════════════════\n");
    printf("学生总数: %d\n\n", studentCount);
    
    /* 2. 依次调用 5 大子模块 */
    calculateBasicStatistics();     // 基础统计（总分平均、最高、最低）
    calculateSubjectStatistics();   // 单科统计（平均分、最高分、最低分、及格率）
    calculateScoreDistribution();   // 分数段统计（优秀/良好/中等/及格/不及格）
    calculateClassStatistics();     // 班级统计（函数本体未给出，预留）
    displayRankings();              // 显示排名
    
    /* 3. 统一的底部封底栏 */
    printf("\n═══════════════════════════════════════════════\n");
}

/**
 * 保存数据到文本文件
 * @param filename 要保存的文件名
 *
 * 功能说明：
 * 1. 以文本格式保存学生数据，方便查看和编辑
 * 2. 包含文件头说明，记录保存时间
 * 3. 每行保存一个学生的完整信息
 * 4. 如果保存失败会给出错误提示
 */
void saveToFile(const char* filename) {
    // 尝试以写入模式打开文件
    FILE *file = fopen(filename, "w");
    // 检查文件是否成功打开
    if (file == NULL) {
        printf("错误：无法创建文件 %s！\n", filename);
        printf("可能的原因：磁盘已满、路径不存在或没有写权限。\n");
        return;
    }
    
    // 写入文件头说明
    fprintf(file, "# 学生成绩管理系统数据文件\n");
    fprintf(file, "# 格式：学号 姓名 班级 语文 数学 英语 音乐 体育\n");
    fprintf(file, "# 示例：1001 张三 高三1班 95.5 88.0 92.5 85.0 90.0\n");
    fprintf(file, "# 生成时间：%s", __DATE__ " " __TIME__ "\n\n");
    
    // 遍历所有学生，逐个保存到文件
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d %s %s %.1f %.1f %.1f %.1f %.1f\n",
                students[i].id,
                students[i].name,
                students[i].className,
                students[i].chinese,
                students[i].math,
                students[i].english,
                students[i].music,
                students[i].physical);
    }
    
    // 关闭文件（重要：确保数据真正写入磁盘）
    fclose(file);
    
    // 显示保存结果
    printf("成功保存 %d 个学生的数据到文件：%s\n", studentCount, filename);
}

/**
 * 从文本文件加载数据
 * @param filename 要加载的文件名
 *
 * 功能说明：
 * 1. 从文本文件读取学生数据
 * 2. 跳过注释行（以#开头的行）
 * 3. 验证数据的合法性（学号、成绩范围等）
 * 4. 自动计算每个学生的总分和平均分
 * 5. 如果加载失败会恢复原有数据
 */
void loadFromFile(const char* filename) {
    // 尝试以读取模式打开文件
    FILE *file = fopen(filename, "r");
    // 检查文件是否存在
    if (file == NULL) {
        printf("错误：无法打开文件 %s！\n", filename);
        printf("可能的原因：文件不存在、路径错误或没有读权限。\n");
        return;
    }
    
    // 保存当前学生数据的备份，用于加载失败时恢复
    Student backupStudents[MAX_STUDENTS];
    int backupCount = studentCount;
    memcpy(backupStudents, students, sizeof(Student) * studentCount);
    
    // 重置学生计数器，开始加载新数据
    studentCount = 0;
    char line[256];
    
    // 逐行读取文件
    while (fgets(line, sizeof(line), file) != NULL) {
        // 跳过空行和注释行
        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }
        
        // 解析学生数据
        Student newStudent;
        int result = sscanf(line, "%d %s %s %f %f %f %f %f",
                          &newStudent.id,
                          newStudent.name,
                          newStudent.className,
                          &newStudent.chinese,
                          &newStudent.math,
                          &newStudent.english,
                          &newStudent.music,
                          &newStudent.physical);
        
        // 验证数据完整性
        if (result != 8) {
            printf("警告：文件格式错误，跳过无效行。\n");
            continue;
        }
        
        // 验证成绩范围
        if (newStudent.chinese < 0 || newStudent.chinese > 100 ||
            newStudent.math < 0 || newStudent.math > 100 ||
            newStudent.english < 0 || newStudent.english > 100 ||
            newStudent.music < 0 || newStudent.music > 100 ||
            newStudent.physical < 0 || newStudent.physical > 100) {
            printf("警告：成绩超出范围，跳过无效数据。\n");
            continue;
        }
        
        // 检查学号是否重复
        int idExists = 0;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].id == newStudent.id) {
                idExists = 1;
                break;
            }
        }
        if (idExists) {
            printf("警告：学号 %d 已存在，跳过重复数据。\n", newStudent.id);
            continue;
        }
        
        // 计算总分和平均分
        newStudent.total = newStudent.chinese + newStudent.math + 
                         newStudent.english + newStudent.music + newStudent.physical;
        newStudent.average = newStudent.total / 5.0;
        
        // 添加到学生数组
        if (studentCount < MAX_STUDENTS) {
            students[studentCount++] = newStudent;
        } else {
            printf("警告：学生数量已达上限，无法加载更多学生。\n");
            break;
        }
    }
    
    fclose(file);
    
    // 检查加载结果
    if (studentCount == 0) {
        printf("警告：未加载到任何有效学生数据，恢复原有数据。\n");
        // 恢复备份数据
        studentCount = backupCount;
        memcpy(students, backupStudents, sizeof(Student) * studentCount);
    } else {
        printf("成功加载 %d 个学生数据从文件：%s\n", studentCount, filename);
    }
}

/**
 * 文件操作菜单
 *
 * 功能说明：
 * 提供保存和加载文件的用户界面
 * 用户可以输入文件名来保存或加载数据
 */
void fileOperationsMenu() {
    int choice;
    do {
        printf("\n═══════════════════════════════════════════════\n");
        printf("                文件操作菜单\n");
        printf("═══════════════════════════════════════════════\n");
        printf("1. 保存数据到文件\n");
        printf("2. 从文件加载数据\n");
        printf("0. 返回主菜单\n");
        printf("请选择操作 (0-2): ");
        scanf("%d", &choice);
        
        char filename[100];  // 存储用户输入的文件名
        
        switch (choice) {
            case 1:
                // 保存数据到文件
                printf("请输入要保存的文件名（例如：students.txt）: ");
                scanf("%s", filename);
                saveToFile(filename);
                break;
            case 2:
                // 从文件加载数据
                printf("请输入要加载的文件名: ");
                scanf("%s", filename);
                loadFromFile(filename);  // 实际调用加载函数
                break;
            case 0:
                printf("返回主菜单。\n");
                break;
            default:
                printf("无效选择，请输入 0-2 之间的数字！\n");
        }
        
        // 如果不是返回主菜单，暂停让用户查看结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();  // 吸收之前的换行符
            getchar();  // 等待用户按回车
        }
    } while (choice != 0);
}