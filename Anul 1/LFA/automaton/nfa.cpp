#include "nfa.h"

nfa::nfa(int nr_stari)
	: automaton(nr_stari)
{

}

nfa::nfa(const lambda_nfa& from)
	: automaton(from.GetNrStari())
{
	SetStareInit(from.GetStareInit());
	const veciniMatrix &vecini = from.GetVecini();

	for (int stare = 0; stare < nr_stari; ++stare)
	{
		std::set<std::pair<int, char> > to;
		std::unordered_set<int> lambdaClosure = from.GetLambdaClosure(stare);
		for (auto elem : lambdaClosure)
		{
			if (from.IsFinal(elem))
				AddStareFinala(stare);
			for (const auto& charEdges : vecini[elem])
				if (charEdges.first != LAMBDA)
					for (int vecin : charEdges.second)
						to.emplace(vecin, charEdges.first);
		}
		for (auto& edge : to)
			AddEdge(stare, edge.first, edge.second);
	}
}

void nfa::AddEdge(int from, int to, char val)
{
	if (val == LAMBDA)
		throw std::runtime_error("LAMBDA character not allowed in NFA!");
	vecini[from][val].insert(to);
}