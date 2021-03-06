﻿#pragma once
#include <string>
#include <fstream>
#include<iostream>
#include <time.h>
#define STU_NUM_MAX 64      //最大学生数量
using namespace std;

typedef struct student {
	unsigned stu_id;    //学号
	string stu_name;    //姓名
	unsigned stu_age;   //年龄
	string stu_sex;     //性别
	string stu_birth;   //籍贯
	string stu_tel;     //电话
	string stu_email;   //电子邮件
	string stu_department;     //系别
	string stu_major;   //专业
	string stu_class;   //班级
	int stu_lossCount;  //缺勤次数
	student *stu_next;    //射线结构链表
} student;


template <typename T>
class Student
{
	friend class Call;

public:
	Student();     //构造函数
	~Student();    //析构函数

				   //录入学生信息
	student *createByStdin(int model, student &tmp); // 从标准输入中创建学生，model = 1: 不读取学号，2:不读取姓名，其他，读取所有信息。
	void logon(); // 连续录入学生信息


				  //查找
	void Query() const; // 查询学生信息
	student *findById(unsigned id) const; // 根据学号查找
	student *findByName(const string &name) const; // 根据姓名查找
	student *findBySex(const string &sex) const; // 根据性别查找
	student *findByEmail(const string &email) const; // 根据电子邮箱查找

													 //删除
	void deleteBy(); // 删除
	bool deleteById(unsigned &id); // 根据学号删除
	bool deleteByName(string &name); // 根据姓名删除

									 //修改
	void modify(); // 修改
	bool modifyById(); // 根据学号修改
	bool modifyByName(); // 根据姓名修改

						 //显示
	void Show() const; // 列出学生信息

					   //文件操作
	void saveToFile(); // 保存到文件
	void readFile(string new_file = "student.txt"); // 读取文件
	bool Student::insert(const student &astu);

	//点名
	void rollcall();   // 随机点名
	bool IsExist(int id);   //判断是否已点名

							//缺勤查询函数
	void Student::LossQuery() const;
	student *LossfindByName(const string &name) const;
	student *LossfindById(unsigned id)  const;

	//缺勤修改函数
	void Lossmodify();
	bool modifyLossById();
	bool modifyLossByName();

	unsigned headCount() const;

private:
	student *head;   //全局的引导进入链表的指针
	T len;
	T exist[STU_NUM_MAX];
};

int index = 0;    //点名次数

void show(student *p);
void Lossshow(student *p);

template <typename T>
Student<T>::Student()
{
	head = new student;
	head->stu_id = 0;
	head->stu_name = "No name";
	head->stu_next = NULL;
	len = 0;
}

template <typename T>
Student<T>::~Student()
{
	student *p = head, *q;
	while (p)
	{
		q = p;
		p = q->stu_next;
		delete q;
	}
}

//注册函数
template <typename T>
void Student<T>::logon()
{
	student tmp;
	cout << "学号 (0 结束输入 ): ";
	cin >> tmp.stu_id;

	while (tmp.stu_id)
	{
		if (findById(tmp.stu_id) == NULL)
		{
			cout << "姓    名: ";
			cin >> tmp.stu_name;
			cout << "年    龄: ";
			cin >> tmp.stu_age;
			cout << "性    别: ";
			cin >> tmp.stu_sex;
			cout << "籍    贯: ";
			cin >> tmp.stu_birth;
			cout << "系    别: ";
			cin >> tmp.stu_department;
			cout << "专    业: ";
			cin >> tmp.stu_major;
			cout << "班    级: ";
			cin >> tmp.stu_class;
			cout << "手    机: ";
			cin >> tmp.stu_tel;
			cout << "电子邮箱: ";
			cin >> tmp.stu_email;
			cout << "缺勤次数: ";
			cin >> tmp.stu_lossCount;
			insert(tmp);

		}
		else cout << "重复的学号: " << tmp.stu_id << endl;
		cout << "学号 (0 结束输入): ";
		cin >> tmp.stu_id;
	}

}

