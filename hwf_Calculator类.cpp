#include<iostream>
using namespace std;
#include<string>
#include<map>
#include<math.h>
#include<Windows.h>
#include"hwf_Calculator类.h"
#include"hwf_Tools.h"

Calculator::Calculator()
{
	//cout << "构造函数调用" << endl;
}

Calculator::~Calculator()
{
	//cout << "析构函数调用" << endl;
}
//初始化函数接收用户输入并设定运算符优先级
bool Calculator::Init()    
{
	string world;
	getline(cin, world);
	if (Catch_Cmd(world))
	{
		return false;
	}
	else
	{
		m_World = this->Clear_BlankCharacter(world);

		//如果栈外out的优先级大于栈内，入栈    小于则栈内符号出栈计算在将栈外入栈
		//第一优先级
		inp["#"] = -1;
		inp["("] = 0, outp["("] = 50;
		inp[")"] = 50, outp[")"] = 0;
		inp["!"] = 49;     //单目运算符不需要栈外优先级，会单独处理
		inp["++"] = 49, outp["++"] = 48;
		inp["--"] = 49, outp["--"] = 48;


		//第二优先级
		inp["^"] = 13, outp["^"] = 14;   //注意求幂应该是后进的先算
		inp["*"] = 12, outp["*"] = 11;
		inp["/"] = 12, outp["/"] = 11;
		inp["%"] = 13, outp["%"] = 11;

		inp["+"] = 10, outp["+"] = 9;
		inp["-"] = 10, outp["-"] = 9;

		//第三优先级
		inp["<"] = 8, outp[">"] = 7;
		inp["<="] = 8, outp["<="] = 7;
		inp[">="] = 8, outp[">="] = 7;

		inp["=="] = 6, outp["=="] = 5;
		inp["!="] = 6, outp["!="] = 5;
		inp["&&"] = 4, outp["&&"] = 3;
		inp["||"] = 2, outp["||"] = 1;
		
	}
	return true;
	
	
}

//剔除非法输入
string Calculator::Clear_BlankCharacter(string& world)
{
	bool flag = false;
	for (int i = 0; i < world.size(); i++)
	{
		if (world[i] < 33 || (world[i] > 33 && world[i] < 37) ||world[i]== 39 || world[i] == 58 || world[i] == 59 || world[i] == 63 || world[i] == 64 || world[i] == 91 || world[i] == 93 || world[i] == 95 || world[i] == 96 || world[i] == 123 || world[i]>124)
		{
			world.erase(i, 1);
			i--;
			flag = true;
		}
	}
	if (flag)
		cout << "表达式存在非法字符，剔除后的表达式是：" << world << endl;
	return world;

}

//遍历
void Calculator::Traverse()
{
	this->m_Str.push("#");  //压一个#到栈底，便于判断求值结束
	int i;
	for (i = 0; i < this->m_World.size(); i++)
	{
		char c = this->m_World[i];
		if (c == ',')          //逗号起分割作用，直接下一个
			continue;
		if (isdigit(c))      //读取到了数字  
		{
			this->Find_Num(i);   //转入发现数字
			continue;
		}
		else if (Is_Char(c))   //读取到了字符(字符串)
		{
			cout << "读取到了字符" << endl;

		}
		else             //既不是数字又不是字符而非法输入已被剔除则只能是运算符,注意优先判断单目运算符
		{ 
			if (Is_Operatop(c) && Is_Operatop(this->m_World[i + 1]))   //连续两个运算符，出现组合运算符
			{
				Find_AssortedOperatop(i);
				continue;
			}

			else if (c == '-' || c == '!')  //可能读取到了单目运算符 - 或者 !
			{
				if (this->m_Num.empty())
				{
					Find_DanmuOperatop(i);
					continue;
				}
				else
				{
					if (i != 0)    //此句话是为了防止下面的i-1出现越界
						if (!isdigit(this->m_World[i - 1]) && !Is_Char(this->m_World[i - 1]) && (this->m_World[i-1] != ')'))
						{
							Find_DanmuOperatop(i);
							continue;
						}
				}
			}


			if (outp[Char_To_Str(c)] > inp[this->m_Str.top()])  //栈外优先级高，符号入栈
			{
				this->Cheak_Push(Char_To_Str(c));
				this->m_Str.push(Char_To_Str(c));
				continue;

			}
			else if (outp[Char_To_Str(c)] < inp[this->m_Str.top()])   //栈外优先级低，进行运算,注意此处考虑括号情况
			{
				double ret = this->Cal();   //计算并将结果入数字栈
				this->m_Num.push(ret);
				Cheak_Push(Char_To_Str(c));
				this->m_Str.push(Char_To_Str(c));
				this->Has_Brackets();  //考虑括号情况

			}
			else if (outp[Char_To_Str(c)] == inp[this->m_Str.top()])  //右括号撞左括号
			{
				this->Cheak_Push(Char_To_Str(c));       
				this->m_Str.pop();
			}
			else
			{
				cout << "无法入栈" << endl;   //理论上不存在
			}

		}

		

	}
	if (i == this->m_World.size())
		this->Read_End(--i);






}

void Calculator::Cheak_Push(string op)
{
	while (outp[op] < inp[this->m_Str.top()])   //防止运算符堆积确保栈外优先级高才可以入栈
	{
		double ret = this->Cal();   //计算并将结果入数字栈
		this->m_Num.push(ret);
	}
}
//是否读取到最后一个字符及其处理方法
void Calculator::Read_End(int& i)  
{
	this->Has_Brackets();
	//当用户直接输入回车,此时需要额外做运算，直到将运算符栈的元素清空
	if (i == this->m_World.size() - 1)
	{

		while (!this->m_Str.empty())
		{
			if (this->m_Str.top() == "#")
			{
				return;  //只剩最初压入的#，代表计算已结束
			}
			else
			{
				double ret = this->Cal();   //计算并将结果入数字栈
				this->m_Num.push(ret);

			}
		}
	}
}


