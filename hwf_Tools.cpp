#include"hwf_Tools.h"

void Show_Help()  //提示帮助信息
{
	cout << "****************************欢迎来到交互式表达式求值系统******************************************" << endl;
	cout << "本系统支持：整数、小数，字符串的数据类型，支持如下符号：+ - * / ++ -- && || ( ) ^ - % += -= ==  = " << endl;
	cout << "                          注意： 所有非法的输入都将被自动忽略！                                   " << endl;
	cout << "             本系统支持如下命令：help--显示帮助信息  cls--清屏  exit--退出系统                    " << endl;
	cout << "**************************************************************************************************" << endl;
}


double Str_To_Num(string  s)
{
	double num;
	num = stod(s);  //直接利用string内部的接口
	return num;
}

string Char_To_Str(char a)  //将单个字符转为字符串
{
	string s = "x";
	s[0] = a;
	return s;
}

bool Is_Operatop(char c)    //判断这个字符是不是运算符
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '&' || c == '|' || c == '<' || c == '>' || c == '=' || c== '!')
		return true;
	return false;
}

bool Is_Char(char c)  //判断是不是字母
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return true;
	return false;
}


bool Catch_Cmd(string str) //捕获终端命令
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
		cout << "欢迎下次使用" << endl;
		exit(0);
	}
	return false;
		
	
}