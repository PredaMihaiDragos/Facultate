#include <iostream>
#include <fstream>

#include "lambda_nfa.h"
#include "nfa.h"
#include "dfa.h"
#include "regGrammar.h"

using namespace std;

int main()
{
    ifstream in("grammar.in");
    regGrammar gr;
    in >> gr;
    in.close();

    lambda_nfa aut(gr);
    nfa NFA(aut);
    dfa DFA(NFA);
    DFA.Minimize();

    ofstream out("grammar.out");
    out << DFA;
    out.close();


   /* ifstream in("nfa.in");
    lambda_nfa aut;
    in >> aut;

    nfa NFA(aut);
    dfa DFA(NFA);
    DFA.Minimize();

    cout << DFA;

    ofstream out("nfa.out");
    int q;
    in >> q;
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