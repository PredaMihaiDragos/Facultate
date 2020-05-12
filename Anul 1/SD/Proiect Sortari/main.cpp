#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
#include <chrono>

#include "algoritmi/stlsort.cpp"
#include "algoritmi/quicksort.cpp"
#include "algoritmi/mergesort.cpp"
#include "algoritmi/heapsort.cpp"
#include "algoritmi/radixsort.cpp"
#include "algoritmi/treapsort.cpp"

using namespace std;

/*
ofstream out("result.txt");
#define cout out
*/

void test_function(function<void(vector<int>&)> f, vector<int> v)
{
    auto start = chrono::high_resolution_clock::now();
    f(v);
    auto stop = chrono::high_resolution_clock::now();
    assert(is_sorted(v.begin(), v.end()));

    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "a durat: " << duration.count() << " milisecunde\n";
}

int main()
{
    ifstream in("data.in");
    int teste;
    in >> teste;
    while(teste--)
    {
        string type;
        int n, val_max;
        in >> n >> val_max >> type;
        cout << "Numere: " << n << "\n";
        cout << "Valoare maxima: " << val_max << "\n";
        cout << "Tipul vectorului: " << type << "\n";

        vector<int> v(n);
        for(int &x:v)
            in >> x;

        cout << "STL sort: ";
        test_function(stlsort::Sort, v);
        cout << "Quicksort ";
        test_function(quicksort::Sort, v);
        cout << "Mergesort ";
        test_function(Mergesort::Sort, v);
        cout << "Heapsort ";
        test_function(Heapsort::Sort, v);
        cout << "Radixsort ";
        test_function(Radixsort::Sort, v);
        cout << "Treapsort ";
        test_function(treapsort::Sort, v);

        cout << "\n";
    }
    return 0;
}
