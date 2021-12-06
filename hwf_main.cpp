/*
开发时间：2021_8_15 20.35
开发人员：Lenvo
开发工具：Visual Studio 2019
*/
#include<iostream>
using namespace std;
#include<map>
#include<string>
#include"hwf_Calculator类.h"
#include"hwf_Tools.h"


int main()
{
	
	
	Show_Help();
	Calculator p;
	
	while (true)   //该循环为死循环，用户输入exit才可直接退出
	{
		if (p.Init())  //p.Init()//接收用户输入并初始化优先级   初始化失败(即用户输入了cmd命令)什么也不做
		{
			p.Traverse();

			while (!p.m_Num.empty())   //清空数字栈
			{
				cout << p.m_Num.top() << endl;
				p.m_Num.pop();

			}
			while (!p.m_Str.empty())  //清空运算符栈
			{
				//cout << p.m_Str.top() << endl;
				p.m_Str.pop();

			}

		}
		

	}
	
	
	
	system("pause");
	return 0;
}