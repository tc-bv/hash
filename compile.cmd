@echo off
chcp 936
cd %~dp0
echo 将使用 g++ demo.cpp -o demo.exe -std=c++11 -static -static-libgcc -static-libstdc++编译
g++ demo.cpp -o demo.exe -std=c++11 -static -static-libgcc -static-libstdc++
echo 编译完成。
pause