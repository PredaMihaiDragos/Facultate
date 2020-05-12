#include "dbModel.h"

void dbModel::Save() const
{
	std::unordered_map<std::string, fieldType> rows = toMap();
	std::string query = "INSERT INTO " + tableName + "(";
	for (const auto& row : rows)
		query = query + row.first + ",";
	query.pop_back(); //delete ,
	query += ") VALUES(";
	for (const auto& row : rows)
	{
		if (auto field = std::get_if<const int*>(&row.second))
			query += std::to_string(**field) + ",";
		else if (auto field = std::get_if<const std::string*>(&row.second))
			query += "'" + **field + "'" + ",";
		else
			throw Exception("Field type not known!", "dbModel.cpp");
	}
	query.pop_back(); //delete ,
	query += ")";

	database::GetInstance() << query;
}