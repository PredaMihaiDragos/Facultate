#include "database.h"

database::database()
{
	con = std::make_shared<SQLite::Database>("database.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
}

void database::Query(const std::string& query)
{
	try
	{
		con->exec(query);
	}
	catch (Exception &e)
	{
		Logger::GetInstance() += e;
	}
}

database& operator<<(database& db, const std::string& query)
{
	db.Query(query);
	return db;
}
