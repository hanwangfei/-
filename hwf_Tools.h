#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<stack>
void Show_Help();  //��ʾ������Ϣ

double Str_To_Num(string  s); //���ַ���ת��Ϊdouble
string Char_To_Str(char a);  //�������ַ�תΪ�ַ���

bool Is_Operatop(char c);   //�ж��ǲ�����ϲ�����
bool Is_Char(char c);  //�ж��ǲ�����ĸ

bool Catch_Cmd(string str);  //�����ն�����
