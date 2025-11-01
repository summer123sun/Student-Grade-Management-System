//
// Created by summer on 2025/10/11.
//
#include  <stdio.h>
#include <string.h>
#include " student.h"
#include <time.h>

//全局变量定义
Student students[MAX_STUDENTS];
int studentCount = 0;
//初始化系统
void initializeSystem() {
    studentCount = 0;
    printf("===学生成绩管理系统初始化完成===\n");
    printf("系统可以存储最多 %d 名学生信息\n",MAX_STUDENTS);
}
// 成绩验证辅助函数
float getValidScore(const char* subjectName) {
    float score;
    do {
        printf("%s成绩（0-100）",subjectName);
        scanf("%f",&score);
        if (score < 0 || score > 100) {
            printf("错误：成绩必须在0-100!之间！\n");
        }
    } while (score < 0 || score > 100);
    return score;
}
// 计算学生的总分和平均分
void calculateStudentTotal(Student *student) {
    student->total = student->chinese + student->math + student->english +
                    student->music + student->physical;
    student->average = student->total / 5.0f;
}

// 为所有学生计算总分和平均分
void calculateAllStudentsTotal() {
    for (int i = 0; i < studentCount; i++) {
        calculateStudentTotal(&students[i]);
    }
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

    //输入班级
    printf("请输入班级");
    scanf("%s",newStudent.className);

    // 使用辅助函数输入各科成绩
    printf("\n--- 请输入各科成绩 ---\n");
    newStudent.chinese = getValidScore("语文");
    newStudent.math = getValidScore("数学");
    newStudent.english = getValidScore("英语");
    newStudent.music = getValidScore("音乐");
    newStudent.physical = getValidScore("体育");

    // 计算总分和平均分 - 新增
    calculateStudentTotal(&newStudent);

    //添加到数组
    students[studentCount] = newStudent;
    studentCount++;
    printf("成功添加学生：%s(学号：%d,班级:%s)\n"
        ,newStudent.name,newStudent.id,newStudent.className);

}
//显示所有学生信息
void displayAllStudents() {
    if (studentCount == 0) {
        printf("目前没有学生信息。\n");
        return;
    }

    printf("\n=== 所有学生信息 ===\n");
    printf("学生总数: %d\n", studentCount);

    // 打印表头
    printf("┌──────┬──────────────┬────────────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐\n");
    printf("│ 学号  │     姓名      │    班级    │ 语文 │ 数学 │ 英语 │ 音乐 │ 体育 │ 总分 │ 平均分       │      │\n");
    printf("├──────┼──────────────┼────────────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤\n");

    // 打印每个学生的信息
    for (int i = 0; i < studentCount; i++) {
        printf("│ %4d │ %-12s │ %-10s │ %4.1f │ %4.1f │ %4.1f │ %4.1f │ %4.1f │ %4.1f │ %5.1f │\n",
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

    Student *student = &students[index];  // 使用指针简化代码

    printf("\n═══════════════════════════════════════════════\n");
    printf("               学生详细信息\n");
    printf("═══════════════════════════════════════════════\n");
    printf(" 学号: %d\n", student->id);
    printf(" 姓名: %s\n", student->name);
    printf(" 班级: %s\n", student->className);
    printf("───────────────────────────────────────────────\n");
    printf(" 成绩单:\n");
    printf("   语文: %6.1f 分", student->chinese);
    displayScoreStatus(student->chinese);  // 显示成绩状态

    printf("   数学: %6.1f 分", student->math);
    displayScoreStatus(student->math);

    printf("   英语: %6.1f 分", student->english);
    displayScoreStatus(student->english);

    printf("   音乐: %6.1f 分", student->music);
    displayScoreStatus(student->music);

    printf("   体育: %6.1f 分", student->physical);
    displayScoreStatus(student->physical);

    printf("───────────────────────────────────────────────\n");
    printf(" 总分:  %6.1f 分\n", student->total);
    printf(" 平均分:%6.1f 分 \n", student->average);
    printf("═══════════════════════════════════════════════\n");
}

// 显示成绩状态（优秀/良好/及格/不及格）
void displayScoreStatus(float score) {
    if (score >= 90) {
        printf("  优秀\n");
    } else if (score >= 80) {
        printf("  良好\n");
    } else if (score >= 60) {
        printf("   及格\n");
    } else {
        printf(" 不及格\n");
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
            foundIndices[foundCount] = i;
            foundCount++;
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
    float newScore;
    printf("当前%s成绩: %.1f\n", subjectName, *subjectScore);
    printf("请输入新的%s成绩: ", subjectName);
    scanf("%f", &newScore);

    // 验证成绩范围
    if (newScore < 0 || newScore > 100) {
        printf("错误：成绩必须在 0-100 之间！\n");
        return;
    }

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
    printf("\n??  即将删除以下学生信息:\n");
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
/*------------------------------------------------------------
 * 主入口：计算并打印所有统计信息
 *----------------------------------------------------------*/
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
    displayRankings();              // 显示排名（函数本体未给出，预留）

    /* 3. 统一的底部封底栏 */
    printf("\n═══════════════════════════════════════════════\n");
}

/*------------------------------------------------------------
 * 子模块 1：基础统计
 * 统计全体学生的总分平均值、最高总分、最低总分
 *----------------------------------------------------------*/
void calculateBasicStatistics() {
    printf("【基础统计】\n");

    float totalSum = 0;          // 所有学生总分之和
    float maxTotal = students[0].total; // 当前最高总分
    float minTotal = students[0].total; // 当前最低总分
    int maxIndex = 0;            // 最高分学生在数组中的下标
    int minIndex = 0;            // 最低分学生在数组中的下标

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

    float avgTotal = totalSum / studentCount;  // 平均总分

    /* 打印结果 */
    printf("总分平均: %.2f\n", avgTotal);
    printf("最高总分: %.1f (学号: %d, 姓名: %s)\n",
           maxTotal, students[maxIndex].id, students[maxIndex].name);
    printf("最低总分: %.1f (学号: %d, 姓名: %s)\n",
           minTotal, students[minIndex].id, students[minIndex].name);
    printf("\n");
}

/*------------------------------------------------------------
 * 子模块 2：单科详细统计
 * 对语文、数学、英语、音乐、体育分别计算：
 *   平均分、最高分、最低分、及格人数、及格率、最高分学生姓名
 *----------------------------------------------------------*/
void calculateSubjectStatistics() {
    printf("【各科成绩统计】\n");

    /* 内部结构体：保存单科的统计中间值 */
    struct SubjectStats {
        float sum;        // 分数累加
        float max;        // 当前最高
        float min;        // 当前最低
        int   maxIndex;   // 最高分学生下标
        int   minIndex;   // 最低分学生下标
        int   passCount;  // ≥60 分人数
    };

    /* 5 门课分别初始化 */
    struct SubjectStats chinese  = {0, 0, 100, 0, 0, 0};
    struct SubjectStats math     = {0, 0, 100, 0, 0, 0};
    struct SubjectStats english  = {0, 0, 100, 0, 0, 0};
    struct SubjectStats music    = {0, 0, 100, 0, 0, 0};
    struct SubjectStats physical = {0, 0, 100, 0, 0, 0};

    /* 单轮循环完成 5 门课的累加与比较 */
    for (int i = 0; i < studentCount; i++) {
        /* ---- 语文 ---- */
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

        /* ---- 数学 ---- */
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

        /* ---- 英语 ---- */
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

        /* ---- 音乐 ---- */
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

        /* ---- 体育 ---- */
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

    /* 统一输出表头 */
    printf("科目    平均分  最高分  最低分  及格率   最高分学生\n");
    printf("------------------------------------------------------------\n");

    /* 打印 5 行结果 */
    printf("语文    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n",
           chinese.sum/studentCount,
           chinese.max,
           chinese.min,
           (float)chinese.passCount/studentCount*100,
           students[chinese.maxIndex].name);

    printf("数学    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n",
           math.sum/studentCount,
           math.max,
           math.min,
           (float)math.passCount/studentCount*100,
           students[math.maxIndex].name);

    printf("英语    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n",
           english.sum/studentCount,
           english.max,
           english.min,
           (float)english.passCount/studentCount*100,
           students[english.maxIndex].name);

    printf("音乐    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n",
           music.sum/studentCount,
           music.max,
           music.min,
           (float)music.passCount/studentCount*100,
           students[music.maxIndex].name);

    printf("体育    %6.1f  %6.1f  %6.1f  %5.1f%%   %s\n",
           physical.sum/studentCount,
           physical.max,
           physical.min,
           (float)physical.passCount/studentCount*100,
           students[physical.maxIndex].name);

    printf("\n");
}

/*------------------------------------------------------------
 * 子模块 3：分数段分布统计
 * 按“学生个人平均分”划定优秀/良好/中等/及格/不及格
 *----------------------------------------------------------*/
void calculateScoreDistribution() {
    printf("【分数段分布统计】\n");

    int excellentAll = 0;  // 优秀：90+
    int goodAll      = 0;  // 良好：80-89
    int mediumAll    = 0;  // 中等：70-79
    int passAll      = 0;  // 及格：60-69
    int failAll      = 0;  // 不及格：0-59

    /* 根据学生个人平均分进行划段 */
    for (int i = 0; i < studentCount; i++) {
        if (students[i].average >= 90) {
            excellentAll++;
        } else if (students[i].average >= 80) {
            goodAll++;
        } else if (students[i].average >= 70) {
            mediumAll++;
        } else if (students[i].average >= 60) {
            passAll++;
        } else {
            failAll++;
        }
    }

    /* 打印数字与百分比 */
    printf("整体分数段分布（按平均分）:\n");
    printf("优秀(90-100): %2d人 (%5.1f%%)\n", excellentAll, (float)excellentAll/studentCount*100);
    printf("良好(80-89):  %2d人 (%5.1f%%)\n", goodAll,      (float)goodAll/studentCount*100);
    printf("中等(70-79):  %2d人 (%5.1f%%)\n", mediumAll,    (float)mediumAll/studentCount*100);
    printf("及格(60-69):  %2d人 (%5.1f%%)\n", passAll,      (float)passAll/studentCount*100);
    printf("不及格(0-59): %2d人 (%5.1f%%)\n", failAll,      (float)failAll/studentCount*100);

    /* 简版条形图 */
    printf("\n分数段分布图:\n");
    displayBarChart("优秀", excellentAll, studentCount);
    displayBarChart("良好", goodAll,      studentCount);
    displayBarChart("中等", mediumAll,    studentCount);
    displayBarChart("及格", passAll,      studentCount);
    displayBarChart("不及格", failAll,    studentCount);

    printf("\n");
}

/*------------------------------------------------------------
 * 工具：绘制单行条形图
 * label：分数段名称
 * count：该段人数
 * total：总人数
 *----------------------------------------------------------*/
void displayBarChart (const char* label, int count, int total) {
    /* 按比例缩放到 20 个字符宽度 */
    int bars = (count * 20) / total;
    if (bars == 0 && count > 0) bars = 1;  // 有人就至少显示 1 格

    printf("%s: ", label);
    for (int i = 0; i < bars; i++) {
        printf("█");
    }
    printf(" %d人\n", count);
}
// 班级统计
void calculateClassStatistics() {
    if (studentCount == 0) return;

    printf("【班级成绩统计】\n");

    // 找出所有不同的班级
    char classes[MAX_STUDENTS][MAX_STUDENTS];
    int classCount = 0;
    int classStudentCount[MAX_STUDENTS] = {0};

    for (int i = 0; i < studentCount; i++) {
        int found = 0;
        for (int j = 0; j < classCount; j++) {
            if (strcmp(students[i].className, classes[j]) == 0) {
                found = 1;
                classStudentCount[j]++;
                break;
            }
        }
        if (!found) {
            strcpy(classes[classCount], students[i].className);
            classStudentCount[classCount] = 1;
            classCount++;
        }
    }

    // 为每个班级计算统计信息
    for (int c = 0; c < classCount; c++) {
        float classChineseSum = 0, classMathSum = 0, classEnglishSum = 0;
        float classMusicSum = 0, classPhysicalSum = 0, classTotalSum = 0;
        int classExcellent = 0, classFail = 0;

        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].className, classes[c]) == 0) {
                classChineseSum += students[i].chinese;
                classMathSum += students[i].math;
                classEnglishSum += students[i].english;
                classMusicSum += students[i].music;
                classPhysicalSum += students[i].physical;
                classTotalSum += students[i].total;

                if (students[i].average >= 90) classExcellent++;
                if (students[i].average < 60) classFail++;
            }
        }

        printf("\n班级: %s (%d人)\n", classes[c], classStudentCount[c]);
        printf("  各科平均: 语%.1f 数%.1f 英%.1f 音%.1f 体%.1f\n",
               classChineseSum/classStudentCount[c],
               classMathSum/classStudentCount[c],
               classEnglishSum/classStudentCount[c],
               classMusicSum/classStudentCount[c],
               classPhysicalSum/classStudentCount[c]);
        printf("  班级平均分: %.1f\n", classTotalSum/classStudentCount[c]);
        printf("  优秀率: %.1f%%, 不及格率: %.1f%%\n",
               (float)classExcellent/classStudentCount[c]*100,
               (float)classFail/classStudentCount[c]*100);
    }

    printf("\n");
}

