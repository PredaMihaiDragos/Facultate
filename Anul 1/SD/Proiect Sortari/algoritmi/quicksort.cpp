#include <vector>

namespace quicksort
{
    void sort_util(std::vector<int> &v, int st, int dr)
    {
        int pivot = v[(st + dr) / 2];

        int i = st, j = dr;
        while(i <= j)
        {
            while(v[i] < pivot)
                ++i;
            while(v[j] > pivot)
                --j;
            if(i <= j)
            {
                std::swap(v[i], v[j]);
                ++i;
                --j;
            }
        }
        if(st < j)
            sort_util(v, st, j);
        if(i < dr)
            sort_util(v, i, dr);
    }
    void Sort(std::vector<int> &v)
    {
        sort_util(v, 0, v.size() - 1);
    }
}
