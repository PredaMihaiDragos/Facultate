#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <set>

class automaton
{
public:
    automaton(int nr_stari);
    const char LAMBDA = '$';
    void AddStareFinala(int stare);
    void SetStareInit(int stare);
    virtual void AddEdge(int from, int to, char val) = 0;
    bool Contains(char* x) const;
    int GetNrStari() const { return nr_stari; }
private:
    bool Contains(int nod, char* x, int sz, std::set<std::pair<int, int> > &viz) const;
protected:
    std::vector<std::unordered_map<char, std::vector<int> > > vecini;
    std::vector<bool> is_final;
    int stare_init;
    int nr_stari;
};
