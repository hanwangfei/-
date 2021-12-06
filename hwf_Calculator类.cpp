#include<iostream>
using namespace std;
#include<string>
#include<map>
#include<math.h>
#include<Windows.h>
#include"hwf_Calculator��.h"
#include"hwf_Tools.h"

Calculator::Calculator()
{
	//cout << "���캯������" << endl;
}

Calculator::~Calculator()
{
	//cout << "������������" << endl;
}
//��ʼ�����������û����벢�趨��������ȼ�
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

		//���ջ��out�����ȼ�����ջ�ڣ���ջ    С����ջ�ڷ��ų�ջ�����ڽ�ջ����ջ
		//��һ���ȼ�
		inp["#"] = -1;
		inp["("] = 0, outp["("] = 50;
		inp[")"] = 50, outp[")"] = 0;
		inp["!"] = 49;     //��Ŀ���������Ҫջ�����ȼ����ᵥ������
		inp["++"] = 49, outp["++"] = 48;
		inp["--"] = 49, outp["--"] = 48;


		//�ڶ����ȼ�
		inp["^"] = 13, outp["^"] = 14;   //ע������Ӧ���Ǻ��������
		inp["*"] = 12, outp["*"] = 11;
		inp["/"] = 12, outp["/"] = 11;
		inp["%"] = 13, outp["%"] = 11;

		inp["+"] = 10, outp["+"] = 9;
		inp["-"] = 10, outp["-"] = 9;

		//�������ȼ�
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

//�޳��Ƿ�����
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
		cout << "���ʽ���ڷǷ��ַ����޳���ı��ʽ�ǣ�" << world << endl;
	return world;

}

//����
void Calculator::Traverse()
{
	this->m_Str.push("#");  //ѹһ��#��ջ�ף������ж���ֵ����
	int i;
	for (i = 0; i < this->m_World.size(); i++)
	{
		char c = this->m_World[i];
		if (c == ',')          //������ָ����ã�ֱ����һ��
			continue;
		if (isdigit(c))      //��ȡ��������  
		{
			this->Find_Num(i);   //ת�뷢������
			continue;
		}
		else if (Is_Char(c))   //��ȡ�����ַ�(�ַ���)
		{
			cout << "��ȡ�����ַ�" << endl;

		}
		else             //�Ȳ��������ֲ����ַ����Ƿ������ѱ��޳���ֻ���������,ע�������жϵ�Ŀ�����
		{ 
			if (Is_Operatop(c) && Is_Operatop(this->m_World[i + 1]))   //���������������������������
			{
				Find_AssortedOperatop(i);
				continue;
			}

			else if (c == '-' || c == '!')  //���ܶ�ȡ���˵�Ŀ����� - ���� !
			{
				if (this->m_Num.empty())
				{
					Find_DanmuOperatop(i);
					continue;
				}
				else
				{
					if (i != 0)    //�˾仰��Ϊ�˷�ֹ�����i-1����Խ��
						if (!isdigit(this->m_World[i - 1]) && !Is_Char(this->m_World[i - 1]) && (this->m_World[i-1] != ')'))
						{
							Find_DanmuOperatop(i);
							continue;
						}
				}
			}


			if (outp[Char_To_Str(c)] > inp[this->m_Str.top()])  //ջ�����ȼ��ߣ�������ջ
			{
				this->Cheak_Push(Char_To_Str(c));
				this->m_Str.push(Char_To_Str(c));
				continue;

			}
			else if (outp[Char_To_Str(c)] < inp[this->m_Str.top()])   //ջ�����ȼ��ͣ���������,ע��˴������������
			{
				double ret = this->Cal();   //���㲢�����������ջ
				this->m_Num.push(ret);
				Cheak_Push(Char_To_Str(c));
				this->m_Str.push(Char_To_Str(c));
				this->Has_Brackets();  //�����������

			}
			else if (outp[Char_To_Str(c)] == inp[this->m_Str.top()])  //������ײ������
			{
				this->Cheak_Push(Char_To_Str(c));       
				this->m_Str.pop();
			}
			else
			{
				cout << "�޷���ջ" << endl;   //�����ϲ�����
			}

		}

		

	}
	if (i == this->m_World.size())
		this->Read_End(--i);






}

