#include "student.h"

string filename("student.txt");       //默认文件

void menu() {
	cout << "+---------------------------------------------+\n";
	cout << "|                  点名管理系统                 |\n";
	cout << "+---------------------------------------------+\n";
	cout << "|   1、查询学生缺勤信息  |  5、添加新学生信息   |\n";
	cout << "|   2、修改学生缺勤信息  |  6、修改学生信息     |\n";
	cout << "|   3、删除学生信息      |  7、显示学生信息     |\n";
	cout << "|   4、随机学生点名      |  8、查询学生信息     |\n";
	cout << "|             9、保存更改信息到文件             |\n";
	cout << "+---------------------------------------------+\n";
	cout << "|                     0、退出                  |\n";
	cout << "+---------------------------------------------+\n";
	cout << "|       提示：修改完数据后务必保存到文件       |\n";
	cout << "+---------------------------------------------+\n";
}

void open()
{
	string flag;
	cin >> flag;
	if (flag == "n")
	{
		cout << "请输入要打开的文件名称：";
		cin >> filename;
	}
	else if (flag == "y")
	{
		cout << "已打开/创建默认文件 student.txt" << endl;
	}
	else
	{
		cout <<"错误的指令，请重新输入(y/n)：";
		open();
	}

}

int main()
{
	cout << "是否使用/创建默认学生信息文件：student.txt (y/n)：" << endl;
	open();
	Student<int> m_stu;
	int choice;
	menu();
	do {
		cout << "请输入指令:";
		cin >> choice;
		switch (choice) 
		{
			try
			{
				m_stu.readFile(filename);
			}
			catch (string &a)
			{
				cout << a;
				system("pause");
				return 0;
			}
		case 1: m_stu.LossQuery(); break;
		case 2: m_stu.Lossmodify(); break;
		case 3: m_stu.deleteBy(); break;
		case 4: m_stu.rollcall(); break;
		case 5: m_stu.logon(); break;
		case 6: m_stu.modify(); break;
		case 7: m_stu.Show(); break;
		case 8: m_stu.Query(); break;
		case 9: m_stu.saveToFile(); break;
		case 0:; break;
		default: cout << "请输入正确的选项" << endl; menu(); break;
		}
	} while (choice);
	return 0;
}