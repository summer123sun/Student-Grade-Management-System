#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "user.h"

// 全局变量
User users[MAX_USERS];
int userCount = 0;

//加密字符
char encryption(char mw){
    char mm;
    int m=(int)mw-8;
    if(m<33){
        m=m+94;
    }
    mm=(char)m;
    return mm;
}
//解密字符
char decryption(char mw){
    char mingwen;
    int m;
    m=(int)mw+8;
    if(m>126){
        m=m-94;
    }
    mingwen=(char)m;
    return mingwen;
}

// 加密密码
void encryptPassword(char *password) {
    for (int i = 0; i < strlen(password); i++) {
        password[i] = encryption(password[i]);
    }
}

// 解密密码
void decryptPassword(char *password) {
    for (int i = 0; i < strlen(password); i++) {
        password[i] = decryption(password[i]);
    }
}

// 初始化用户系统
void initUserSystem() {
    userCount = 0;
    // 加载默认管理员账号
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "123456");
    encryptPassword(users[0].password);
    userCount = 1;
}

// 从文件加载用户
int loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0; // 文件不存在
    }

    userCount = 0;
    char tempUsername[MAX_USERNAME_LEN];
    char tempPassword[MAX_PASSWORD_LEN];
    
    while (fscanf(file, "%s %s", tempUsername, tempPassword) == 2 && userCount < MAX_USERS) {
        strcpy(users[userCount].username, tempUsername);
        strcpy(users[userCount].password, tempPassword);
        userCount++;
    }

    fclose(file);
    return 1;
}

// 保存用户到文件
int saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("无法保存用户信息！\n");
        return 0;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
    return 1;
}

// 查找用户
int findUser(const char *username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

// 用户注册
int registerUser() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    system("cls");
    printf("\n========== 用户注册 ==========\n\n");

    // 输入用户名
    printf("请输入用户名: ");
    scanf("%s", username);

    // 检查用户名是否已存在
    if (findUser(username) != -1) {
        printf("用户名已存在！\n");
        system("pause");
        return 0;
    }

    // 输入密码（带回显*）
    printf("请输入密码: ");
    int i = 0;
    char ch;
    while (i < MAX_PASSWORD_LEN - 1 && (ch = getch()) != '\r') {
        if (ch == '\b' && i > 0) { // 退格
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");

    // 确认密码
    printf("请再次输入密码: ");
    i = 0;
    while (i < MAX_PASSWORD_LEN - 1 && (ch = getch()) != '\r') {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            confirmPassword[i++] = ch;
            printf("*");
        }
    }
    confirmPassword[i] = '\0';
    printf("\n");

    // 验证两次密码是否一致
    if (strcmp(password, confirmPassword) != 0) {
        printf("两次密码不一致！\n");
        system("pause");
        return 0;
    }

    // 添加用户
    if (userCount >= MAX_USERS) {
        printf("用户数量已达上限！\n");
        return 0;
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    encryptPassword(users[userCount].password);
    userCount++;

    // 保存到文件
    saveUsersToFile();

    printf("注册成功！\n");
    system("pause");
    return 1;
}

// 用户登录
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
        int i = 0;
        char ch;
        while (i < MAX_PASSWORD_LEN - 1 && (ch = getch()) != '\r') {
            if (ch == '\b' && i > 0) {
                printf("\b \b");
                i--;
            } else if (ch != '\b') {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0';
        printf("\n");

        // 查找用户
        int userIndex = findUser(username);
        if (userIndex != -1) {
            // 解密密码并验证
            char tempPassword[MAX_PASSWORD_LEN];
            strcpy(tempPassword, users[userIndex].password);
            decryptPassword(tempPassword);
            
            if (strcmp(password, tempPassword) == 0) {
                printf("登录成功！欢迎 %s\n", username);
                Sleep(1000);
                return 1;
            }
        }

        attempts--;
        if (attempts > 0) {
            printf("用户名或密码错误！剩余尝试次数: %d\n", attempts);
            system("pause");
            system("cls");
            printf("\n========== 用户登录 ==========\n\n");
        }
    }

    printf("登录失败次数过多，程序退出！\n");
    return 0;
}