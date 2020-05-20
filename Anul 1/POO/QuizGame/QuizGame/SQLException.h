#pragma once

#include "Exception.h"

class SQLException :
	public Exception
{
public:
	explicit SQLException(const std::string& message, const std::string& fileName, const std::string& query) : Exception(message, fileName), query(query) {};
	virtual ~SQLException() {};
	std::string GetMessage() const noexcept override { return "SQL Exception: " + message; };
	std::string GetQuery() const noexcept { return query; };
private:
	std::string query;
};

