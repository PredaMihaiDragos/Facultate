#include "nfa.h"

nfa::nfa(int nr_stari)
	: automaton(nr_stari)
{

}

nfa::nfa(const lambda_nfa& from)
	: automaton(from.GetNrStari())
{

}

void nfa::AddEdge(int from, int to, char val)
{
	assert(val != LAMBDA);
	vecini[from][val].push_back(to);
}