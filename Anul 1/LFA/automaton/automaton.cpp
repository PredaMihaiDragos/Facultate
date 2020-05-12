#include "automaton.h"

void automaton::AddStareFinala(int stare)
{
    finals.insert(stare);
}

void automaton::AddStareFinala(const std::vector<int> &stare)
{
    finals.insert(stare.begin(), stare.end());
}

void automaton::SetStareInit(int stare)
{
    stare_init = stare;
}

std::unordered_set<int> automaton::GetVecini(int stare, char c) const
{
    std::unordered_set<int> ret;
    if(auto stareVecini = vecini.find(stare); stareVecini != vecini.end())
    { 
        if (auto v = stareVecini->second.find(c); v != stareVecini->second.end())
            for (auto x : v->second)
                ret.insert(x);
    }
    return ret;
}

std::set<std::pair<char, int> > automaton::GetVecini(int stare) const
{
    std::set<std::pair<char, int> > ret;
    if (auto stareVecini = vecini.find(stare); stareVecini != vecini.end())
    {
        for (const auto& charEdges : stareVecini->second)
            for (auto stare : charEdges.second)
                ret.insert(std::make_pair(charEdges.first, stare));
    }
    return ret;
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
        return IsFinal(nod);
    if (viz.find(std::make_pair(nod, sz - 1)) != viz.end())
        return false;
    viz.insert(std::make_pair(nod, sz - 1));
    auto vec = GetVecini(nod, x[0]);
    for (int vecin : vec)
        if (Contains(vecin, x + 1, sz - 1, viz))
            return true;
    vec = GetVecini(nod, LAMBDA);
    for (int vecin : vec)
        if (Contains(vecin, x, sz, viz))
            return true;
    return false;
}

veciniMatrix automaton::GetTranspose(const veciniMatrix& vecini)
{
    veciniMatrix ret;
    for(const auto &p:vecini)
        for(const auto& charEdges:p.second)
            for (int vecin : charEdges.second)
                ret[vecin][charEdges.first].insert(p.first);
    return ret;
}

std::istream& operator>> (std::istream& in, automaton& aut)
{
    aut.vecini = veciniMatrix();
    aut.finals.clear();

    int n, m, k, s;
    in >> n >> m >> k >> s;
    aut.SetStareInit(s);
    while (k--)
    {
        int stare;
        in >> stare;
        aut.AddStareFinala(stare);
    }
    while (m--)
    {
        int a, b;
        char c;
        in >> a >> b >> c;
        aut.AddEdge(a, b, c);
    }
    return in;
}

std::ostream& operator<< (std::ostream& out, const automaton& aut)
{
    std::vector<std::pair<std::pair<int, int>, char> > edges;
    for (auto p : aut.vecini)
    {
        auto vec = aut.GetVecini(p.first);
        for (auto edge : vec)
            edges.push_back(std::make_pair(std::make_pair(p.first, edge.second), edge.first));
    }
    out << aut.vecini.size() << " " << edges.size() << " " << aut.finals.size() << " " << aut.stare_init << "\n";
    for (auto stare : aut.finals)
        out << stare << " ";
    out << "\n";
    for (auto edge : edges)
        out << edge.first.first << " " << edge.first.second << " " << edge.second << "\n";
    return out;
}