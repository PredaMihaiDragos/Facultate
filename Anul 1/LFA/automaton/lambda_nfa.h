#pragma once
#include "automaton.h"
#include "regGrammar.h"

#include <queue>
#include <unordered_set>

class lambda_nfa : public automaton
{
public:
	lambda_nfa(int nr_stari = 0);
	lambda_nfa(const regGrammar& from);
	void AddEdge(int from, int to, char val);
	std::unordered_set<int> GetLambdaClosure(int start) const;
};

