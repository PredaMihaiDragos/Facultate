#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <sstream>

using namespace std;

struct pacient
{
	string cnp, name;
};

struct lbilet
{
	string aDen, aVmin, aVmax, aRez, aUma, aCoda, aCodg;
	vector<string> sDen, sVmin, sVmax, sRez, sUma;
	string GetJson() const
	{
		string ret = " {";
		ret += "\"aDen\": \"" + escape_json(aDen) + "\",";
		ret += "\"aVmin\": \"" + escape_json(aVmin) + "\",";
		ret += "\"aVmax\": \"" + escape_json(aVmax) + "\",";
		ret += "\"aRez\": \"" + escape_json(aRez) + "\",";
		ret += "\"aUma\": \"" + escape_json(aUma) + "\",";
		ret += "\"aCoda\": \"" + escape_json(aCoda) + "\",";
		ret += "\"aCodg\": \"" + escape_json(aCodg);
		ret += "\"}";
		return ret;
	}
	static std::string escape_json(const std::string& s) {
		std::ostringstream o;
		for (auto c = s.cbegin(); c != s.cend(); c++) {
			if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
				o << "\\u"
					<< std::hex << std::setw(4) << std::setfill('0') << (int)*c;
			}
			else {
				o << *c;
			}
		}
		return o.str();
	}
};

struct bilet
{
	string idp, cuv, codv, db, rec, trm, orap, pard, doc;
	map<string, lbilet> analize;
	string GetAnalizeJson() const
	{
		if (analize.empty())
			return "[]";
		string ret = "[";
		for (const auto& b : analize)
		{
			ret += b.second.GetJson();
			ret += ",";
		}
		ret.pop_back();
		ret += "]";
		return ret;
	}
};

struct grupa
{
	string codg, name;
};