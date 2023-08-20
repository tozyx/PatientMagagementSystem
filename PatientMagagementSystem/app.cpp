#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <String>
#include "PatientManager.h"
#include <synchapi.h>
#include <consoleapi2.h>
#include <sysinfoapi.h>

/*
*��װ����
*/
//��ӡ����vector
void ptvector(vector<Patient> a) {
	int id = 18, name = 20, age = 10, time = 18;//������ռλ
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(id) << "סԺ��" << resetiosflags(ios::left) // ����֮�����
		<< setiosflags(ios::right) << setw(name) << "����" << setw(name) << "����" << setw(time) << "��Ժʱ��"
		<< setw(time) << "��Ժʱ��"
		<< resetiosflags(ios::right) << endl;
	for (auto& t : a) {
		if (!t.patient_time_out.compare("1111-11-11"))
		{
			t.patient_time_out = "סԺ��    ";
		}
		cout << setiosflags(ios::left) << setw(id) << t.patient_id << resetiosflags(ios::left) // ����֮�����
			<< setiosflags(ios::right) << setw(name) << t.patient_name << setw(name) << t.patient_age << setw(time)
			<< t.patient_time_in << setw(time) << t.patient_time_out
			<< resetiosflags(ios::right) << endl;
	}
	cout << "------------------------------------------------------------------------------------------------\n" << endl;
}
//��ӡ����vector
void ptvector(vector<Ward> a) {
	int id = 8, bed = 8, doc = 10;//������ռλ
	cout << "------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(id) << "������" << resetiosflags(ios::left) // ����֮�����
		<< setiosflags(ios::right) << setw(bed) << "�ܴ�λ" << setw(doc) << "����ҽ��"
		<< resetiosflags(ios::right) << endl;
	for (auto& t : a) {
		cout << setiosflags(ios::left) << setw(id) << t.ward_id << resetiosflags(ios::left) // ����֮�����
			<< setiosflags(ios::right) << setw(bed) << t.ward_bed << setw(doc) << t.ward_doc
			<< resetiosflags(ios::right) << endl;
	}
	cout << "------------------------------------\n" << endl;
}
//���벡��/����
bool insert(Patient pt) {
	return	PatientManager::GetInstance()->insert_patient(pt);
}
bool insert(Ward pt) {//����
	return	PatientManager::GetInstance()->insert_ward(pt);
}
//�޸Ĳ���/����
bool update(Patient pt) {
	return	PatientManager::GetInstance()->update_patient(pt);
}
bool update(Ward pt) {
	return	PatientManager::GetInstance()->update_ward(pt);
}
//ɾ������
bool delete_patient(long long int id) {
	return PatientManager::GetInstance()->delete_patient(id);
}
//ɾ������
bool delete_ward(int id) {
	return PatientManager::GetInstance()->delete_ward(id);
}
//���Ҳ���
void select_patient(string st) {
	ptvector(PatientManager::GetInstance()->get_patient(st));
}
void select_patient(long long int i) {
	ptvector(PatientManager::GetInstance()->get_patient(i));
}
vector<Patient> paitent_vec(long long int i) {
	return PatientManager::GetInstance()->get_patient(i);
}
//���Ҳ���
void select_ward(int st) {
	ptvector(PatientManager::GetInstance()->get_ward(st));
}
void select_ward(string st) {
	ptvector(PatientManager::GetInstance()->get_ward(st));
}
vector<Ward> pt_doc_(int i) {
	return (PatientManager::GetInstance()->get_ward(i));
}
//�ж��Ƿ��в�����Ϣ
vector<int> ward_access() {
	return PatientManager::GetInstance()->ward_id();
}
//סԺ����סԺ��
vector<long long int> pt_in() {
	return PatientManager::GetInstance()->pt_num();
}

//סԺ��ת��Ӧ������
vector<int> pt_ward(vector<long long int> pt_in) {
	vector<int> pt_ward;
	for (int i = 0; i < pt_in.size(); i++)
	{
		if (to_string(pt_in[i]).length() == 12)
			pt_ward.push_back(pt_in[i] % 10000 / 10);
	}
	return pt_ward;
}


//�ж������Ƿ�Ϸ�
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

//����pt
Patient returnpt() {
	int date_in, date_out, age, ward, bed;
	char stname[20];
	string name, wardst;
	bool manage_patient(), app(), Islegal();//����
	while (true)
	{
		printf("\n��Ժ���ڣ�");
		scanf_s("%d", &date_in);
		printf("\n��Ժ���ڣ�");
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
			printf("�������ڷǷ����������룡��");
		}
	}
	printf("\n����������");
	scanf("%s", stname);
	name = stname;
	while (true)
	{
		printf("\n�������䣺");
		scanf_s("%d", &age);
		if (age >= 0 && age <= 150)
			break;
		else
			printf("���������д����������룡��");
	}
	while (true)
	{
		string st;
		printf("\n�����ţ�");
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
			printf("���������д����������룡��");
	}
	while (true)
	{
		printf("\n�����ţ�");
		scanf_s("%d", &bed);
		if (bed >= 1 && bed <= 9)
			break;
		else
			printf("���������д����������룡��");
	}
	string patient_id = to_string(date_in).append(wardst).append(to_string(bed));
	string date_out_string;
	if (date_out == 11111111)
		date_out_string = "סԺ��";
	else
		date_out_string = to_string(date_out);
	Patient pt{ atoll(patient_id.c_str()), name, age, to_string(date_in), date_out_string };
	vector<Patient> preveiw;//Ԥ��
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
		cout << "\n���벡���ţ�";
		scanf_s("%d", &ward_id);
		if (ward_id >= 1 && ward_id <= 999)
			break;
		else
			printf("���������д����������룡��");
	}
	cout << "\n����ҽ��������";
	scanf("%s", docst);
	ward_doc = docst;
	Ward wd{ ward_id, ward_bed, ward_doc };
	vector<Ward> preveiw;
	preveiw.push_back(wd);
	ptvector(preveiw);
	return wd;
}

