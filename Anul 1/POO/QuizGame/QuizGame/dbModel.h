#pragma once

#include <string>
#include <unordered_map>
#include <variant>

typedef std::variant<int*, std::string*> fieldType;

class dbModel
{
private:
	std::string tableName;
public:
	dbModel(const std::string &table) : tableName(table) {}
	virtual std::unordered_map<std::string, fieldType> toMap() = 0;
	std::string GetTableName() { return tableName; }
};

