/*
����ʱ�䣺2021_8_15 20.35
������Ա��Lenvo
�������ߣ�Visual Studio 2019
*/
#include<iostream>
using namespace std;
#include<map>
#include<string>
#include"hwf_Calculator��.h"
#include"hwf_Tools.h"


int main()
{
	
	
	Show_Help();
	Calculator p;
	
	while (true)   //��ѭ��Ϊ��ѭ�����û�����exit�ſ�ֱ���˳�
	{
		if (p.Init())  //p.Init()//�����û����벢��ʼ�����ȼ�   ��ʼ��ʧ��(���û�������cmd����)ʲôҲ����
		{
			p.Traverse();

			while (!p.m_Num.empty())   //�������ջ
			{
				cout << p.m_Num.top() << endl;
				p.m_Num.pop();

			}
			while (!p.m_Str.empty())  //��������ջ
			{
				//cout << p.m_Str.top() << endl;
				p.m_Str.pop();

			}

		}
		

	}
	
	
	
	system("pause");
	return 0;
}