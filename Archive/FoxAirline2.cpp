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
#include <cstring>
#include <cstdint>
#include <typeinfo>
#include <functional>

using namespace std;
// BEGIN CUT HERE
vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( size_t i = 0 ; i != s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}
vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( size_t i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))
template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( size_t i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( size_t i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FILL1D(a, v) std::fill_n(a, sizeof(a) / sizeof(a[0]), v)
#define FILL2D(a, v) std::fill_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), v)
#define FILL3D(a, v) std::fill_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), v)
#define FILL4D(a, v) std::fill_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), v)
#define COPY1D(a, b) std::copy_n(a, sizeof(a) / sizeof(a[0]), b)
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])
#define COPY3D(a, b) std::copy_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), &b[0][0][0])
#define COPY4D(a, b) std::copy_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), &b[0][0][0][0])
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define SQR(x) ((x) * (x))
#define PW(x) (1ll << (x))
#define BCNT(x) __builtin_popcountll(x)
#define LZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_clzll(x))
#define RZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_ctzll(x))
#define ALL(c) (c).begin(),(c).end()
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c,x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

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

class FoxAirline2 {
public:
    using su = SetUnion<12>;
    string ok(bool yes)
    {
        return yes ? "Possible" : "Impossible";
    }
    string isPossible(int n, vector <int> a, vector <int> b)
    {
        int m = a.size();
        auto allIn = [n](const su& t) {
            REP(v, n) if (!t.conn(0, v)) return false;
            return true;
        };
        auto done = [&allIn](const su& t1, const su& t2) {
            return allIn(t1) && allIn(t2);
        };
        function<bool(int, const su&, const su&)> dfs = [&a, &b, m, &done, &dfs](int e, const su& t1, const su& t2) {
            if (e == m) {
//                cerr << "e  : " << e << endl;
//                cerr << " t1: " << t1 << endl;
//                cerr << " t2: " << t2 << endl;
                return done(t1, t2);
            }
            if (!t1.conn(a[e], b[e])) {
                auto tn = t1;
                tn.merge(a[e], b[e]);
                // cerr << a[e] << "-" << b[e] << " => t1" << endl;
                if (dfs(e + 1, tn, t2)) return true;
                // cerr << " <-- " << a[e] << "-" << b[e] << endl;
            }
            if (!t2.conn(a[e], b[e])) {
                auto tn = t2;
                tn.merge(a[e], b[e]);
                // cerr << a[e] << "-" << b[e] << " => t2" << endl;
                if (dfs(e + 1, t1, tn)) return true;
                // cerr << " <-- " << a[e] << "-" << b[e] << endl;
            }
            if (t1.conn(a[e], b[e]) && t2.conn(a[e], b[e])) return dfs(e + 1, t1, t2);
            return false;
        };
        su t1, t2;
        return ok(dfs(0, t1, t2));
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int aARRAY[] = {0, 1, 2, 0, 1, 2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1, 2, 3, 2, 3, 3};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(6, theObject.isPossible(4, a, b),"Possible");
    }
    {
        int aARRAY[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1, 2, 3, 4, 5, 2, 3, 4, 5, 0};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(6, theObject.isPossible(6, a, b),"Possible");
    }
    {
        int aARRAY[] = {8, 7, 5, 9, 2, 9, 0, 1, 6, 2, 3, 0, 1, 3, 1, 2, 1, 8};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {5, 2, 4, 7, 5, 3, 1, 9, 8, 9, 9, 9, 7, 8, 8, 4, 5, 6};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(6, theObject.isPossible(10, a, b),"Possible");
    }
    {
        int aARRAY[] = {0,0,0,1,1,2,2,3};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,4,2,4,3,4,4};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(2, theObject.isPossible(5, a, b),"Possible");
    }
    {
        int aARRAY[] = {0,1,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,0,0};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(3, theObject.isPossible(2, a, b),"Possible");
    }
    {
        int aARRAY[] = {0};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(5, theObject.isPossible(2, a, b),"Impossible");
    }
    {
        int aARRAY[] = {0,0,0,1,1,2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,2,3,3};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(0, theObject.isPossible(4, a, b),"Possible");
    }
    {
        int aARRAY[] = {0,0,0,0,1,1,1,2,2,3,0};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,2,3,4,3,4,4,5};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(1, theObject.isPossible(6, a, b),"Impossible");
    }
    {
        int aARRAY[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 8};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9, 3, 4, 5, 6, 7, 8, 9, 4, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9, 6, 7, 8, 9, 7, 8, 9, 8, 9, 9};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FoxAirline2 theObject;
        eq(4, theObject.isPossible(10, a, b),"Possible");
    }
    return 0;
}
// END CUT HERE
