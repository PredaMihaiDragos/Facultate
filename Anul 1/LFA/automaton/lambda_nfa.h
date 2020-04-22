#pragma once
#include "automaton.h"
class lambda_nfa : public automaton
{
public:
	lambda_nfa(int nr_stari = 0);
	void AddEdge(int from, int to, char val);
};