//查找函数
template <typename T>
void Student<T>::Query() const {
	int select;
	unsigned id;
	string name;
	string sex;
	string email;
	student *p;
	cout << "1、按学号查询\n2、按姓名查询\n3、按性别查询\n4、按Email查询\n0、返回\n";
	cin >> select;
	switch (select)
	{
	case 1: cout << "请输入学号: "; cin >> id;
		if ((p = findById(id))) show(p->stu_next);
		break;
	case 2: cout << "请输入姓名: "; cin >> name;
		if ((p = findByName(name))) show(p->stu_next);
		break;
	case 3:cout << "请输入性别："; cin >> sex;
		if ((p = findBySex(sex))) show(p->stu_next);
		break;
	case 4:cout << "请输入Email："; cin >> email;
		if ((p = findByEmail(email))) show(p->stu_next);
		break;
	case 0: return;
	default: cout << "选择错误. \n";
	}
}
template <typename T>
student *Student<T>::findByEmail(const string &email) const {
	student *p;
	for (p = head; p->stu_next; p = p->stu_next)
		if (p->stu_next->stu_email == email) return p;
	cout << "没有找到输入的Email" << endl;
	return NULL;
}
template <typename T>
student *Student<T>::findBySex(const string &sex) const {
	student *p;
	for (p = head; p->stu_next; p = p->stu_next)
		if (p->stu_next->stu_sex == sex) return p;
	cout << "没有找到输入的性别的用户" << endl;
	return NULL;
}
template <typename T>
student *Student<T>::findByName(const string &name) const {
	student *p;
	for (p = head; p->stu_next; p = p->stu_next)
		if (p->stu_next->stu_name == name) return p;
	cout << "没有找到输入的姓名" << endl;
	return NULL;
}
template <typename T>
student *Student<T>::findById(unsigned id)  const
{
	student *p;
	for (p = head; p->stu_next; p = p->stu_next)
		if (p->stu_next->stu_id == id) return p;
	return NULL;
}

//删除函数
template <typename T>
void Student<T>::deleteBy() {
	int select;
	unsigned id;
	string name;
	cout << "1、按学号删除\n2、按姓名删除\n0、返回\n";
	cin >> select;
	switch (select)
	{
	case 1: cout << "请输入学号: "; cin >> id;
		deleteById(id);
		break;
	case 2: cout << "请输入姓名: "; cin >> name;
		deleteByName(name);
		break;
	case 0: return;
	default: cout << "选择错误. \n";
	}
}
template <typename T>
bool Student<T>::deleteById(unsigned &id) {
	student *q, *p;
	p = findById(id);
	if (p == NULL)
	{
		cout << "没有找到学号是 \"" << id << "\" 的学生，删除失败! \n";
		return false;
	}
	q = p->stu_next;
	p->stu_next = q->stu_next;
	delete q;
	cout << "成功删除 " << id << " 的信息. \n";
	return true;
}
template <typename T>
bool Student<T>::deleteByName(string &name) {
	student *q, *p;
	p = findByName(name);
	if (p == NULL) {
		cout << "没有找到姓名是 \"" << name << "\" 的学生, 删除失败! \n";
		return false;
	}
	q = p->stu_next;
	p->stu_next = q->stu_next;
	delete q;
	cout << "成功删除 " << name << " 的信息. \n";
	return true;
}

//修改函数
template <typename T>
void Student<T>::modify() {
	int select;
	cout << "1、按学号修改\n2、按姓名修改\n0、返回\n";
	cin >> select;
	switch (select) {
	case 1: if (modifyById()) cout << "修改成功. \n"; break;
	case 2: if (modifyByName()) cout << "修改成功. \n"; break;
	case 0: return;
	default: cout << "选择错误. \n";
	}
}
template <typename T>
bool Student<T>::modifyById()
{
	student *p;
	unsigned id;
	cout << "输入要修改的学号: ";
	cin >> id;
	p = findById(id);
	if (p == NULL)
	{
		cout << "没有找到学号是 \"" << id << "\" 的学生, 修改失败! \n";
		return false;
	}
	createByStdin(1, *(p->stu_next));
	return true;
}
template <typename T>
bool Student<T>::modifyByName()
{
	student *p;
	string name;
	cout << "输入要修改人的姓名: ";
	cin >> name;
	p = findByName(name);
	if (p == NULL) {
		cout << "没有找到姓名是 \"" << name << "\" 的学生, 修改失败! \n";
		return false;
	}
	createByStdin(2, *(p->stu_next));
	return true;
}
template <typename T>
student *Student<T>::createByStdin(int model, student &tmp)
{
	if (model != 1) { cout << "学    号: "; cin >> tmp.stu_id; }
	if (model != 2) { cout << "姓    名: "; cin >> tmp.stu_name; }
	cout << "年龄：";
	cin >> tmp.stu_age;
	cout << "性    别: ";
	cin >> tmp.stu_sex;
	cout << "籍    贯: ";
	cin >> tmp.stu_birth;
	cout << "系    别: ";
	cin >> tmp.stu_department;
	cout << "专    业:";
	cin >> tmp.stu_major;
	cout << "班    级:";
	cin >> tmp.stu_class;
	cout << "手    机: ";
	cin >> tmp.stu_tel;
	cout << "电子邮箱: ";
	cin >> tmp.stu_email;
	cout << "缺勤次数: ";
	cin >> tmp.stu_lossCount;

	return &tmp;
}