//计算
double Calculator::Cal()
{
	string op = this->m_Str.top();
	this->m_Str.pop();  
	if (op != "!")
	{
		if (op != "++" && op != "--")
		{
			double rdata = this->m_Num.top();
			this->m_Num.pop();
			double ldata = this->m_Num.top();
			this->m_Num.pop();

			if (op == "+")
				return ldata + rdata;
			else if (op == "-")
				return ldata - rdata;
			else if (op == "*")
				return ldata * rdata;
			else if (op == "/")
			{
				if (rdata == 0)   //分母不能为0
				{
					cout << "表达式有误，分母不可以为0" << endl;
					cout << "欢迎下次使用" << endl;
					exit(0);

				}
				return ldata / rdata;
			}
			else if (op == "%")
			{
				if (rdata == 0)   //分母不能为0
				{
					cout << "表达式有误，分母不可以为0" << endl;
					cout << "欢迎下次使用" << endl;
					exit(0);

				}
				return fmod(ldata, rdata);   //调用math提供的fmod函数可以对浮点数取余

			}
			else if (op == "^")
				return pow(ldata, rdata);   //调用math提供的求幂运算
			else if (op == ">")
				return ldata > rdata ? 1 : 0;
			else if (op == "<")
				return ldata < rdata ? 1 : 0;
			else if (op == ">=")
				return ldata >= rdata ? 1 : 0;
			else if (op == "<=")
				return ldata <= rdata ? 1 : 0;
			else if (op == "==")
				return ldata == rdata ? 1 : 0;
			else if (op == "&&")
				return (ldata == 1 && rdata == 1) ? 1 : 0;
			else if (op == "||")
				return (ldata == 1 || rdata == 1) ? 1 : 0;
			else if (op == "!=")
				return ldata == rdata ? 0 : 1;

			else
			{
				cout << "表达式有误,请按要求输入" << endl;
				cout << "欢迎下次使用" << endl;
				exit(0);

			}

		}
		else
		{
			if (op == "++")
			{
				double data = this->m_Num.top();
				this->m_Num.pop();
				return data+1;

			}
			if (op == "--")
			{
				double data = this->m_Num.top();
				this->m_Num.pop();
				return data-1;

			}
		}
		

	}
	else            //对 !运算符处理 ,只取右操作数
	{
		double rdata = this->m_Num.top();
		this->m_Num.pop();

		if (rdata == 0)
		{
			return 1;

		}
		return 0;    //非0取反全部返回1

	}




}



//有括号的情况直接删除这对括号
void Calculator::Has_Brackets()
{
	if (this->m_Str.top() == ")")
	{
		cout << "删除右括号" << endl;
		this->m_Str.pop();
		while(this->m_Str.top() != "(")
		{
			double ret = this->Cal();
			this->m_Num.push(ret);
			
		}
		cout << "删除左括号" << endl;
		this->m_Str.pop();
		

	}

}

//读到了数字
void Calculator::Find_Num(int& i)
{
	int start = i;

	for (; isdigit(this->m_World[i]) || this->m_World[i] == '.'; i++)
	{

	}
	int len = i - start;  //记录数字的长度，注意包含小数点

	string num = this->m_World.substr(start, len);   //通过substr方法截取该数字片段
	this->m_Num.push(Str_To_Num(num));  //压入数字栈
	i--;  //此处要将i置为数字的末尾下标，因为后续i++

}

//读到组合运算符
void Calculator::Find_AssortedOperatop(int& i)
{
	string op = this->m_World.substr(i, 2);
	Cheak_Push(op);
	
	this->m_Str.push(op);
	i++;  //越过后一个字符
}

//读到单目运算符
void Calculator::Find_DanmuOperatop(int& i)
{
	if (this->m_World[i] == '-')   //单目运算符-,下一个一定是数字或字符串
	{
		if (isdigit(this->m_World[i + 1]))  //   单目运算符后面跟数字数字
		{
			int start = i;

			for (i = i + 1; isdigit(this->m_World[i]) || this->m_World[i] == '.'; i++)
			{

			}
			int len = i - start;  //记录数字的长度，注意包含小数点

			string num = this->m_World.substr(start, len);   //通过substr方法截取该数字片段
			this->m_Num.push(Str_To_Num(num));  //压入数字栈
			i--;  //此处要将i置为数字的末尾下标，因为后续i++


		}
		else if (this->m_World[i + 1] == '(')    //  单目运算符后面跟括号  比如  -(1+3)
		{
			this->m_World.insert(i + 1, "1*");       //转变表达式为 -1*(1+3)
			i--;     //重新遍历这个位置，此时就会转为单目运算符后跟数字的方式处理


		}
		else if (Is_Char(this->m_World[i + 1]))  //单目运算符后面跟字符(串)
		{

			cout << "待开发" << endl;
			exit(0);

		}
		else
		{
			cout << "表达式有误" << endl;
			exit(0);
		}


	}
	else                           //单目运算符  ! 直接入栈
	{
		Cheak_Push(Char_To_Str(this->m_World[i]));
		this->m_Str.push(Char_To_Str(this->m_World[i]));
		return;

	}

}