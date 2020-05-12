#include <fstream>
#include <ctime>
#include <random>

using namespace std;

long long llrand()
{
    return 1LL * rand() * rand();
}

int main()
{
    srand(time(0));
    ofstream out("data.in");
    out << 1 << "\n";
    const int n = 5000000;
    const int VAL_MAX = 2000000000;    
    out << n << " " << VAL_MAX << " Generat_random\n";
    for(int i = 0; i < n; ++i)
        out << llrand() % VAL_MAX << " ";
    out.close();
    return 0;
}