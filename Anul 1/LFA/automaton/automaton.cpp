#include "automaton.h"

automaton::automaton(int nr_stari)
{
    this->nr_stari = nr_stari;
    vecini.resize(nr_stari);
    is_final.resize(nr_stari);
}

void automaton::AddStareFinala(int stare)
{
	is_final[stare] = true;
}

void automaton::SetStareInit(int stare)
{
    stare_init = stare;
}

bool automaton::Contains(char* x) const
{
    int sz = strlen(x);
    std::set<std::pair<int, int> > viz;
    bool ret = Contains(stare_init, x, sz, viz);
    return ret;
}

bool automaton::Contains(int nod, char* x, int sz, std::set<std::pair<int, int> >& viz) const
{
    if (sz == 0)
        return is_final[nod];
    if (viz.find(std::make_pair(nod, sz - 1)) != viz.end())
        return false;
    viz.insert(std::make_pair(nod, sz - 1));
    auto elem = vecini[nod].find(x[0]);
    if (elem == vecini[nod].end())
        return false;
    for (int vecin : elem->second)
        if (Contains(vecin, x + 1, sz - 1, viz))
            return true;
    return false;
}