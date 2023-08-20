#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <String>
#include "PatientManager.h"
#include <synchapi.h>
#include <consoleapi2.h>
#include <sysinfoapi.h>

/*
*封装函数
*/
//打印病人vector
void ptvector(vector<Patient> a) {
	int id = 18, name = 20, age = 10, time = 18;//输出表格占位
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(id) << "住院号" << resetiosflags(ios::left) // 用完之后清除
		<< setiosflags(ios::right) << setw(name) << "姓名" << setw(name) << "年龄" << setw(time) << "入院时间"
		<< setw(time) << "出院时间"
		<< resetiosflags(ios::right) << endl;
	for (auto& t : a) {
		if (!t.patient_time_out.compare("1111-11-11"))
		{
			t.patient_time_out = "住院中    ";
		}
		cout << setiosflags(ios::left) << setw(id) << t.patient_id << resetiosflags(ios::left) // 用完之后清除
			<< setiosflags(ios::right) << setw(name) << t.patient_name << setw(name) << t.patient_age << setw(time)
			<< t.patient_time_in << setw(time) << t.patient_time_out
			<< resetiosflags(ios::right) << endl;
	}
	cout << "------------------------------------------------------------------------------------------------\n" << endl;
}
//打印病房vector
void ptvector(vector<Ward> a) {
	int id = 8, bed = 8, doc = 10;//输出表格占位
	cout << "------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(id) << "病房号" << resetiosflags(ios::left) // 用完之后清除
		<< setiosflags(ios::right) << setw(bed) << "总床位" << setw(doc) << "负责医生"
		<< resetiosflags(ios::right) << endl;
	for (auto& t : a) {
		cout << setiosflags(ios::left) << setw(id) << t.ward_id << resetiosflags(ios::left) // 用完之后清除
			<< setiosflags(ios::right) << setw(bed) << t.ward_bed << setw(doc) << t.ward_doc
			<< resetiosflags(ios::right) << endl;
	}
	cout << "------------------------------------\n" << endl;
}
//插入病人/病房
bool insert(Patient pt) {
	return	PatientManager::GetInstance()->insert_patient(pt);
}
bool insert(Ward pt) {//重载
	return	PatientManager::GetInstance()->insert_ward(pt);
}
//修改病人/病房
bool update(Patient pt) {
	return	PatientManager::GetInstance()->update_patient(pt);
}
bool update(Ward pt) {
	return	PatientManager::GetInstance()->update_ward(pt);
}
//删除病人
bool delete_patient(long long int id) {
	return PatientManager::GetInstance()->delete_patient(id);
}
//删除病房
bool delete_ward(int id) {
	return PatientManager::GetInstance()->delete_ward(id);
}
//查找病人
void select_patient(string st) {
	ptvector(PatientManager::GetInstance()->get_patient(st));
}
void select_patient(long long int i) {
	ptvector(PatientManager::GetInstance()->get_patient(i));
}
vector<Patient> paitent_vec(long long int i) {
	return PatientManager::GetInstance()->get_patient(i);
}
//查找病房
void select_ward(int st) {
	ptvector(PatientManager::GetInstance()->get_ward(st));
}
void select_ward(string st) {
	ptvector(PatientManager::GetInstance()->get_ward(st));
}
vector<Ward> pt_doc_(int i) {
	return (PatientManager::GetInstance()->get_ward(i));
}
//判断是否有病房信息
vector<int> ward_access() {
	return PatientManager::GetInstance()->ward_id();
}
//住院病人住院号
vector<long long int> pt_in() {
	return PatientManager::GetInstance()->pt_num();
}

//住院号转对应病房号
vector<int> pt_ward(vector<long long int> pt_in) {
	vector<int> pt_ward;
	for (int i = 0; i < pt_in.size(); i++)
	{
		if (to_string(pt_in[i]).length() == 12)
			pt_ward.push_back(pt_in[i] % 10000 / 10);
	}
	return pt_ward;
}


//判断日期是否合法
bool IsLegal(int year, int mon, int day) {
	if ((mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) && (day >= 1 && day <= 31))
	{
		return true;
	}
	else if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && (day >= 1 && day <= 30))
	{
		return true;
	}
	if (mon == 2 && day >= 0 && day <= 29)
	{
		if (day <= 28 || (day == 29 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)))
		{
			return true;
		}
	}
	return false;
}

