#include "dfa.h"

dfa::dfa(const nfa& from)
{	
	SetStareInit(1 << from.GetStareInit());
	auto fromVecini = from.GetVecini();
	std::queue<int> q;
	std::unordered_set<int> viz;
	q.push(stare_init);
	viz.insert(stare_init);
	while (q.empty() == false)
	{
		int stare = q.front();
		q.pop();
		std::unordered_map<char, int> edges;
		for (const auto& p : fromVecini)
			if (stare & (1 << p.first))
			{
				auto vec = from.GetVecini(p.first);
					for (auto vecin : vec)
						edges[vecin.first] |= (1 << vecin.second);
			}
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
	for (const auto& p : vecini)
	{
		auto f = from.GetFinals();
		for (int stare: f)
			if (p.first & (1 << stare))
				AddStareFinala(p.first);
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
	std::unordered_set<int> vizInitial;
	DFS(stare_init, vizInitial);

	vecini = GetTranspose(vecini);
	std::unordered_set<int> vizFinal;
	for (auto stare:finals)
		DFS(stare, vizFinal);
	vecini = GetTranspose(vecini);

	std::unordered_map<int, int> classOf, newClassOf;
	std::vector<std::vector<int> > classes(2), newClasses;

	auto vizTotal = vizInitial;
	vizTotal.insert(vizFinal.begin(), vizFinal.end());
	for (int p:vizTotal)
	{
		classes[IsFinal(p)].push_back(p);
		classOf[p] = IsFinal(p);
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
	auto old_finals = finals;

	vecini = veciniMatrix();
	finals = std::unordered_set<int>();
	SetStareInit(classOf[stare_init]);

	for (int i = 0; i < classes.size(); ++i)
		for (auto stare : classes[i])
		{
			if (old_finals.find(stare) != old_finals.end())
				AddStareFinala(i);
			for (const auto& charEdges : old_vecini[stare])
				for (int vecin : charEdges.second)
					if (vecini[i][charEdges.first].size() == 0)
						AddEdge(i, classOf[vecin], charEdges.first);
		}
}

void dfa::DFS(int current, std::unordered_set<int>& viz) const
{
	if (viz.find(current) != viz.end())
		return;
	viz.insert(current);
	auto v = GetVecini(current);
	for (auto vecin : v)
		DFS(vecin.second, viz);
}