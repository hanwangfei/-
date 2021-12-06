#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<stack>
class Calculator
{
public:
	string m_World; 
	stack<string> m_Str;  //�����ջ
	stack<double> m_Num;  //����ջ
	map<string, int> outp, inp;   //���ò��������ȼ�
	map<string, double> m_Variable;  //�����ֵ�
	 

	Calculator();
	~Calculator();
	
	bool Init();    //��ʼ�����������û�����,���趨���ȼ�����ʼ���ɹ�����true
	string Clear_BlankCharacter(string& world);  //�޳��Ƿ�����
	
	void Traverse();    //����
	void Read_End(int& i);  //�Ƿ��ȡ�����һ���ַ�
	void Has_Brackets();  //�����ŵ����ֱ��ɾ���������
	void Find_Num(int &i);    //����������
	void Find_DanmuOperatop(int &i);
	void Find_AssortedOperatop(int& i);
	void Cheak_Push(string op);    //����ַ���op�Ƿ�����������ջ

	double Cal();  //����
	
};

