#pragma once

#include <iostream>
#include <sstream>
#include <unordered_map>

class regGrammar
{
public:
	static const char LAMBDA = '$';
	static const int SIGMA = 21;
	void AddProd(char from, std::string to);
	friend std::istream& operator>> (std::istream& in, regGrammar& current);
	friend std::ostream& operator<< (std::ostream& out, const regGrammar& current);
	bool IsTerm(char x) { return islower(x) || x == LAMBDA; };
	bool IsNonTerm(char x) { return isupper(x); }

	std::unordered_map<char, std::vector<char> > GetProdTerm() const { return prodTerm; };
	std::unordered_map<char, std::vector<std::pair<char, char> > > GetProdNonTerm() const { return prodNonTerm; };
private:
	std::unordered_map<char, std::vector<char> > prodTerm;
	std::unordered_map<char, std::vector<std::pair<char, char> > > prodNonTerm;
};