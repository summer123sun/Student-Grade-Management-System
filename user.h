#ifndef STUDENT_GRADE_MANAGEMENT_SYSTEM_USER_H
#define STUDENT_GRADE_MANAGEMENT_SYSTEM_USER_H

#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20

// 链表节点结构体
typedef struct UserNode {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    struct UserNode *next;
} User;

// 链表头指针（全局变量）
extern User *userHead;
// 当前登录用户名
extern char currentUsername[MAX_USERNAME_LEN];

// 函数声明
void initUserSystem();                      // 初始化链表
int loadUsersFromFile();                    // 从文件加载链表
int saveUsersToFile();                      // 保存链表到文件
int registerUser();                         // 注册（尾插法）
int loginUser();                            // 登录
void freeUserList();                        // 释放链表内存
int findUser(const char *username);         // 查找用户
void encryptPassword(char *password);       // 加密
void decryptPassword(char *password);       // 解密
void inputPassword(char *password, int maxLen);  // 密码输入
int isAdmin();                              // 检查是否是管理员
const char* getCurrentUsername();           // 获取当前登录用户名

#endif