//文件操作函数
template <typename T>
void Student<T>::saveToFile()
{
	string new_file;
	cout << "是否保存至默认文件 student.txt (y/n):";
	string flag;
	cin >> flag;
	if (flag == "n")
	{
		cout << "请输入欲保存的文件名: ";
		cin >> new_file;
	}
	else
	{
		new_file = "student.txt";
	}
	fstream file;
	file.open(new_file.c_str(), ios::out);
	if (file.bad())
	{
		cout << "文件打开失败. " << endl;
		return;
	}
	len = headCount();
	file << len << endl;
	student *pHead = head->stu_next;
	while (pHead != NULL)
	{
		file << pHead->stu_id << endl;
		file << pHead->stu_name << endl;
		file << pHead->stu_sex << endl;
		file << pHead->stu_age << endl;
		file << pHead->stu_birth << endl;
		file << pHead->stu_department << endl;
		file << pHead->stu_major << endl;
		file << pHead->stu_class << endl;
		file << pHead->stu_email << endl;
		file << pHead->stu_tel << endl;
		file << pHead->stu_lossCount << endl;
		pHead = pHead->stu_next;
	}
	file.close();
	cout << "保存成功！" << endl;
	return;
}
template <typename T>
void Student<T>::readFile(string new_file)
{
	fstream file;
	file.open(new_file.c_str(), ios::in);
	if (file.bad())
	{
		throw string("文件打开失败. ");
	}
	int tmp;
	file >> len;
	tmp = len;
	if (!len)
	{
		return;
	}
	student pHead;
	file.get();
	while (len--)
	{
		file >> pHead.stu_id;
		file >> pHead.stu_name;
		file >> pHead.stu_sex;
		file >> pHead.stu_age;
		file >> pHead.stu_birth;
		file >> pHead.stu_department;
		file >> pHead.stu_major;
		file >> pHead.stu_class;
		file >> pHead.stu_email;
		file >> pHead.stu_tel;
		file >> pHead.stu_lossCount;
		insert(pHead);
	}
	file.close();
	len = tmp;
	return;
}

template <typename T>
bool Student<T>::insert(const student &astu)
{
	student *newnode, *p = head;
	if (p->stu_next == NULL)    //当没有下一个堆，则新建一个堆来储存修改数据
	{
		p->stu_next = new student(astu);   //用传入的已修改结构初始化
		p->stu_next->stu_next = NULL;      //NULL处理再下一个堆
		return true;
	}
	while (p->stu_next)           //当存在下一个堆
	{
		if (p->stu_next->stu_id == astu.stu_id)    //判重
		{
			return false;
		}
		if (p->stu_next->stu_id > astu.stu_id)    //如果下一个堆的id大于传入id
		{
			newnode = new student(astu);           //newnode指向初始修改结构
			newnode->stu_next = p->stu_next;
			p->stu_next = newnode;               // 移位
			return true;
		}
		p = p->stu_next;    //既不大于也不重复就后移添加
	}
	p->stu_next = new student(astu);
	p->stu_next->stu_next = NULL;
	return true;
}

//显示函数
template <typename T>
void Student<T>::Show() const {
	student *p;
	cout << "----------------------------------------------------------\n";
	for (p = head->stu_next; p; p = p->stu_next)
	{
		show(p);
	}
	cout << "----------------------------------------------------------\n";
}
void show(student *p)
{
	cout << "  学号： " << p->stu_id << "  姓名： " << p->stu_name << "  年龄： " << p->stu_age << "  性别： ";
	cout << p->stu_sex << "  籍贯： " << p->stu_birth << "  系别： " << p->stu_department << endl;
	cout << "  专业： " << p->stu_major << "  班级： " << p->stu_class << "  手机： " << p->stu_tel << "  Email： " << p->stu_email << "  缺勤次数： " << p->stu_lossCount << endl;
}

