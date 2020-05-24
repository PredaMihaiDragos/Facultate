#include "nfa.h"

nfa::nfa(const lambda_nfa& from)
{
	SetStareInit(from.GetStareInit());
	auto fromVecini = from.GetVecini();
	SetFinals(from.GetFinals());

	for(const auto &p:fromVecini)
	{
		std::set<std::pair<char, int> > to;
		std::unordered_set<int> lambdaClosure = from.GetLambdaClosure(p.first);
		for (auto elem : lambdaClosure)
		{
			if (from.IsFinal(elem))
				AddStareFinala(p.first);
			auto vec = from.GetVecini(elem);
			for (const auto& charEdges : vec)
				if (charEdges.first != LAMBDA)
					to.insert(charEdges);
		}
		for (auto& edge : to)
			AddEdge(p.first, edge.second, edge.first); 
	}
}

void nfa::AddEdge(int from, int to, char val)
{
	if (val == LAMBDA)
		throw std::runtime_error("LAMBDA character not allowed in NFA!");
	vecini[from][val].insert(to);
}