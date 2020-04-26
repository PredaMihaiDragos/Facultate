#pragma once

#include "automaton.h"
#include "nfa.h"

#include <queue>

class dfa : public automaton
{
public:
	dfa(int nr_stari = 0);
	dfa(const nfa& from);
	void AddEdge(int from, int to, char val);
	void Minimize();
private:
	void DFS(int current, std::vector<bool>& viz) const;

};