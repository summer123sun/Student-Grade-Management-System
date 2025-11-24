//
// Created by summer on 2025/11/24.
//

#ifndef STUDENT_GRADE_MANAGEMENT_SYSTEM_USER_H
#define STUDENT_GRADE_MANAGEMENT_SYSTEM_USER_H

#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_USERS 50

// 用户结构体
typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];  // 存储加密后的密码
} User;

// 用户数组和计数器
extern User users[MAX_USERS];
extern int userCount;

// 函数声明
void initUserSystem();                          // 初始化用户系统
int loadUsersFromFile();                        // 从文件加载用户
int saveUsersToFile();                          // 保存用户到文件
int registerUser();                             // 用户注册
int loginUser();                                // 用户登录
void encryptPassword(char *password);           // 加密密码
void decryptPassword(char *password);           // 解密密码
int findUser(const char *username);             // 查找用户
#endif //STUDENT_GRADE_MANAGEMENT_SYSTEM_USER_H