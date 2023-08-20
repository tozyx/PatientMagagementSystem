#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
using namespace std;

typedef struct Patient {
	long long int patient_id;
	string patient_name;
	int patient_age;
	string patient_time_in;//写入数据库格式 YYYY-MM-DD 或YYYYMMDD
	string patient_time_out;
} Patient;
typedef struct Ward {
	int ward_id;
	int ward_bed;
	string ward_doc;
}Ward;


class PatientManager {
	PatientManager();
	~PatientManager();

public:
	static PatientManager* GetInstance(){
		static PatientManager PatientManager;
		return &PatientManager;
	}
public:
	bool database_access();
	bool insert_patient(Patient& t);
	bool update_patient(Patient& t);
	bool delete_patient(long long int patient_id);
	vector<Patient> get_patient(string condition = "");
	vector<Patient> get_patient(long long int condition);
	vector<long long int> pt_num();

	bool insert_ward(Ward& t);
	bool update_ward(Ward& t);
	bool delete_ward(int ward_id);
	vector<Ward> get_ward(string condition = "");
	vector<Ward> get_ward(int condition = 0);
	vector<int> ward_id();
	
private:
	MYSQL* con;
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* pw = "123456";
	const char* database_name = "patient_manager";
	const int port = 3306;

};
