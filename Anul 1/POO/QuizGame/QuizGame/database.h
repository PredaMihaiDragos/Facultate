#pragma once

#include <memory>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

#include "error.h"
#include "Singleton.h"
#include "Logger.h"


class database :
	public Singleton<database>
{
public:
	virtual ~database() {};
private:
	std::shared_ptr<SQLite::Database> con;
	void Query(const std::string& query);
	friend database& operator<< (database& db, const std::string &query);

	friend class dbModel;
	friend class dbModelCreator;

	database();
	friend class Singleton<database>;
};
