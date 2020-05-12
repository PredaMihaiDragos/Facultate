#include <vector>

namespace Heapsort
{
    void Comb_Heap(std::vector<int> &v, int ind, int sz)
    {
        int st;
        int dr;
        int next;
        while(2 * ind < sz)
        {
            st = 2 * ind;
            dr = st + 1;
            if(dr >= sz || v[st] > v[dr])
                next = st;
            else
                next = dr;
            if(v[ind] < v[next])
                std::swap(v[ind], v[next]), std::swap(ind, next);
            else
                break;
        }
    }

    void Make_Heap(std::vector<int> &v)
    {
        for(int i = v.size() / 2; i >= 0; --i)
            Comb_Heap(v, i, v.size());
    }

    inline void DeleteMax(std::vector<int> &v, int sz)
    {
        std::swap(v[0], v[sz-1]);
        Comb_Heap(v, 0, sz - 1);
    }

    void Sort(std::vector<int> &v)
    {
        Make_Heap(v);
        int mx;
        for(int i = v.size()-1; i > 0; --i)
        {
            mx = v[0];
            DeleteMax(v, i);
            v[i] = mx;
        }
    }
}