/*
*�ṹ���ʽ
*
* Patient  |   Patient_id  | Patient_name | Patient_age | Patient_time_in | Patient_time_out
*  cpp     | long long int |    string    |     int     |     string      |    string
*  mysql   |   bigint      |  varchar(255)|     int     |      date       |    date
*
*   Ward   |   Ward_id  |   Ward_bed   |   Ward_doc  |
*   c++    |    int     |     int      |    string   |
*   mysql  |    int     |     int      | varchar(255)|
*
* ��ѯ����Ϊ������0 ���ȫ�����
*/
//��Ӳ���/����
void add(string a) {
	if (a == "����")
	{
		Patient returnpt();
		char yes;
		printf("\n---��Ӳ���---���ڸ�ʽ��yyyymmdd---סԺ�У���Ժ������0---�����ţ�1-99---�����ţ�1-9---");
		Patient pt = returnpt();
		printf("\nȷ�ϲ�����Ϣ (Y/N):");
		while (getchar() != '\n') continue;
		scanf("%c", &yes);
		if (yes == 'y' || yes == 'Y' || yes == '\n')
		{
			insert(pt);
			printf("����ɹ���3��󷵻���ҳ��");
			Sleep(3000);
		}
		else if (yes == 'n' || yes == 'N')
		{
			bool manage_patient();
			manage_patient();
		}

	}
	else if (a == "����")
	{
		char yes;
		printf("\n---��Ӳ���---�����ţ�1-99---��λĬ�϶�Ϊ10�޷�����");
		Ward wd = returnwd();
		printf("\nȷ�ϲ�����Ϣ (Y/N):");
		while (getchar() != '\n') continue;
		scanf("%c", &yes);
		if (yes == 'y' || yes == 'Y' || yes == '\n')
		{
			insert(wd);
			printf("����ɹ���3��󷵻���ҳ��");
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
	if (a == "����")
	{
		printf("\n---ɾ������---סԺ�Ÿ�ʽ����Ժ����(8λ)  +  ������(3λ ��λ����)  +  ������(1λ)---");
		long long int id;
		while (true)
		{
			cout << endl << "���벡��סԺ�ţ�";
			scanf_s("%lld", &id);
			if (to_string(id).length() == 12)
			{
				select_patient(id);
				printf("ȷ��ɾ���ò���(Y/N):");
				char a;
				getchar();
				scanf("%c", &a);
				if (a == 'Y' || a == 'y' || a == '\n')
				{
					delete_patient(id);
					cout << "ɾ���ɹ��� 3�뷵��������";
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
				printf("������������ ��������ȷ��12λסԺ�ţ���\n");
			}
		}
	}
	else if (a == "����")
	{
		printf("\n---ɾ������---");
		int wardid;
		while (true)
		{
			cout << endl << "���벡���ţ�";
			scanf_s("%d", &wardid);
			if (wardid >= 1 && wardid <= 999)
			{
				select_ward(wardid);
				printf("ȷ��ɾ���ò���(Y/N):");
				char a;
				getchar();
				scanf("%c", &a);
				if (a == 'Y' || a == 'y' || a == '\n')
				{
					delete_ward(wardid);
					cout << "ɾ���ɹ��� 3�뷵��������";
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
	if (s == "����")
	{
		printf("\n---�޸Ĳ���---סԺ�Ÿ�ʽ����Ժ����(8λ)  +  ������(3λ ��λ����)  +  ������(1λ)---");
		long long int id;
		char a;
		Patient returnpt();
		while (true)
		{
			cout << endl << "���벡��סԺ�ţ�";
			scanf_s("%lld", &id);
			if (to_string(id).length() == 12)
			{
				cout << "��ǰ���ˣ�" << endl;
				select_patient(id);
			}
			else
				cout << "���������������������룡��";
			Patient pt = returnpt();
			while (getchar() != '\n') continue;
			cout << "ȷ���޸ģ�Y/N��:";
			scanf("%c", &a);
			if (a == 'Y' || a == 'y' || a == '\n')
			{
				bool update(Patient);
				update(pt);
				cout << "�޸ĳɹ��� 3�뷵��������";
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
	else if (s == "����")
	{
		printf("\n---�޸Ĳ���---�����ţ�1-99---");
		int wardid;
		char a;
		Patient returnpt();
		while (true)
		{
			cout << endl << "���벡���ţ�";
			scanf_s("%d", &wardid);
			if (wardid >= 1 && wardid <= 999)
			{
				cout << "��ǰ������" << endl;
				select_ward(wardid);
			}
			else
				cout << "���������������������룡��";
			Ward wd = returnwd();
			while (getchar() != '\n') continue;
			cout << "ȷ���޸ģ�Y/N��:";
			scanf("%c", &a);
			if (a == 'Y' || a == 'y' || a == '\n')
			{
				bool update(Ward);
				update(wd);
				cout << "�޸ĳɹ��� 3�뷵��������";
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
	cout << "-----------------������-----------------" << endl;
	cout << "\t0.����" << endl;
	cout << "\t1.���" << endl;
	cout << "\t2.ɾ��" << endl;
	cout << "\t3.�޸�" << endl;
	cout << "------------------------------------------" << endl;
	int set;
	bool app();
	printf("����������");
	scanf("%d", &set);
	while (getchar() != '\n') continue;//������뻺����
	switch (set)
	{
	case 0:  break;
	case 1:  add("����"); break;
	case 2:  del("����"); break;
	case 3:  update_all("����"); break;
	default:
		break;
	}
	return true;
}

bool manage_ward() {
	system("cls");
	cout << "-----------------������-----------------" << endl;
	cout << "\t0.����" << endl;
	cout << "\t1.���" << endl;
	cout << "\t2.ɾ��" << endl;
	cout << "\t3.�޸�" << endl;
	cout << "------------------------------------------" << endl;
	int set;
	bool app();
	printf("����������");
	scanf("%d", &set);
	while (getchar() != '\n') continue;//������뻺����
	switch (set)
	{
	case 0:  break;
	case 1:  add("����"); break;
	case 2:  del("����"); break;
	case 3:  update_all("����"); break;
	default:
		break;
	}
	return true;
}

void find_patient() {
	system("cls");
	cout << "\n---���Ҳ���---";
	cout << "\n���벡������/סԺ�ţ�";
	char st[20];
	string str;
	scanf("%s", st);
	while (getchar() != '\n') continue;//������뻺����
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
	cout << "\n---���Ҳ���---";
	cout << "\n���벡����/����ҽ����";
	char st[20];
	string str;
	scanf("%s", st);
	while (getchar() != '\n') continue;//������뻺����
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
	cout << "----------���·����пմ�-(����)----------"<< endl;
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
			printf("��%03d�Ų�����Ϣ����",ward_num[i]);
				break;
		}
	}
	cout << endl;
	system("pause");
}

void pt_doc() {
	system("cls");
	cout << "----------���Ҳ��˸���ҽ��----------\n";
	long long int a;
	string s;
	int ward_id;
	cout << "������סԺ�ţ�";
	scanf("%lld", &a);
	while (getchar() != '\n') continue;//������뻺����
	s = to_string(a);
	if (s.length() == 12)
	{
		vector<Patient> pt = paitent_vec(a);
		ward_id = a % 10000%10000 / 10;
		vector<Ward> wd = pt_doc_(ward_id);
		if (wd.size() == 0)
			printf("δ¼��%03d������Ϣ������������...\n", ward_id);
		else
			cout << "����������" << pt[0].patient_name << "\t��Ժ���ڣ�" << pt[0].patient_time_in << "\t�����ţ�" << ward_id << "\t����ҽ����" << wd[0].ward_doc << endl;
		
	}
	else {
		cout << "סԺ�����󣬷���������..." << endl;
	}
	
	system("pause");
}

//����app
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
	string week[] = { "��","һ","��","��","��","��","��" };
	cout << "----------��ӭ����סԺ���˹���ϵͳ-----------\n" << endl;
	printf("%4d/%02d/%02d\t%02d : %02d : %02d.%03d\t����%s\n\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, week[sys.wDayOfWeek].c_str());
	cout << "\t0.�˳�ϵͳ" << endl;
	cout << "\t1.������" << endl;
	cout << "\t2.������" << endl;
	cout << "\t3.���Ҳ���" << endl;
	cout << "\t4.���Ҳ���" << endl;
	cout << "\t5.��ѯ��λ����" << endl;
	cout << "\t6.��ѯ���˸���ҽ��" << endl << endl;
	cout << "\ta.��ʾ���в���" << endl;
	cout << "\tb.��ʾ���в���" << endl;
	cout << "\n---------------------------------------------" << endl;
	printf("����������");
	char set;
	scanf("%c", &set);
	while (getchar() != '\n') continue;//������뻺����
	switch (set)
	{
	case '0': cout << endl << "��лʹ�ã��ټ�" << endl; Sleep(3000); system("exit"); exit(0); break;
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
	SetConsoleTitle(L"���˹���ϵͳ");
	PatientManager::GetInstance()->database_access();//������ݿ��Ƿ���Ч
	system("ver");
	cout << endl;
	bool cls = true;
	while (true) {
		app(cls); 
	}

}
