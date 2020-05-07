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

void automaton::AddStareFinala(const std::vector<int> &stare)
{
    for (int x : stare)
        is_final[x] = true;
}

void automaton::SetStareInit(int stare)
{
    stare_init = stare;
}

void automaton::SetNrStari(int nr_stari)
{
    this->nr_stari = nr_stari;
    vecini.resize(nr_stari);
    is_final.resize(nr_stari);
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
    if (elem != vecini[nod].end())
    {
        for (int vecin : elem->second)
            if (Contains(vecin, x + 1, sz - 1, viz))
                return true;
    }
    elem = vecini[nod].find(LAMBDA);
    if (elem != vecini[nod].end())
    {
        for (int vecin : elem->second)
            if (Contains(vecin, x, sz, viz))
                return true;
    }
    return false;
}

veciniMatrix automaton::GetTranspose(const veciniMatrix& vecini)
{
    veciniMatrix ret(vecini.size());
    for (unsigned int stare = 0; stare < vecini.size(); ++stare)
        for (const auto& charEdges : vecini[stare])
            for (int vecin : charEdges.second)
                ret[vecin][charEdges.first].insert(stare);
    return ret;
}

std::istream& operator>> (std::istream& in, automaton& aut)
{
    aut.vecini = veciniMatrix();
    aut.is_final.clear();

    int n, m, k, s, q;
    in >> n >> m >> k >> s;
    aut.SetNrStari(n+1);
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
    for (int from = 0; from < aut.nr_stari; ++from)
        for (const auto& charEdges : aut.vecini[from])
            for (int to : charEdges.second)
                edges.push_back(std::make_pair(std::make_pair(from, to), charEdges.first));
    std::vector<int> finale;
    for (int i = 0; i < aut.nr_stari; ++i)
        if (aut.is_final[i])
            finale.push_back(i);
    out << aut.nr_stari << " " << edges.size() << " " << finale.size() << " " << aut.stare_init << "\n";
    for (auto stare : finale)
        out << stare << "\n";
    for (auto edge : edges)
        out << edge.first.first << " " << edge.first.second << " " << edge.second << "\n";
    return out;
}