//构造pt
Patient returnpt() {
	int date_in, date_out, age, ward, bed;
	char stname[20];
	string name, wardst;
	bool manage_patient(), app(), Islegal();//声明
	while (true)
	{
		printf("\n入院日期：");
		scanf_s("%d", &date_in);
		printf("\n出院日期：");
		scanf_s("%d", &date_out);
		if (to_string(date_in).length() == 8 && to_string(date_out).length() == 8 && date_in <= date_out
			&& IsLegal(date_in / 10000, date_in % 10000 / 100, date_in % 100) && IsLegal(date_out / 10000, date_out % 10000 / 100, date_out % 100))
			break;
		else if (date_out == 0)
		{
			date_out = 11111111; break;
		}
		else {
			getchar();
			printf("！！日期非法请重新输入！！");
		}
	}
	printf("\n病人姓名：");
	scanf("%s", stname);
	name = stname;
	while (true)
	{
		printf("\n病人年龄：");
		scanf_s("%d", &age);
		if (age >= 0 && age <= 150)
			break;
		else
			printf("！！输入有错请重新输入！！");
	}
	while (true)
	{
		string st;
		printf("\n病房号：");
		scanf_s("%d", &ward);
		if (ward > 0 && ward <= 9) {
			st = "00";
			wardst = st.append(to_string(ward)); break;
		}
		else if (ward >= 10 && ward <= 99)
		{
			st = "0";
			wardst = st.append(to_string(ward)); break;
		}
		else if (ward >= 100 && ward <= 999)
		{
			wardst = to_string(ward); break;
		}
		else
			printf("！！输入有错请重新输入！！");
	}
	while (true)
	{
		printf("\n病床号：");
		scanf_s("%d", &bed);
		if (bed >= 1 && bed <= 9)
			break;
		else
			printf("！！输入有错请重新输入！！");
	}
	string patient_id = to_string(date_in).append(wardst).append(to_string(bed));
	string date_out_string;
	if (date_out == 11111111)
		date_out_string = "住院中";
	else
		date_out_string = to_string(date_out);
	Patient pt{ atoll(patient_id.c_str()), name, age, to_string(date_in), date_out_string };
	vector<Patient> preveiw;//预览
	preveiw.push_back(pt);
	ptvector(preveiw);
	Patient pt2{ atoll(patient_id.c_str()), name, age, to_string(date_in), to_string(date_out) };
	return pt2;
}

Ward returnwd() {
	int ward_id;
	int ward_bed = 10;
	string ward_doc;
	char docst[20];
	bool manage_ward(), app();
	while (true)
	{
		cout << "\n输入病房号：";
		scanf_s("%d", &ward_id);
		if (ward_id >= 1 && ward_id <= 999)
			break;
		else
			printf("！！输入有错请重新输入！！");
	}
	cout << "\n负责医生姓名：";
	scanf("%s", docst);
	ward_doc = docst;
	Ward wd{ ward_id, ward_bed, ward_doc };
	vector<Ward> preveiw;
	preveiw.push_back(wd);
	ptvector(preveiw);
	return wd;
}

/*
*结构体格式
*
* Patient  |   Patient_id  | Patient_name | Patient_age | Patient_time_in | Patient_time_out
*  cpp     | long long int |    string    |     int     |     string      |    string
*  mysql   |   bigint      |  varchar(255)|     int     |      date       |    date
*
*   Ward   |   Ward_id  |   Ward_bed   |   Ward_doc  |
*   c++    |    int     |     int      |    string   |
*   mysql  |    int     |     int      | varchar(255)|
*
* 查询参数为“”或0 输出全部结果
*/
//添加病人/病房
void add(string a) {
	if (a == "病人")
	{
		Patient returnpt();
		char yes;
		printf("\n---添加病人---日期格式：yyyymmdd---住院中：出院日期填0---病房号：1-99---病床号：1-9---");
		Patient pt = returnpt();
		printf("\n确认病人信息 (Y/N):");
		while (getchar() != '\n') continue;
		scanf("%c", &yes);
		if (yes == 'y' || yes == 'Y' || yes == '\n')
		{
			insert(pt);
			printf("插入成功！3秒后返回主页面");
			Sleep(3000);
		}
		else if (yes == 'n' || yes == 'N')
		{
			bool manage_patient();
			manage_patient();
		}

	}
	else if (a == "病房")
	{
		char yes;
		printf("\n---添加病房---病房号：1-99---床位默认都为10无法更改");
		Ward wd = returnwd();
		printf("\n确认病房信息 (Y/N):");
		while (getchar() != '\n') continue;
		scanf("%c", &yes);
		if (yes == 'y' || yes == 'Y' || yes == '\n')
		{
			insert(wd);
			printf("插入成功！3秒后返回主页面");
			Sleep(3000);
		}
		else if (yes == 'n' || yes == 'N')
		{
			bool manage_ward();
			manage_ward();
		}

	}
}

