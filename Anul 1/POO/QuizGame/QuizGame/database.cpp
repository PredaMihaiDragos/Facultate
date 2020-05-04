#include "database.h"

database* database::instance = nullptr;

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
	catch (std::exception& e)
	{
		error << "exception: " << e.what() << std::endl;
	}
}