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
			throw std::runtime_error("Field type not known!");
	}
	query.pop_back(); //delete ,
	query += ")";

	database::GetInstance()->Query(query);
}