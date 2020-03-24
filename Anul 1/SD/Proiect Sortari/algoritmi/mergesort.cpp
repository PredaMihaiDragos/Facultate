#include <vector>

namespace mergesort
{
    void sort_util(std::vector<int> &v, std::vector<int> &tmp, int st, int dr)
    {
        if(st == dr)
            return;
        int mid = (st + dr) / 2;
        sort_util(v, tmp, st, mid);
        sort_util(v, tmp, mid + 1, dr);

        for(int i = st; i <= dr; ++i)
            tmp[i] = v[i];
        int ind1 = st;
        int ind2 = mid + 1;
        int i;
        for(i = st; i <= dr && ind1 <= mid && ind2 <= dr; ++i)
        {
            if(tmp[ind1] < tmp[ind2])
                v[i] = tmp[ind1++];
            else
                v[i] = tmp[ind2++];
        }
        while(ind1 <= mid)
            v[i++] = tmp[ind1++];
        while(ind2 <= dr)
            v[i++] = tmp[ind2++];
    }
    void Sort(std::vector<int> &v)
    {
        std::vector<int> tmp(v.size());
        sort_util(v, tmp, 0, v.size() - 1);
    }
}
