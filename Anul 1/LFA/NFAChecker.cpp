#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <unordered_map>

using namespace std;

class automat
{
public:
    automat(int nr_stari, int stare_init)
    {
        this->nr_stari = nr_stari;
        this->stare_init = stare_init;
        vecini.resize(nr_stari);
        is_final.resize(nr_stari);
        viz.resize(nr_stari);
    }
    void AddStareFinala(int stare)
    {
        is_final[stare] = true;
    }
    void AddEdge(int x, int y, char val)
    {
        vecini[x][val].push_back(y);
    }
    bool Contains(char * x)
    {
        int sz = strlen(x);
        for(vector<bool> &v: viz)
            v.resize(sz, false);
        bool ret = Contains(stare_init, x, sz);
        for(vector<bool> &v: viz)
            v = vector<bool>();
        return ret;
    }
private:
    bool Contains(int nod, char * x, int sz)
    {
        if(sz == 0)
            return is_final[nod];
        if(viz[nod][sz-1])
            return false;
        viz[nod][sz-1] = true;
        if(vecini[nod].find(x[0]) == vecini[nod].end())
            return false;
        for(int vecin:vecini[nod][x[0]])
            if(Contains(vecin, x+1, sz-1))
                return true;
        return false;
    }
    vector<vector<bool> > viz;
    vector<unordered_map<char, vector<int> > > vecini;
    vector<bool> is_final;
    int stare_init;
    int nr_stari;
};

int main()
{
    ifstream in("data.in");
    ofstream out("data.out");
    int n, m, k, s, q;
    in >> n >> m >> k >> s;
    automat aut(n+1, s);
    while(k--)
    {
        int stare;
        in >> stare;
        aut.AddStareFinala(stare);
    }
    while(m--)
    {
        int a, b;
        char c;
        in >> a >> b >> c;
        aut.AddEdge(a, b, c);
    }
    in >> q;
    char s[1005];
    while(q--)
    {
        in >> s;
        out << aut.Contains(s) << "\n";
    }
    in.close();
    out.close();
    return 0;
}