// 显示排名
void displayRankings() {
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
        // 交换
        Student temp = sortedStudents[i];
        sortedStudents[i] = sortedStudents[maxIndex];
        sortedStudents[maxIndex] = temp;
    }

    // 显示前10名
    int showCount = (studentCount < 10) ? studentCount : 10;
    printf("前%d名学生:\n", showCount);
    printf("名次 学号    姓名        班级        总分   平均分\n");
    printf("----------------------------------------------\n");

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

    // 写入文件头信息（说明文件格式）
    fprintf(file, "# 学生成绩管理系统数据文件\n");
    fprintf(file, "# 保存时间：%s\n", getCurrentTime());
    fprintf(file, "# 数据格式：学号 姓名 班级 语文 数学 英语 音乐 体育\n");
    fprintf(file, "# 注意：总分和平均分会在加载时自动计算\n");
    fprintf(file, "# =========================================\n");

    int savedCount = 0;  // 记录成功保存的学生数量

    // 遍历所有学生，逐个保存到文件
    for (int i = 0; i < studentCount; i++) {
        // 将学生数据格式化为一行文本写入文件
        // 只保存基本信息，总分和平均分在加载时重新计算
        int writeResult = fprintf(file, "%d %s %s %.1f %.1f %.1f %.1f %.1f\n",
                    students[i].id,
                    students[i].name,
                    students[i].className,
                    students[i].chinese,
                    students[i].math,
                    students[i].english,
                    students[i].music,
                    students[i].physical);

        // 检查是否写入成功
        if (writeResult > 0) {
            savedCount++;  // 成功保存一个学生
        } else {
            printf("警告：写入第%d个学生数据时发生错误。\n", i + 1);
        }
    }

    // 关闭文件（重要：确保数据真正写入磁盘）
    fclose(file);

    // 显示保存结果
    if (savedCount == studentCount) {
        printf("成功保存 %d 个学生的数据到文件：%s\n", savedCount, filename);
    } else {
        printf("保存不完整，成功保存 %d/%d 个学生到文件：%s\n",
               savedCount, studentCount, filename);
    }
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

    // 备份当前数据（重要：防止加载失败时丢失原有数据）
    Student backupStudents[MAX_STUDENTS];
    int backupCount = studentCount;
    for (int i = 0; i < studentCount; i++) {
        backupStudents[i] = students[i];
    }

    // 重置学生计数器，开始加载新数据
    studentCount = 0;
    int loadedCount = 0;  // 记录成功加载的学生数量
    char line[256];       // 缓冲区，用于存储每行文本

    printf("正在从文件加载数据...\n");

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file)) {
        // 检查是否已达到最大学生数量
        if (studentCount >= MAX_STUDENTS) {
            printf("警告：已达到最大学生数量 %d，停止加载更多数据。\n", MAX_STUDENTS);
            break;
        }

        // 跳过注释行和空行
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        // 创建新的学生变量来存储加载的数据
        Student newStudent;

        // 从文本行中解析学生数据
        // sscanf返回值表示成功解析的字段数量
        int parsedFields = sscanf(line, "%d %49s %19s %f %f %f %f %f",
                           &newStudent.id,           // 学号
                           newStudent.name,          // 姓名
                           newStudent.className,     // 班级
                           &newStudent.chinese,      // 语文成绩
                           &newStudent.math,         // 数学成绩
                           &newStudent.english,      // 英语成绩
                           &newStudent.music,        // 音乐成绩
                           &newStudent.physical);    // 体育成绩

        // 检查是否成功解析了所有8个字段
        if (parsedFields == 8) {
            // 数据验证阶段

            // 1. 验证学号是否为正数
            if (newStudent.id <= 0) {
                printf("警告：跳过学号无效的学生（学号：%d）\n", newStudent.id);
                continue;
            }

            // 2. 验证学号是否重复
            int duplicate = 0;
            for (int i = 0; i < studentCount; i++) {
                if (students[i].id == newStudent.id) {
                    printf("警告：跳过学号重复的学生（学号：%d）\n", newStudent.id);
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate) {
                continue;
            }

            // 3. 验证各科成绩是否在合理范围内（0-100分）
            if (newStudent.chinese < 0 || newStudent.chinese > 100 ||
                newStudent.math < 0 || newStudent.math > 100 ||
                newStudent.english < 0 || newStudent.english > 100 ||
                newStudent.music < 0 || newStudent.music > 100 ||
                newStudent.physical < 0 || newStudent.physical > 100) {
                printf("警告：跳过成绩无效的学生（学号：%d）\n", newStudent.id);
                continue;
            }

            // 所有验证通过，将学生添加到数组
            // 先计算总分和平均分
            calculateStudentTotal(&newStudent);

            // 添加到学生数组
            students[studentCount] = newStudent;
            studentCount++;
            loadedCount++;

        } else {
            // 解析失败，可能是文件格式错误
            printf("警告：跳过格式错误的数据行：%s", line);
        }
    }

    // 关闭文件
    fclose(file);

    // 显示加载结果
    if (loadedCount > 0) {
        printf("? 成功加载 %d 个学生的数据\n", loadedCount);
        printf("当前共有 %d 个学生\n", studentCount);
    } else {
        // 加载失败，恢复备份数据
        studentCount = backupCount;
        for (int i = 0; i < studentCount; i++) {
            students[i] = backupStudents[i];
        }
        printf("? 加载失败，没有找到有效数据，已恢复原有数据\n");
    }
}
/**
 * 获取当前时间的字符串表示
 * @return 返回当前时间的字符串（格式：YYYY-MM-DD HH:MM:SS）
 *
 * 功能说明：
 * 用于在保存文件时记录时间戳
 */
const char* getCurrentTime() {
    static char timeStr[100];  // 静态变量，保证返回的指针有效
    time_t now = time(NULL);   // 获取当前时间
    struct tm *t = localtime(&now);  // 转换为本地时间结构

    // 格式化时间字符串
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", t);
    return timeStr;
}

/**
 * 检查文件是否存在
 * @param filename 要检查的文件名
 * @return 1-文件存在，0-文件不存在
 *
 * 功能说明：
 * 用于在加载文件前检查文件是否存在
 */
int fileExists(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);  // 文件存在，立即关闭
        return 1;
    }
    return 0;  // 文件不存在
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

                // 检查文件是否存在
                if (fileExists(filename)) {
                    loadFromFile(filename);
                } else {
                    printf("错误：文件 %s 不存在！\n", filename);
                }
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