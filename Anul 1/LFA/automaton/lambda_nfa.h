#pragma once
#include "automaton.h"

#include <queue>
#include <unordered_set>

class lambda_nfa : public automaton
{
public:
	lambda_nfa(int nr_stari = 0);
	void AddEdge(int from, int to, char val);
	std::unordered_set<int> GetLambdaClosure(int start) const;
};

