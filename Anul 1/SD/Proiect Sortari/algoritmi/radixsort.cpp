#include <vector>
#include <algorithm>

namespace radixsort
{
    const int base = 256;

    inline int GetDigit(int x, int d)
    {
        return (x / d) % base;
    }

    void count_sort(std::vector<int> &v, std::vector<int> &temp, std::vector<int> &cnt, int digit)
    {
        for(int i = 0; i < base; ++i)
            cnt[i] = 0;
        for(int i = 0; i < v.size(); ++i)
            cnt[GetDigit(v[i], digit)]++;
        for(int i = 1; i < base; ++i)
            cnt[i] += cnt[i-1];
        for(int i = v.size()-1; i >= 0; --i)
            temp[--cnt[GetDigit(v[i], digit)]] = v[i];
        v = temp;
    }

    void Sort(std::vector<int> &v)
    {
        int mx = *std::max_element(v.begin(), v.end());
        std::vector<int> temp(v.size());
        std::vector<int> cnt(base);

        for(long long i = 1; mx / i > 0; i *= base)
            count_sort(v, temp, cnt, i);
    }
}
