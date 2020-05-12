#include "regGrammar.h"

std::istream& operator>> (std::istream& in, regGrammar& current)
{
	int n; //nr de productii
	in >> n;
	while (n--)
	{
		char from;
		std::string to;
		in >> from >> to;
		try
		{
			current.AddProd(from, to);
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << "\n";
		}
	}
	return in;
}

std::ostream& operator<< (std::ostream& out, const regGrammar& current)
{
	std::vector<std::string> outs;
	for (const auto& charProds : current.prodTerm)
		for (const auto& prod : charProds.second)
		{
			outs.push_back(std::string(1, charProds.first) + " " + prod);
		}
	for (const auto& charProds : current.prodNonTerm)
		for (const auto& prod : charProds.second)
			outs.push_back(std::string(1, charProds.first) + " " + prod.first + prod.second);
	out << outs.size() << "\n";
	for (const auto &line : outs)
		out << line << "\n";
	return out;
}

void regGrammar::AddProd(char from, std::string to)
{
	if(!isupper(from))
		throw std::runtime_error("Invalid 'from' parameter");
	if (to.size() == 1)
	{
		if (IsTerm(to[0]))
			prodTerm[from].push_back(to[0]);
		else
			throw std::runtime_error("Invalid 'to' parameter");
	}
	else if (to.size() == 2)
	{
		if (IsTerm(to[0]) && IsNonTerm(to[1]))
			prodNonTerm[from].push_back(std::make_pair(to[0], to[1]));
		else
			throw std::runtime_error("Invalid 'to' parameter");
	}
	else
		throw std::runtime_error("Invalid 'to' parameter");
}