#pragma once

#include <memory>
#include "dbModel.h"

class dbModelCreator
{
public:
	virtual ~dbModelCreator() {};
	virtual std::unique_ptr<dbModel> Create() const = 0;
protected:
	const std::shared_ptr<SQLite::Database> GetDatabaseCon() const;
};