//结构数量计算函数
template <typename T>
unsigned Student<T>::headCount() const
{
	unsigned cnt = 0;
	student *p;
	for (p = head->stu_next; p; p = p->stu_next, ++cnt);
	return cnt;
}

//点名函数
template <typename T>
void Student<T>::rollcall() // 随机点名
{
	while (index < len)
	{
		student *p = head;
		srand((unsigned)time(NULL));
		int i = 0;
		int randID = rand() % (len - 1 + 1) + 1; // 1~len
		for (int i = 0; i < randID; i++)
		{
			p = p->stu_next;
		}
		if (IsExist(p->stu_id))
		{
			exist[index++] = p->stu_id;
			cout << "随机点到的姓名为：" << p->stu_name << endl;
			cout << "此人是否缺勤？(y/n)" << endl;
			string tmp;
			cin >> tmp;
			if (tmp == "y")
			{
				p->stu_lossCount++;
			}
			cout << "是否继续点名？(y/n)" << endl;
			string flag;
			cin >> flag;
			if (flag == "y")
			{
				rollcall();
			}
			else
				break;
		}
	}
	cout << "点名已完成。" << endl;
	return;
}

template <typename T>
bool Student<T>::IsExist(int id)
{
	for (int i = 0; i<len; i++)
		if (exist[i] == id) return false; //已被点名
	return true; // 未被点名
}

//缺勤查询函数
template <typename T>
void Student<T>::LossQuery() const {
	int select;
	unsigned id;
	string name;
	string sex;
	string email;
	student *p;
	cout << "1、按学号查询\n2、按姓名查询\n0、返回\n";
	cin >> select;
	switch (select)
	{
	case 1: cout << "请输入学号: "; cin >> id;
		if ((p = findById(id))) Lossshow(p->stu_next);
		break;
	case 2: cout << "请输入姓名: "; cin >> name;
		if ((p = findByName(name))) Lossshow(p->stu_next);
		break;
	case 0: return;
	default: cout << "选择错误. \n";
	}
}
template <typename T>
student *Student<T>::LossfindByName(const string &name) const
{
	student *p;
	for (p = head; p->stu_next; p = p->stu_next)
		if (p->stu_next->stu_name == name) return p;
	cout << "没有找到输入的姓名" << endl;
	return NULL;
}
template <typename T>
student *Student<T>::LossfindById(unsigned id)  const
{
	student *p;
	for (p = head; p->stu_next; p = p->stu_next)
		if (p->stu_next->stu_id == id) return p;
	return NULL;
}
void Lossshow(student *p)
{
	cout << "  学号： " << p->stu_id << "  姓名： " << p->stu_name << "  缺勤次数： " << p->stu_lossCount << endl;
}

//缺勤修改函数
template <typename T>
void Student<T>::Lossmodify() {
	int select;
	cout << "1、按学号修改\n2、按姓名修改\n0、返回\n";
	cin >> select;
	switch (select) {
	case 1: if (modifyLossById()) cout << "修改成功. \n"; break;
	case 2: if (modifyLossByName()) cout << "修改成功. \n"; break;
	case 0: return;
	default: cout << "选择错误. \n";
	}
}
template <typename T>
bool Student<T>::modifyLossById()
{
	student *p;
	unsigned id;
	cout << "输入要修改的学号: ";
	cin >> id;
	p = LossfindById(id);
	if (p == NULL)
	{
		cout << "没有找到学号是 \"" << id << "\" 的学生, 修改失败! \n";
		return false;
	}
	cout << "缺勤次数: ";
	cin >> p->stu_next->stu_lossCount;
	return true;
}
template <typename T>
bool Student<T>::modifyLossByName()
{
	student *p;
	string name;
	cout << "输入要修改人的姓名: ";
	cin >> name;
	p = LossfindByName(name);
	if (p == NULL) {
		cout << "没有找到姓名是 \"" << name << "\" 的学生, 修改失败! \n";
		return false;
	}
	cout << "缺勤次数: ";
	cin >> p->stu_next->stu_lossCount;
	return true;
}

