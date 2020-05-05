#pragma once

#include <memory>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

#include "error.h"


class database
{
private:
	std::shared_ptr<SQLite::Database> con;
	database();
	database(const database&) = delete;
	database& operator=(const database&) = delete;
	void Query(const std::string& query);

	friend class dbModel;
	friend class dbModelCreator;
public:
	static database* GetInstance()
	{
		static database instance;
		return &instance;
	}
};
