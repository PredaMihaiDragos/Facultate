#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

class automat
{
public:
    automat(int nr_stari)
    {
        this->nr_stari = nr_stari;
        vecini.resize(nr_stari);
        is_final.resize(nr_stari);
        viz.resize(nr_stari);
        for(vector<vector<int> > &v:vecini)
            v.resize(26);
    }
    void SetStareInit(int stare)
    {
        stare_init = stare;
    }
    void AddStareFinala(int stare)
    {
        is_final[stare] = true;
    }
    void AddEdge(int x, int y, char val)
    {
        vecini[x][val-'a'].push_back(y);
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
    vector<string> GetWords(int nr_max)
    {
        vector<string> ret;
        queue<pair<int, string> > q;
        q.push(make_pair(stare_init, ""));
        while(q.empty() == false)
        {
            pair<int, string> f = q.front();
            q.pop();

            if(is_final[f.first])
            {
               ret.push_back(f.second);
               if(ret.size() == nr_max)
                    break;
            }


            for(int i = 0; i < 26; ++i)
            {
                string newS = f.second;
                newS.push_back((char)('a' + i));
                for(int v:vecini[f.first][i])
                    q.push(make_pair(v, newS));
            }
        }
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
        for(int vecin:vecini[nod][x[0]-'a'])
            if(Contains(vecin, x+1, sz-1))
                return true;
        return false;
    }
    vector<vector<bool> > viz;
    vector<vector<vector<int> > > vecini;
    vector<bool> is_final;
    int stare_init;
    int nr_stari;
};

int main()
{
    ifstream in("nfa.in");
    ofstream out("nfa.out");
    int n, m, k, s;
    in >> n >> m >> k;
    automat aut(n+1);
    in >> s;
    aut.SetStareInit(s);
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
    int q;
    in >> q;
    while(q--)
    {
        char s[150];
        in >> s;
        out << aut.Contains(s) << "\n";
    }
    in.close();
    out.close();
    return 0;
}
