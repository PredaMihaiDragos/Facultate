#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <mysql/jdbc.h>
#include "structs.h"

using namespace sql;
using namespace sql::mysql;

class database
{
private:
	mysql::MySQL_Driver* driver;
	MySQL_Connection* con;
	sql::Statement* stmt;
	std::ofstream log;
	vector<grupa> grupaToAdd;
	vector<pacient> pacientiToAdd;
	vector<bilet> biletToAdd;
public:
	database(const SQLString &host, const SQLString &user, const SQLString &pass);
	void AddPacient(const pacient&);
	void AddBilet(const bilet&);
	void AddGrupa(const grupa&);
	void commit_pacient();
	void commit_grupa();
	void commit_bilet();
	void commit();
	~database();
};

