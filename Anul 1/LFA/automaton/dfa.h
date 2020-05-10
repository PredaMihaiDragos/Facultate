#pragma once

#include "automaton.h"
#include "regGrammar.h"
#include "nfa.h"

#include <queue>

class dfa : public automaton
{
public:
	dfa() {};
	dfa(const nfa& from);
	void AddEdge(int from, int to, char val);
	void Minimize();
private:
	void DFS(int current, std::unordered_set<int>& viz) const;

};