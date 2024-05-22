# 设定CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(PCmodule)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 添加所有源文件到变量SOURCE
set(SOURCES
    producer_consumer.cpp
)

# 创建一个名为test的可执行文件
add_executable(test ${SOURCES})