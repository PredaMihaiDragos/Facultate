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
			if(vecini[stare][edge.first].size() == 0)
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
	if (val == LAMBDA)
		throw std::runtime_error("LAMBDA character not allowed in DFA!");
	if(vecini[from][val].size() != 0)
		throw std::runtime_error("Duplicate edge not allowed in DFA!");
	vecini[from][val].insert(to);
}

void dfa::Minimize()
{
	std::vector<bool> vizInitial(nr_stari);
	DFS(stare_init, vizInitial);

	vecini = GetTranspose(vecini);
	std::vector<bool> vizFinal(nr_stari);
	for (int i = 0; i < nr_stari; ++i)
		if (is_final[i])
			DFS(i, vizFinal);
	vecini = GetTranspose(vecini);

	std::vector<int> classOf(nr_stari), newClassOf(nr_stari);
	std::vector<std::vector<int> > classes(2), newClasses;
	for (int i = 0; i < nr_stari; ++i)
		if (vizInitial[i] || vizFinal[i])
		{
			classes[is_final[i]].push_back(i);
			classOf[i] = is_final[i];
		}
	if (classes[1].empty())
		classes.pop_back();
	if (classes[0].empty())
		classes.erase(classes.begin());
	while (true)
	{
		for (const auto& cls : classes)
		{
			newClasses.push_back({ cls[0] });
			newClassOf[cls[0]] = newClasses.size() - 1;
			int firstClass = newClasses.size() - 1;
			for (int i = 1; i < cls.size(); ++i)
			{
				int elem = cls[i];
				bool gasitClasa = false;
				for (int j = firstClass; j < newClasses.size(); ++j)
				{
					//incercam sa punem elem in clasa j
					int classElem = newClasses[j][0];
					bool ok = true;
					for (const auto& charEdges : vecini[elem])
					{
						char c = charEdges.first;
						if (vecini[classElem].find(c) == vecini[classElem].end())
						{
							ok = false;
							break;
						}

						int vecinElem = *vecini[elem][charEdges.first].begin();
						int vecinClass = *vecini[classElem][charEdges.first].begin();
						if (classOf[vecinElem] != classOf[vecinClass])
						{
							ok = false;
							break;
						}
					}
					if (ok)
					{
						newClasses[j].push_back(elem);
						newClassOf[elem] = j;
						gasitClasa = true;
						break;
					}
				}
				if (gasitClasa == false)
				{
					newClasses.push_back({ elem });
					newClassOf[elem] = newClasses.size() - 1;
				}
			}
		}
		if (classes.size() == newClasses.size())
			break;
		classes = newClasses;
		classOf = newClassOf;
		newClasses.clear();
	}

	auto old_vecini = vecini;
	auto old_is_final = is_final;

	nr_stari = classes.size();
	vecini = veciniMatrix(nr_stari);
	is_final = std::vector<bool>(nr_stari);
	SetStareInit(classOf[stare_init]);

	for (int i = 0; i < classes.size(); ++i)
		for (auto stare : classes[i])
		{
			if (old_is_final[stare])
				AddStareFinala(i);
			for (const auto& charEdges : old_vecini[stare])
				for (int vecin : charEdges.second)
					if (vecini[i][charEdges.first].size() == 0)
						AddEdge(i, classOf[vecin], charEdges.first);
		}
}

void dfa::DFS(int current, std::vector<bool>& viz) const
{
	if (viz[current])
		return;
	viz[current] = true;
	for (const auto& charEdges : vecini[current])
		for (int vecin : charEdges.second)
			DFS(vecin, viz);
}