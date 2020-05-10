#pragma once
#include "automaton.h"
#include "lambda_nfa.h"
#include <cassert>

class nfa : public automaton
{
public:
	nfa() {};
	nfa(const lambda_nfa& from);
	void AddEdge(int from, int to, char val);
private:
	
};

