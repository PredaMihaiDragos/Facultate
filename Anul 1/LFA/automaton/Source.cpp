#include <iostream>

#include "lambda_nfa.h"
#include "nfa.h"
#include "dfa.h"

using namespace std;

int main()
{
    ifstream in("nfa.in");
    ofstream out("nfa.out");
    int n, m, k, s, q;
    in >> n >> m >> k >> s;
    lambda_nfa aut(n + 1);
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

    nfa NFA(aut);
    dfa DFA(NFA);
    DFA.Minimize();
    DFA.Print();

 /*   in >> q;
    char cuv[1005];
    while (q--)
    {
        in >> cuv;
        out << DFA.Contains(cuv) << "\n";
    }
    in.close();
    out.close();*/
	return 0;
}