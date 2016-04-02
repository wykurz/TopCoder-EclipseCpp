#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <tuple>
#include <valarray>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <typeinfo>
#include <functional>

using namespace std;

#define REP(k, a) for (int k = 0; k < (a); ++k)

// BEGIN CUT HERE

template <int N, typename T=char>
struct SetUnion
{
    SetUnion()
    {
        REP(i, N) data[i] = i;
    }

    void merge(int u, int v)
    {
        auto ru = root(u);
        auto rv = root(v);
        auto w = min(ru, rv);
        data[ru] = w;
        data[rv] = w;
    }

    bool conn(int u, int v)
    {
        return root(u) == root(v);
    }

    bool conn(int u, int v) const
    {
        return root(u) == root(v);
    }

    template<int N2, typename T2>
    friend ostream& operator<<(ostream& ostr, const SetUnion<N2, T2>& su);

  private:
    int root(int u) const
    {
        auto r = data[u];
        while (r != data[r]) r = data[r];
        return r;
    }

    int root(int u)
    {
        auto r = data[u];
        while (r != data[r]) r = data[r];
        while (u != data[u]) {
            auto t = data[u];
            data[u] = r;
            u = t;
        }
        assert(u == r);
        return r;
    }

    array<T, N> data;
};

template<int N, typename T>
ostream& operator<<(ostream& ostr, const SetUnion<N, T>& su)
{
    ostr << "[ ";
    REP(i, N) ostr << su.root(i) << " ";
    ostr << "]";
    return ostr;
}

// END CUT HERE

void testSmall()
{
    // TODO
}

void testLarge()
{
    // TODO
}

int main( int argc, char* argv[] )
{
    testSmall();
    testLarge();
    cout << "OK!" << endl;
    return 0;
}
