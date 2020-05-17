#pragma once

#include <fstream>
#include "Singleton.h"
#include "Exception.h"
#include "SQLException.h"
#include <variant>

typedef std::variant<SQLException, Exception, std::string, const char *> logType;

class Logger :
	public Singleton<Logger>
{
public:
	virtual ~Logger() {};
	void operator+=(logType toLog);
private:
	Logger() {};
	friend class Singleton<Logger>;
};

inline void Logger::operator+=(logType toLog)
{
	if (auto except = std::get_if<SQLException>(&toLog))
	{
		std::ofstream out("sqlErrors.log");
		out << "Error: " << except->what() << " in file " << except->GetFile() << "\n";
		out.close();
	}
	else if (auto except = std::get_if<Exception>(&toLog))
	{
		std::ofstream out("errors.log");
		out << "Error: " << except->what() << " in file " << except->GetFile() << "\n";
		out.close();
	}
	else if(auto message = std::get_if<std::string>(&toLog))
	{
		std::ofstream out("log.log");
		out << *message << "\n";
		out.close();
	}
	else if (auto message = std::get_if<const char*>(&toLog))
	{
		std::ofstream out("log.log");
		out << *message << "\n";
		out.close();
	}
}
