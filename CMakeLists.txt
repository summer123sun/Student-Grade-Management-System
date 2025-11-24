cmake_minimum_required(VERSION 4.0)
project(Student_Grade_Management_System C)

set(CMAKE_C_STANDARD 99)

# 只添加.c文件，不要添加.h文件
add_executable(Student_Grade_Management_System
        "main.c"
        "student.c"
        "user.c"
)