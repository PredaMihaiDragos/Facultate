#pragma once

#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>

typedef std::unordered_map<int, std::unordered_map<char, std::unordered_set<int> > > veciniMatrix;

class automaton
{
public:
    static const char LAMBDA = '$';
    void AddStareFinala(int stare);
    void AddStareFinala(const std::vector<int> &stare);
    void SetStareInit(int stare);
    virtual void AddEdge(int from, int to, char val) = 0;
    bool Contains(char* x) const;

    const veciniMatrix& GetVecini() const { return vecini; }
    const std::unordered_set<int>& GetFinals() const { return finals; }
    int GetStareInit() const { return stare_init;  }
    std::unordered_set<int> GetVecini(int stare, char c) const;
    std::set<std::pair<char, int> > GetVecini(int stare) const;
    bool IsFinal(int stare) const { return finals.find(stare) != finals.end(); }

    void SetFinals(const std::unordered_set<int>& finals) { this->finals = finals; }

    static veciniMatrix GetTranspose(const veciniMatrix& vecini);

    friend std::istream& operator>> (std::istream& in, automaton& aut);
    friend std::ostream& operator<< (std::ostream& out, const automaton& aut);
private:
    bool Contains(int nod, char* x, int sz, std::set<std::pair<int, int> > &viz) const;
protected:
    veciniMatrix vecini;
    std::unordered_set<int> finals;
    int stare_init;
};
