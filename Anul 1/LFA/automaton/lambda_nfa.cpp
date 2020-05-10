#include "lambda_nfa.h"

lambda_nfa::lambda_nfa(const regGrammar& from) 
{
	const int fin = regGrammar::SIGMA - 1;
	SetStareInit('S' - 'A');
	AddStareFinala(fin);
	const auto &prodTerm = from.GetProdTerm();
	const auto &prodNonTerm = from.GetProdNonTerm();

	for (const auto& charProds : prodTerm)
		for (const auto& prod : charProds.second)
			AddEdge(charProds.first - 'A', fin, prod);
	for (const auto& charProds : prodNonTerm)
		for (const auto& prod : charProds.second)
			AddEdge(charProds.first - 'A', prod.second - 'A', prod.first);
}

void lambda_nfa::AddEdge(int from, int to, char val)
{
	vecini[from][val].insert(to);
}

std::unordered_set<int> lambda_nfa::GetLambdaClosure(int start) const
{
	std::unordered_set<int> ret;
	std::queue<int> q;
	q.push(start);
	ret.insert(start);

	while (q.empty() == false)
	{
		int current = q.front();
		q.pop();
		
		auto vec = GetVecini(current, LAMBDA);
		for (int vecin : vec)
			if (ret.find(vecin) == ret.end())
			{
				q.push(vecin);
				ret.insert(vecin);
			}
	}
	return ret;
}