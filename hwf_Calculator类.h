#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<stack>
class Calculator
{
public:
	string m_World; 
	stack<string> m_Str;  //运算符栈
	stack<double> m_Num;  //数字栈
	map<string, int> outp, inp;   //设置操作符优先级
	map<string, double> m_Variable;  //变量字典
	 

	Calculator();
	~Calculator();
	
	bool Init();    //初始化函数接收用户输入,并设定优先级，初始化成功返回true
	string Clear_BlankCharacter(string& world);  //剔除非法输入
	
	void Traverse();    //遍历
	void Read_End(int& i);  //是否读取到最后一个字符
	void Has_Brackets();  //有括号的情况直接删除这对括号
	void Find_Num(int &i);    //读到了数字
	void Find_DanmuOperatop(int &i);
	void Find_AssortedOperatop(int& i);
	void Cheak_Push(string op);    //检查字符串op是否可以入运算符栈

	double Cal();  //计算
	
};

