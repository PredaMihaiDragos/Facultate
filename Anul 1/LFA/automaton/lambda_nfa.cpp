#include "lambda_nfa.h"

lambda_nfa::lambda_nfa(int nr_stari)
	: automaton(nr_stari)
{

}

void lambda_nfa::AddEdge(int from, int to, char val)
{
	vecini[from][val].push_back(to);
}