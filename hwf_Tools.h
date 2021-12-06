#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<stack>
void Show_Help();  //提示帮助信息

double Str_To_Num(string  s); //将字符串转化为double
string Char_To_Str(char a);  //将单个字符转为字符串

bool Is_Operatop(char c);   //判断是不是组合操作符
bool Is_Char(char c);  //判断是不是字母

bool Catch_Cmd(string str);  //捕获终端命令
