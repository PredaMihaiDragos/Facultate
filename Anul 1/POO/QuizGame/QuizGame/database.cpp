#include "database.h"

database::database()
{
	con = std::make_unique<SQLite::Database>("database.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
}

database::~database()
{
}

void database::SaveModel(std::shared_ptr<dbModel> model)
{
	std::string table = model->GetTableName();
	std::unordered_map<std::string, fieldType> rows = model->toMap();
	std::string query = "INSERT INTO " + table + "(";
	for (const auto& row : rows)
		query = query + row.first + ",";
	query.pop_back(); //delete ,
	query += ") VALUES(";
	for (const auto &row : rows)
	{
		if (auto field = std::get_if<int*>(&row.second))
			query += std::to_string(**field) + ",";
		else if (auto field = std::get_if<std::string*>(&row.second))
			query += "'" + **field + "'" + ",";
	}
	query.pop_back(); //delete ,
	query += ")";
	try
	{
		con->exec(query);
	}
	catch (std::exception& e)
	{
		error << "exception: " << e.what() << std::endl;
	}
}
