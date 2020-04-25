#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>

typedef std::vector<std::unordered_map<char, std::unordered_set<int> > > veciniMatrix;

class automaton
{
public:
    automaton(int nr_stari);
    static const char LAMBDA = '$';
    void AddStareFinala(int stare);
    void AddStareFinala(const std::vector<int> &stare);
    void SetStareInit(int stare);
    virtual void AddEdge(int from, int to, char val) = 0;
    bool Contains(char* x) const;

    void Print();

    const veciniMatrix& GetVecini() const { return vecini; }
    const std::vector<bool>& GetIsFinal() const { return is_final; }
    int GetStareInit() const { return stare_init;  }
    int GetNrStari() const { return nr_stari; }
    bool IsFinal(int stare) const { return is_final[stare]; }

    void SetIsFinal(const std::vector<bool>& is_final) { this->is_final = is_final; }
private:
    bool Contains(int nod, char* x, int sz, std::set<std::pair<int, int> > &viz) const;
protected:
    veciniMatrix vecini;
    std::vector<bool> is_final;
    int stare_init;
    int nr_stari;
};
