#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "user.h"

// 链表头指针全局变量
User *userHead = NULL;
// 当前登录用户名
char currentUsername[MAX_USERNAME_LEN] = "";

// 保留您的加密函数
char encryption(char mw) {
    char mm;
    int m = (int)mw - 8;
    if (m < 33) m = m + 94;
    mm = (char)m;
    return mm;
}

char decryption(char mw) {
    char mingwen;
    int m = (int)mw + 8;
    if (m > 126) m = m - 94;
    mingwen = (char)m;
    return mingwen;
}

void encryptPassword(char *password) {
    for (int i = 0; i < strlen(password); i++) {
        password[i] = encryption(password[i]);
    }
}

void decryptPassword(char *password) {
    for (int i = 0; i < strlen(password); i++) {
        password[i] = decryption(password[i]);
    }
}

// 初始化用户系统
void initUserSystem() {
    // 确保userHead已经初始化
    if (userHead == NULL) {
        userHead = (User*)malloc(sizeof(User));
        if (userHead == NULL) {
            printf("内存分配失败！\n");
            exit(1);
        }
        strcpy(userHead->username, "head");
        strcpy(userHead->password, "");
        userHead->next = NULL;
    }

    // 从文件加载用户
    loadUsersFromFile();

    // 检查是否存在admin用户，不存在则添加默认admin
    User* current = userHead->next;
    int adminExists = 0;
    while (current != NULL) {
        if (strcmp(current->username, "admin") == 0) {
            adminExists = 1;
            break;
        }
        current = current->next;
    }

    // 若不存在admin，添加默认账号（密码123456，需加密后存储）
    if (!adminExists) {
        User* newAdmin = (User*)malloc(sizeof(User));
        strcpy(newAdmin->username, "admin");
        // 加密默认密码123456（使用encryptPassword函数）
        char defaultPwd[] = "123456";
        encryptPassword(defaultPwd); // 使用正确的加密函数
        strcpy(newAdmin->password, defaultPwd);
        newAdmin->next = NULL;

        // 尾插法添加到链表
        User* tail = userHead;
        while (tail->next != NULL) tail = tail->next;
        tail->next = newAdmin;

        // 保存到文件，确保下次启动生效
        saveUsersToFile();
        printf("已创建默认管理员账号：admin，密码：123456\n");
    }
}

// 从文件加载链表
int loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("提示：用户数据文件 users.txt 不存在，将使用默认设置。\n");
        return 0;
    }

    char tempUsername[MAX_USERNAME_LEN];
    char tempPassword[MAX_PASSWORD_LEN];
    User *tail = userHead;  // 尾指针

    // 确保userHead已经初始化
    if (userHead == NULL) {
        userHead = (User*)malloc(sizeof(User));
        if (userHead == NULL) {
            printf("内存分配失败！\n");
            exit(1);
        }
        strcpy(userHead->username, "head");
        strcpy(userHead->password, "");
        userHead->next = NULL;
    }

    // 清空现有链表（保留头节点）
    while (userHead->next != NULL) {
        User *temp = userHead->next;
        userHead->next = temp->next;
        free(temp);
    }

    // 从文件读取并尾插
    int loadedCount = 0;
    while (fscanf(file, "%s %s", tempUsername, tempPassword) == 2) {
        User *newUser = (User *)malloc(sizeof(User));
        if (newUser == NULL) {
            printf("警告：内存分配失败，无法加载用户 %s\n", tempUsername);
            continue;
        }
        strcpy(newUser->username, tempUsername);
        strcpy(newUser->password, tempPassword);
        newUser->next = NULL;
        tail->next = newUser;
        tail = newUser;
        loadedCount++;
    }

    fclose(file);
    printf("成功从文件加载 %d 个用户\n", loadedCount);
    return loadedCount;
}

// 保存链表到文件
int saveUsersToFile() {
    FILE* file = fopen("users.txt", "w"); // 注意路径：与程序运行目录一致（cmake-build-debug）
    if (file == NULL) {
        printf("保存失败：无法打开文件！错误：%s\n", strerror(errno));
        return 0;
    }

    User* current = userHead->next; // 从第一个用户开始（跳过头节点）
    while (current != NULL) {
        // 按"用户名 加密密码"格式写入，用空格分隔
        fprintf(file, "%s %s\n", current->username, current->password);
        current = current->next;
    }

    fclose(file);
    printf("用户数据已保存到 users.txt\n");
    return 1;
}

// 查找用户（遍历链表）
int findUser(const char *username) {
    User *current = userHead->next;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return 1;  // 找到返回1
        }
        current = current->next;
    }
    return 0;  // 未找到返回0
}

// 检查是否是管理员
int isAdmin() {
    return strcmp(currentUsername, "admin") == 0;
}

// 获取当前登录用户名
const char* getCurrentUsername() {
    return currentUsername;
}

void inputPassword(char *password, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') break;
        else if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        }
        else if (ch >= 32 && ch < 127) {
            password[i++] = ch;
            putchar('*');
            fflush(stdout);
        }
    }
    password[i] = '\0';
    printf("\n");
}

// 注册（尾插法）
int registerUser() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    system("cls");
    printf("\n========== 用户注册 ==========\n\n");

    printf("请输入用户名: ");
    scanf("%s", username);

    if (findUser(username)) {
        printf("用户名已存在！\n");
        system("pause");
        return 0;
    }

    printf("请输入密码: ");
    inputPassword(password, MAX_PASSWORD_LEN);

    printf("请再次输入密码: ");
    inputPassword(confirmPassword, MAX_PASSWORD_LEN);

    if (strcmp(password, confirmPassword) != 0) {
        printf("两次密码不一致！\n");
        system("pause");
        return 0;
    }

    // 创建新节点
    User *newUser = (User *)malloc(sizeof(User));
    if (newUser == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }

    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    encryptPassword(newUser->password);
    newUser->next = NULL;

    // 尾插到链表
    User *tail = userHead;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = newUser;

    saveUsersToFile();
    printf("注册成功！\n");
    system("pause");
    return 1;
}

// 登录（遍历比对）
int loginUser() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int attempts = 3;

    system("cls");
    printf("\n========== 用户登录 ==========\n\n");

    while (attempts > 0) {
        printf("请输入用户名: ");
        scanf("%s", username);

        printf("请输入密码: ");
        inputPassword(password, MAX_PASSWORD_LEN);

        User *current = userHead->next;
        while (current != NULL) {
            char tempPassword[MAX_PASSWORD_LEN];
            strcpy(tempPassword, current->password);
            decryptPassword(tempPassword);

            if (strcmp(current->username, username) == 0 &&
                strcmp(tempPassword, password) == 0) {
                // 记录当前登录用户
                strcpy(currentUsername, username);
                printf("登录成功！欢迎 %s\n", username);
                if (isAdmin()) {
                    printf("您拥有管理员权限，可以进行所有操作。\n");
                } else {
                    printf("您拥有普通用户权限，部分操作可能受限。\n");
                }
                Sleep(1000);
                return 1;
            }

            current = current->next;
        }

        attempts--;
        if (attempts > 0) {
            printf("\n用户名或密码错误！剩余尝试次数: %d\n", attempts);
            system("pause");
            system("cls");
            printf("\n========== 用户登录 ==========\n\n");
        }
    }

    printf("登录失败次数过多，程序退出！\n");
    exit(0);
}

// 释放链表内存（防止内存泄漏）
void freeUserList() {
    User *current = userHead;
    while (current != NULL) {
        User *temp = current;
        current = current->next;
        free(temp);
    }
    userHead = NULL;
    currentUsername[0] = '\0'; // 清空当前登录用户
}