#include "dfa.h"

dfa::dfa(int nr_stari)
	: automaton(nr_stari)
{

}

dfa::dfa(const nfa& from)
	: automaton(1 << from.GetNrStari())
{
	int from_stari = from.GetNrStari();
	const veciniMatrix from_vecini = from.GetVecini();
	assert(from_stari <= 30);
	SetStareInit(1 << from.GetStareInit());
	std::queue<int> q;
	std::unordered_set<int> viz;
	q.push(stare_init);
	viz.insert(stare_init);
	while (q.empty() == false)
	{
		int stare = q.front();
		q.pop();
		std::unordered_map<char, int> edges;
		for (int from_stare = 0; from_stare < from_stari; ++from_stare)
			if (stare & (1 << from_stare))
				for (const auto& charEdges : from_vecini[from_stare])
					for (int vecin : charEdges.second)
						edges[charEdges.first] |= (1 << vecin);
		for (const auto& edge : edges)
		{
			AddEdge(stare, edge.second, edge.first);
			if (viz.find(edge.second) == viz.end())
			{
				q.push(edge.second);
				viz.insert(edge.second);
			}
		}
	}
	for (int stare = 0; stare < nr_stari; ++stare)
	{
		for (int from_stare = 0; from_stare < from_stari; ++from_stare)
			if (from.IsFinal(from_stare) && (stare & (1 << from_stare)))
				AddStareFinala(stare);
	}
}

void dfa::AddEdge(int from, int to, char val)
{
	if(vecini[from][val].size() == 0)
		vecini[from][val].insert(to);
}