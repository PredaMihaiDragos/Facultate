#pragma once

#include <string>
#include <exception>

class Exception :
	public std::exception
{
public:
	explicit Exception(const std::string& message, const std::string& fileName) : message(message), fileName(fileName) {}
	virtual ~Exception() noexcept {}
	virtual const char* what() const noexcept override { return message.c_str(); }
	virtual std::string GetMessage() const noexcept { return message; };
	std::string GetFile() const noexcept { return fileName; };
protected:
	std::string message;
	std::string fileName;
};