void del(string a) {
	if (a == "病人")
	{
		printf("\n---删除病人---住院号格式：入院日期(8位)  +  病房号(3位 空位补零)  +  病床号(1位)---");
		long long int id;
		while (true)
		{
			cout << endl << "输入病人住院号：";
			scanf_s("%lld", &id);
			if (to_string(id).length() == 12)
			{
				select_patient(id);
				printf("确定删除该病人(Y/N):");
				char a;
				getchar();
				scanf("%c", &a);
				if (a == 'Y' || a == 'y' || a == '\n')
				{
					delete_patient(id);
					cout << "删除成功！ 3秒返回主界面";
					Sleep(3000);
					break;
				}
				else if (a == 'N' || a == 'n')
				{
					bool manage_patient();
					manage_patient();
				}
			}
			else
			{
				printf("！！输入有误 请输入正确的12位住院号！！\n");
			}
		}
	}
	else if (a == "病房")
	{
		printf("\n---删除病房---");
		int wardid;
		while (true)
		{
			cout << endl << "输入病房号：";
			scanf_s("%d", &wardid);
			if (wardid >= 1 && wardid <= 999)
			{
				select_ward(wardid);
				printf("确定删除该病房(Y/N):");
				char a;
				getchar();
				scanf("%c", &a);
				if (a == 'Y' || a == 'y' || a == '\n')
				{
					delete_ward(wardid);
					cout << "删除成功！ 3秒返回主界面";
					Sleep(3000);
					break;
				}
				else if (a == 'N' || a == 'n')
				{
					bool manage_ward();
					manage_ward();
				}
			}
		}
	}
}

void update_all(string s) {
	if (s == "病人")
	{
		printf("\n---修改病人---住院号格式：入院日期(8位)  +  病房号(3位 空位补零)  +  病床号(1位)---");
		long long int id;
		char a;
		Patient returnpt();
		while (true)
		{
			cout << endl << "输入病人住院号：";
			scanf_s("%lld", &id);
			if (to_string(id).length() == 12)
			{
				cout << "当前病人：" << endl;
				select_patient(id);
			}
			else
				cout << "！！输入有误请重新输入！！";
			Patient pt = returnpt();
			while (getchar() != '\n') continue;
			cout << "确认修改（Y/N）:";
			scanf("%c", &a);
			if (a == 'Y' || a == 'y' || a == '\n')
			{
				bool update(Patient);
				update(pt);
				cout << "修改成功！ 3秒返回主界面";
				Sleep(3000);
				break;
			}
			else if (a == 'N' || a == 'n')
			{
				bool manage_patient();
				manage_patient();
			}
		}
	}
	else if (s == "病房")
	{
		printf("\n---修改病房---病房号：1-99---");
		int wardid;
		char a;
		Patient returnpt();
		while (true)
		{
			cout << endl << "输入病房号：";
			scanf_s("%d", &wardid);
			if (wardid >= 1 && wardid <= 999)
			{
				cout << "当前病房：" << endl;
				select_ward(wardid);
			}
			else
				cout << "！！输入有误请重新输入！！";
			Ward wd = returnwd();
			while (getchar() != '\n') continue;
			cout << "确认修改（Y/N）:";
			scanf("%c", &a);
			if (a == 'Y' || a == 'y' || a == '\n')
			{
				bool update(Ward);
				update(wd);
				cout << "修改成功！ 3秒返回主界面";
				Sleep(3000);
				break;
			}
			else if (a == 'N' || a == 'n')
			{
				bool manage_ward();
				manage_ward();
			}
		}
	}
}

bool manage_patient() {
	system("cls");
	cout << "-----------------管理病人-----------------" << endl;
	cout << "\t0.返回" << endl;
	cout << "\t1.添加" << endl;
	cout << "\t2.删除" << endl;
	cout << "\t3.修改" << endl;
	cout << "------------------------------------------" << endl;
	int set;
	bool app();
	printf("请键入操作：");
	scanf("%d", &set);
	while (getchar() != '\n') continue;//清空输入缓冲区
	switch (set)
	{
	case 0:  break;
	case 1:  add("病人"); break;
	case 2:  del("病人"); break;
	case 3:  update_all("病人"); break;
	default:
		break;
	}
	return true;
}

bool manage_ward() {
	system("cls");
	cout << "-----------------管理病房-----------------" << endl;
	cout << "\t0.返回" << endl;
	cout << "\t1.添加" << endl;
	cout << "\t2.删除" << endl;
	cout << "\t3.修改" << endl;
	cout << "------------------------------------------" << endl;
	int set;
	bool app();
	printf("请键入操作：");
	scanf("%d", &set);
	while (getchar() != '\n') continue;//清空输入缓冲区
	switch (set)
	{
	case 0:  break;
	case 1:  add("病房"); break;
	case 2:  del("病房"); break;
	case 3:  update_all("病房"); break;
	default:
		break;
	}
	return true;
}

