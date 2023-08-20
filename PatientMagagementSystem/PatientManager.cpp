#define  _CRT_SECURE_NO_WARNINGS
#include "PatientManager.h"

PatientManager::PatientManager()
{
	con = mysql_init(NULL);
	//设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");

	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		fprintf(stderr, "Fail to connect databasse:Error:%s\n", mysql_error(con));
		exit(1);
	}
}

PatientManager::~PatientManager()
{
	mysql_close(con);
}

//数据库连接成功
bool PatientManager::database_access() 
{
	con = mysql_init(NULL);
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0))
	{
		fprintf(stderr, "已连接到数据库:%s...", database_name);
		return true;
	}
	else {
		fprintf(stderr, "Fail to connect databasse:Error:%s\n", mysql_error(con));
		exit(1);
	}
}

//插入病人
bool PatientManager::insert_patient(Patient& pt)
{
	char sql[1024];
	sprintf(sql, "insert into patient(patient_id,patient_name,patient_age,patient_time_in,patient_time_out) values (%lld,'%s',%d,'%s','%s')",
		pt.patient_id, pt.patient_name.c_str(), pt.patient_age, pt.patient_time_in.c_str(), pt.patient_time_out.c_str());
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to insert data(patient):Error:%s\n", mysql_error(con));
		return false;
	}
	return true;
}
//修改病人
bool PatientManager::update_patient(Patient& pt)
{
	char sql[1024];
	sprintf(sql, "Update patient set patient_name='%s',patient_age=%d,patient_time_in='%s',patient_time_out='%s'"
		"where patient_id = %lld",
		pt.patient_name.c_str(), pt.patient_age, pt.patient_time_in.c_str(), pt.patient_time_out.c_str(), pt.patient_id);
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to update data(patient):Error:%s\n", mysql_error(con));
		return false;
	}
	return true;
}
//删除病人
bool PatientManager::delete_patient(long long int patient_id) 
{
	char sql[1024];
	sprintf(sql, "DELETE FROM patient Where patient_id =%lld", patient_id);
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to delete data(patient):Error:%s\n", mysql_error(con));
		return false;
	}
	return true;
}
//查找病人
vector<Patient> PatientManager::get_patient(string condition)
{
	vector<Patient> ptList;

	char sql[1024];
	if (!condition.compare(""))//compare空为0
	{
		sprintf(sql, "SELECT * FROM patient");
	}
	else {
		sprintf(sql, "SELECT * FROM patient where patient_name like '%%%s%%'", condition.c_str());
	}

	//sprintf(sql, "SELECT * FROM patient %s", condition.c_str());
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to selete data(patient):Error:%s\n", mysql_error(con));
		return {};
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		Patient pt;
		pt.patient_id = atoll(row[0]);
		pt.patient_name = row[1];
		pt.patient_age = atoi(row[2]);
		pt.patient_time_in = row[3];
		pt.patient_time_out = row[4];

		ptList.push_back(pt);
	}
	return ptList;
}
vector<Patient> PatientManager::get_patient(long long int condition)
{
	vector<Patient> ptList;

	char sql[1024];
	sprintf(sql, "SELECT * FROM patient where patient_id like '%lld'", condition);
	//sprintf(sql, "SELECT * FROM patient %s", condition.c_str());
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to selete data(patient):Error:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		Patient pt;
		pt.patient_id = atoll(row[0]);
		pt.patient_name = row[1];
		pt.patient_age = atoi(row[2]);
		pt.patient_time_in = row[3];
		pt.patient_time_out = row[4];

		ptList.push_back(pt);
	}
	return ptList;
}
//插入病房
bool PatientManager::insert_ward(Ward& wd)
{
	char sql[1024];
	sprintf(sql, "insert into ward(ward_id,ward_bed,ward_doc) values (%d,%d,'%s')",
		wd.ward_id, wd.ward_bed, wd.ward_doc.c_str());
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to insert data(ward):Error:%s\n", mysql_error(con));
		return false;
	}
	return true;
}
//修改病房
bool PatientManager::update_ward(Ward& wd)
{
	char sql[1024];
	sprintf(sql, "Update ward set ward_bed=%d,ward_doc='%s'"
		"where ward_id = %d",
		wd.ward_bed, wd.ward_doc.c_str(), wd.ward_id);
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to update data(ward):Error:%s\n", mysql_error(con));
		return false;
	}
	return true;
}
//删除病房
bool PatientManager::delete_ward(int ward_id)
{
	char sql[1024];
	sprintf(sql, "DELETE FROM ward Where ward_id =%d", ward_id);
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to delete data(ward):Error:%s\n", mysql_error(con));
		return false;
	}
	return true;
}
//查找病房
vector<Ward> PatientManager::get_ward(int condition)
{
	vector<Ward> WdList;

	char sql[1024];
	if (condition == 0)
	{
		sprintf(sql, "SELECT * FROM ward");
	}
	else {
		sprintf(sql, "SELECT * FROM ward where ward_id = %d", condition);
	}
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to selete data(ward):Error:%s\n", mysql_error(con));
		return {};
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		Ward wd;
		wd.ward_id = atoi(row[0]);
		wd.ward_bed = atoi(row[1]);
		wd.ward_doc = row[2];

		WdList.push_back(wd);
	}
	return WdList;
}

vector<Ward> PatientManager::get_ward(string condition)
{
	vector<Ward> WdList;

	char sql[1024];
	if (!condition.compare(""))
	{
		sprintf(sql, "SELECT * FROM ward");
	}
	else {
		sprintf(sql, "SELECT * FROM ward where ward_doc like '%%%s%%'", condition.c_str());

	}
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to selete data(ward):Error:%s\n", mysql_error(con));
		return {};
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		Ward wd;
		wd.ward_id = atoi(row[0]);
		wd.ward_bed = atoi(row[1]);
		wd.ward_doc = row[2];

		WdList.push_back(wd);
	}
	return WdList;
}

vector<int> PatientManager::ward_id() {
	vector<int> wdid;
	char sql[1024];
	sprintf(sql, "SELECT * FROM ward");
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to selete data(ward ward_id()):Error:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		wdid.push_back(atoi(row[0]));
	}
	return wdid;
}
//住院病人住院号
vector<long long int> PatientManager::pt_num() {
	vector<long long int> ptid;
	char sql[1024];
	sprintf(sql, "SELECT * FROM patient where patient_time_out like '1111-11-11'");
	if (mysql_query(con, sql))
	{
		fprintf(stderr, "Fail to selete data(patient pt_num()):Error:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		ptid.push_back(atoll(row[0]));
	}
	return ptid;
}