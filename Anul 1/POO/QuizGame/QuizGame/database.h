#pragma once

#include <memory>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

#include "dbModel.h"
#include "questions.h"
#include "error.h"


class database
{
private:
	std::unique_ptr<SQLite::Database> con;
	database();
	~database();
	database(const database&) = delete;
	database& operator=(const database&) = delete;
public:
	void SaveModel(std::shared_ptr<dbModel> model);
	template<typename T>
	std::vector<std::shared_ptr<T> > LoadTable();
	static database* GetInstance()
	{
		static database* instance = new database;
		return instance;
	}
};

template<typename T>
std::vector<std::shared_ptr<T> > database::LoadTable()
{
	static_assert(std::is_base_of<dbModel, T>::value);
	std::vector<std::shared_ptr<T> > ret;
	std::shared_ptr<T> row = std::make_shared<T>();
	std::string table = row->GetTableName();

	return ret;
}
