#include "dbModelCreator.h"

const std::shared_ptr<SQLite::Database> dbModelCreator::GetDatabaseCon() const
{
	return database::GetInstance().con;
}