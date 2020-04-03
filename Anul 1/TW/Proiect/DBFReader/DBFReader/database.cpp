#include "database.h"

database::database(const SQLString& host, const SQLString& user, const SQLString& pass)
{
	driver = get_mysql_driver_instance();
	con = dynamic_cast<MySQL_Connection *>(driver->connect(host, user, pass));
	log = std::ofstream("dblog.txt");
	if (con->isValid() == false)
		std::cout << "MYSQL CONNECTION INVALID\n";
	else
	{
		stmt = con->createStatement();
		stmt->execute("USE " "test");
	}
}

database::~database()
{
	log.close();
	delete con;
	delete stmt;
}

void database::AddPacient(const pacient& p)
{
	pacientiToAdd.push_back(p);
}

void database::AddBilet(const bilet& b)
{
	biletToAdd.push_back(b);
}

void database::AddGrupa(const grupa& g)
{
	grupaToAdd.push_back(g);
}

void database::commit_pacient()
{
	const int chunkSize = 2000;
	const SQLString baseQuery = "REPLACE INTO pacient(CNP, Name) VALUES ";
	SQLString query = baseQuery;
	if (con->isValid() == false)
	{
		std::cout << "MYSQL CONNECTION INVALID\n";
		return;
	}
	for (int i = 0; i < pacientiToAdd.size(); ++i)
	{
		query += "('" + con->escapeString(pacientiToAdd[i].cnp) + "', '" + con->escapeString(pacientiToAdd[i].name) + "')";
		if ((i > 0 && i % chunkSize == 0) || i == pacientiToAdd.size() - 1)
		{
			stmt->execute(query);
			log << query << "\n";
			query = baseQuery;
			continue;
		}
		if (i != pacientiToAdd.size() - 1)
			query += ",";
	}
	pacientiToAdd.clear();
}

void database::commit_grupa()
{
	const int chunkSize = 2000;
	const SQLString baseQuery = "REPLACE INTO grupa(CODG, NUME) VALUES ";
	SQLString query = baseQuery;
	if (con->isValid() == false)
	{
		std::cout << "MYSQL CONNECTION INVALID\n";
		return;
	}
	for (int i = 0; i < grupaToAdd.size(); ++i)
	{
		query += "('" + con->escapeString(grupaToAdd[i].codg) + "', '" + con->escapeString(grupaToAdd[i].name) + "')";
		if ((i > 0 && i % chunkSize == 0) || i == grupaToAdd.size() - 1)
		{
			stmt->execute(query);
			log << query << "\n";
			query = baseQuery;
			continue;
		}
		if (i != grupaToAdd.size() - 1)
			query += ",";
	}
	grupaToAdd.clear();
}

void database::commit_bilet()
{
	const int chunkSize = 500;
	const SQLString baseQuery = "REPLACE INTO bilet(CUVCODV, IDP, DB, REC, TRM, ORAP, PARD, DOC, ANALIZE) VALUES ";
	SQLString query = baseQuery;
	if (con->isValid() == false)
	{
		std::cout << "MYSQL CONNECTION INVALID\n";
		return;
	}
	for (int i = 0; i < biletToAdd.size(); ++i)
	{
		query += "('" + 
						con->escapeString(biletToAdd[i].cuv) + "-" + con->escapeString(biletToAdd[i].codv) + "', '" + 
						con->escapeString(biletToAdd[i].idp) + "', '" +
						con->escapeString(biletToAdd[i].db) + "', '" +
						con->escapeString(biletToAdd[i].rec) + "', '" +
						con->escapeString(biletToAdd[i].trm) + "', '" +
						con->escapeString(biletToAdd[i].orap) + "', '" +
						con->escapeString(biletToAdd[i].pard) + "', '" +
						con->escapeString(biletToAdd[i].doc) + "', '" +
						con->escapeString(biletToAdd[i].GetAnalizeJson()) + "')";
		if ((i > 0 && i % chunkSize == 0) || i == biletToAdd.size() - 1)
		{
			stmt->execute(query);
			log << query << "\n";
			query = baseQuery;
			continue;
		}
		if (i != biletToAdd.size() - 1)
			query += ",";
	}
	biletToAdd.clear();
}

void database::commit()
{
	commit_pacient();
	commit_grupa();
	commit_bilet();
}