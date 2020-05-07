#pragma once

#include <string>
#include <unordered_map>
#include <variant>

#include "Exception.h"
#include "database.h"

typedef std::variant<const int*, const std::string*> fieldType;

class dbModel
{
public:
	dbModel(const std::string &table) : tableName(table) {}
	virtual ~dbModel() {};
	virtual std::unordered_map<std::string, fieldType> toMap() const = 0;
	std::string GetTableName() const { return tableName; }
	void Save() const;
private:
	std::string tableName;
};