void Calculator::Cheak_Push(string op)
{
	while (outp[op] < inp[this->m_Str.top()])   //��ֹ������ѻ�ȷ��ջ�����ȼ��߲ſ�����ջ
	{
		double ret = this->Cal();   //���㲢�����������ջ
		this->m_Num.push(ret);
	}
}
//�Ƿ��ȡ�����һ���ַ����䴦����
void Calculator::Read_End(int& i)  
{
	this->Has_Brackets();
	//���û�ֱ������س�,��ʱ��Ҫ���������㣬ֱ���������ջ��Ԫ�����
	if (i == this->m_World.size() - 1)
	{

		while (!this->m_Str.empty())
		{
			if (this->m_Str.top() == "#")
			{
				return;  //ֻʣ���ѹ���#����������ѽ���
			}
			else
			{
				double ret = this->Cal();   //���㲢�����������ջ
				this->m_Num.push(ret);

			}
		}
	}
}


//����
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
				if (rdata == 0)   //��ĸ����Ϊ0
				{
					cout << "���ʽ���󣬷�ĸ������Ϊ0" << endl;
					cout << "��ӭ�´�ʹ��" << endl;
					exit(0);

				}
				return ldata / rdata;
			}
			else if (op == "%")
			{
				if (rdata == 0)   //��ĸ����Ϊ0
				{
					cout << "���ʽ���󣬷�ĸ������Ϊ0" << endl;
					cout << "��ӭ�´�ʹ��" << endl;
					exit(0);

				}
				return fmod(ldata, rdata);   //����math�ṩ��fmod�������ԶԸ�����ȡ��

			}
			else if (op == "^")
				return pow(ldata, rdata);   //����math�ṩ����������
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
				cout << "���ʽ����,�밴Ҫ������" << endl;
				cout << "��ӭ�´�ʹ��" << endl;
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
	else            //�� !��������� ,ֻȡ�Ҳ�����
	{
		double rdata = this->m_Num.top();
		this->m_Num.pop();

		if (rdata == 0)
		{
			return 1;

		}
		return 0;    //��0ȡ��ȫ������1

	}




}



//�����ŵ����ֱ��ɾ���������
void Calculator::Has_Brackets()
{
	if (this->m_Str.top() == ")")
	{
		cout << "ɾ��������" << endl;
		this->m_Str.pop();
		while(this->m_Str.top() != "(")
		{
			double ret = this->Cal();
			this->m_Num.push(ret);
			
		}
		cout << "ɾ��������" << endl;
		this->m_Str.pop();
		

	}

}

//����������
void Calculator::Find_Num(int& i)
{
	int start = i;

	for (; isdigit(this->m_World[i]) || this->m_World[i] == '.'; i++)
	{

	}
	int len = i - start;  //��¼���ֵĳ��ȣ�ע�����С����

	string num = this->m_World.substr(start, len);   //ͨ��substr������ȡ������Ƭ��
	this->m_Num.push(Str_To_Num(num));  //ѹ������ջ
	i--;  //�˴�Ҫ��i��Ϊ���ֵ�ĩβ�±꣬��Ϊ����i++

}

//������������
void Calculator::Find_AssortedOperatop(int& i)
{
	string op = this->m_World.substr(i, 2);
	Cheak_Push(op);
	
	this->m_Str.push(op);
	i++;  //Խ����һ���ַ�
}

//������Ŀ�����
void Calculator::Find_DanmuOperatop(int& i)
{
	if (this->m_World[i] == '-')   //��Ŀ�����-,��һ��һ�������ֻ��ַ���
	{
		if (isdigit(this->m_World[i + 1]))  //   ��Ŀ������������������
		{
			int start = i;

			for (i = i + 1; isdigit(this->m_World[i]) || this->m_World[i] == '.'; i++)
			{

			}
			int len = i - start;  //��¼���ֵĳ��ȣ�ע�����С����

			string num = this->m_World.substr(start, len);   //ͨ��substr������ȡ������Ƭ��
			this->m_Num.push(Str_To_Num(num));  //ѹ������ջ
			i--;  //�˴�Ҫ��i��Ϊ���ֵ�ĩβ�±꣬��Ϊ����i++


		}
		else if (this->m_World[i + 1] == '(')    //  ��Ŀ��������������  ����  -(1+3)
		{
			this->m_World.insert(i + 1, "1*");       //ת����ʽΪ -1*(1+3)
			i--;     //���±������λ�ã���ʱ�ͻ�תΪ��Ŀ�����������ֵķ�ʽ����


		}
		else if (Is_Char(this->m_World[i + 1]))  //��Ŀ�����������ַ�(��)
		{

			cout << "������" << endl;
			exit(0);

		}
		else
		{
			cout << "���ʽ����" << endl;
			exit(0);
		}


	}
	else                           //��Ŀ�����  ! ֱ����ջ
	{
		Cheak_Push(Char_To_Str(this->m_World[i]));
		this->m_Str.push(Char_To_Str(this->m_World[i]));
		return;

	}

}