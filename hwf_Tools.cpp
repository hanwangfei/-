#include"hwf_Tools.h"

void Show_Help()  //��ʾ������Ϣ
{
	cout << "****************************��ӭ��������ʽ���ʽ��ֵϵͳ******************************************" << endl;
	cout << "��ϵͳ֧�֣�������С�����ַ������������ͣ�֧�����·��ţ�+ - * / ++ -- && || ( ) ^ - % += -= ==  = " << endl;
	cout << "                          ע�⣺ ���зǷ������붼�����Զ����ԣ�                                   " << endl;
	cout << "             ��ϵͳ֧���������help--��ʾ������Ϣ  cls--����  exit--�˳�ϵͳ                    " << endl;
	cout << "**************************************************************************************************" << endl;
}


double Str_To_Num(string  s)
{
	double num;
	num = stod(s);  //ֱ������string�ڲ��Ľӿ�
	return num;
}

string Char_To_Str(char a)  //�������ַ�תΪ�ַ���
{
	string s = "x";
	s[0] = a;
	return s;
}

bool Is_Operatop(char c)    //�ж�����ַ��ǲ��������
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '&' || c == '|' || c == '<' || c == '>' || c == '=' || c== '!')
		return true;
	return false;
}

bool Is_Char(char c)  //�ж��ǲ�����ĸ
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return true;
	return false;
}


bool Catch_Cmd(string str) //�����ն�����
{
	if (str == "help")
	{
		Show_Help();
		return true;

	}
	if (str == "cls")
	{
		system("cls");
		return true;
	}
	if (str == "exit")
	{
		cout << "��ӭ�´�ʹ��" << endl;
		exit(0);
	}
	return false;
		
	
}