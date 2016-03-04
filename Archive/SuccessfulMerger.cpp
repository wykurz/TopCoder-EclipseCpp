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


constexpr int L = 50;
bool g[L][L] = {};
bool h[L] = {};
bool v[L] = {};

class SuccessfulMerger {
public:
    int dfs(int prev, int i)
    {
        if (v[i]) {
            h[i] = true;
            return i;
        }
        v[i] = true;
        REP(j, L) if(prev != j && g[i][j]) {
            int k = dfs(i, j);
            if (i == k) break;
            if (0 <= k) {
                h[i] = true;
                return k;
            }
        }
        return -1;
    }
    int minimumMergers(vector <int> r)
    {
        ZERO(g);
        ZERO(h);
        ZERO(v);
        int N = r.size();
        REP(i, N) {
            if (g[i][r[i]]) continue;
            g[i][r[i]] = true;
            g[r[i]][i] = true;
        }
        int l = 0;
        dfs(-1, 0);
        REP(i, N) if (h[i]) {
            int c = 0;
            REP(j, N) if (g[i][j]) ++c;
            if (2 == c) {
                ++l;
                break;
            }
        }
        REP(i, N) {
            int c = 0;
            REP(j, N) if (g[i][j]) ++c;
            if (1 == c) ++l;
        }
        return max(N - l - 1, 0);
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int roadARRAY[] = {5, 13, 3, 16, 10, 15, 4, 12, 4, 15, 7, 10, 6, 9, 16, 8, 11, 6};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(0, theObject.minimumMergers(road),11);
    }
    {
        int roadARRAY[] = {9, 3, 7, 8, 12, 18, 2, 11, 19, 7, 13, 13, 1, 19, 19, 4, 10, 19, 6, 3};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(6, theObject.minimumMergers(road),12);
    }
    {
        int roadARRAY[] = {2, 2, 1, 1, 1};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(0, theObject.minimumMergers(road),1);
    }
    {
        int roadARRAY[] = {3, 4, 5, 4, 5, 3};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(1, theObject.minimumMergers(road),2);
    }
    {
        int roadARRAY[] = {1, 0, 1, 0, 0, 0, 1, 0, 1, 1};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(2, theObject.minimumMergers(road),1);
    }
    {
        int roadARRAY[] = {1, 2, 3, 0};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(3, theObject.minimumMergers(road),2);
    }
    {
        int roadARRAY[] = {31, 19, 0, 15, 30, 32, 15, 24, 0, 20, 40, 1, 22, 21, 39, 28, 0, 23, 15, 5, 19, 22, 6, 32, 8, 38, 35, 30, 4, 28, 32, 18, 18, 9, 22, 41, 20, 18, 6, 25, 41, 34, 4};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(4, theObject.minimumMergers(road),25);
    }
    {
        int roadARRAY[] = {1, 0};
        vector <int> road( roadARRAY, roadARRAY+ARRSIZE(roadARRAY) );
        SuccessfulMerger theObject;
        eq(5, theObject.minimumMergers(road),0);
    }
    return 0;
}
// END CUT HERE