void find_patient() {
	system("cls");
	cout << "\n---查找病人---";
	cout << "\n输入病人姓名/住院号：";
	char st[20];
	string str;
	scanf("%s", st);
	while (getchar() != '\n') continue;//清空输入缓冲区
	str = st;
	if (str.length() == 12)
	{
		select_patient(atoll(str.c_str()));
	}
	else {
		select_patient(str);
	}
	system("pause");
}

void find_ward() {
	system("cls");
	cout << "\n---查找病房---";
	cout << "\n输入病房号/负责医生：";
	char st[20];
	string str;
	scanf("%s", st);
	while (getchar() != '\n') continue;//清空输入缓冲区
	str = st;
	if (atoi(str.c_str()) >= 1 && atoi(str.c_str()) <= 999)
	{
		select_ward(atoi(str.c_str()));
	}
	else {
		select_ward(str);
	}
	system("pause");
}

void list_patient() {
	system("cls");
	void select_patient(string);
	select_patient("");
	system("pause");
}

void list_ward() {
	system("cls");
	void select_ward(string);
	select_ward("");
	system("pause");
}

void bed_access() {
	system("cls");
	cout << "----------以下房间有空床-(床数)----------"<< endl;
	vector<int> ward_num = ward_access();
	vector<long long int> pt_id_ = pt_in();
	vector<int> pt_ward_ = pt_ward(pt_id_);
	for (int i = 0; i < ward_num.size(); i++)
	{
		int count = 0;
		for (int j = 0; j < pt_ward_.size(); j++)
		{
			if (pt_ward_[j] == ward_num[i])
			{
				count++;
			}
		}
		if (count <= 10)
		{
			printf("%03d(%02d)  ", ward_num[i], 10 - count);
			if ((i+1) % 10 == 0)
			{
				cout << endl;
			}
		}
		else {
			system("cls");
			printf("第%03d号病房信息有误！",ward_num[i]);
				break;
		}
	}
	cout << endl;
	system("pause");
}

void pt_doc() {
	system("cls");
	cout << "----------查找病人负责医生----------\n";
	long long int a;
	string s;
	int ward_id;
	cout << "请输入住院号：";
	scanf("%lld", &a);
	while (getchar() != '\n') continue;//清空输入缓冲区
	s = to_string(a);
	if (s.length() == 12)
	{
		vector<Patient> pt = paitent_vec(a);
		ward_id = a % 10000%10000 / 10;
		vector<Ward> wd = pt_doc_(ward_id);
		if (wd.size() == 0)
			printf("未录入%03d病房信息，返回主界面...\n", ward_id);
		else
			cout << "病人姓名：" << pt[0].patient_name << "\t入院日期：" << pt[0].patient_time_in << "\t病房号：" << ward_id << "\t负责医生：" << wd[0].ward_doc << endl;
		
	}
	else {
		cout << "住院号有误，返回主界面..." << endl;
	}
	
	system("pause");
}

//重载app
bool app()
{
	bool i = true;
	bool app(i);
	return 1;
}

bool app(bool& cls) {
	if (cls) {
		cls = false;

	}
	else
		system("cls");
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	string week[] = { "日","一","二","三","四","五","六" };
	cout << "----------欢迎访问住院病人管理系统-----------\n" << endl;
	printf("%4d/%02d/%02d\t%02d : %02d : %02d.%03d\t星期%s\n\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, week[sys.wDayOfWeek].c_str());
	cout << "\t0.退出系统" << endl;
	cout << "\t1.管理病人" << endl;
	cout << "\t2.管理病房" << endl;
	cout << "\t3.查找病人" << endl;
	cout << "\t4.查找病房" << endl;
	cout << "\t5.查询空位病房" << endl;
	cout << "\t6.查询病人负责医生" << endl << endl;
	cout << "\ta.显示所有病人" << endl;
	cout << "\tb.显示所有病房" << endl;
	cout << "\n---------------------------------------------" << endl;
	printf("请键入操作：");
	char set;
	scanf("%c", &set);
	while (getchar() != '\n') continue;//清空输入缓冲区
	switch (set)
	{
	case '0': cout << endl << "感谢使用，再见" << endl; Sleep(3000); system("exit"); exit(0); break;
	case '1': manage_patient(); break;
	case '2': manage_ward(); break;
	case '3': find_patient(); break;
	case '4': find_ward(); break;
	case '5': bed_access(); break;
	case '6': pt_doc(); break;
	case 'a': list_patient(); break;
	case 'b': list_ward(); break;
	default:
		break;
	}
	return 0;
}


int main() {
	system("color b0");
	SetConsoleTitle(L"病人管理系统");
	PatientManager::GetInstance()->database_access();//检测数据库是否有效
	system("ver");
	cout << endl;
	bool cls = true;
	while (true) {
		app(cls); 
	}

}
