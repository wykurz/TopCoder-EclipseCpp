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

const int dd[] = {1, 0, -1, 0};

class BearSpans {
public:
    vector <int> findAnyGraph(int n, int m, int k)
    {
        if (10 < k || (1 < k && n < PW(k))) return {-1};
        vector<int> ret;
        if (1 == k) {
            REP(i, n - 1) {
                ret.push_back(i + 1);
                ret.push_back(i + 2);
                --m;
            }
            if (0 < m) {
                ret.push_back(n);
                ret.push_back(1);
                --m;
            }
            REP(i, n) FOR(j, i + 2, n - 1) {
                if (m == 0) return ret;
                if (i + n - j < 2) continue;
                assert(0 < m);
                ret.push_back(i + 1);
                ret.push_back(j + 1);
                --m;
            }
            return ret;
        }
        REP(di, k) {
            auto d = PW(di);
            auto s = d - 1;
            auto e = PW(k);
            for (int i = s; i + d < e; i += 2 * d) {
                assert(0 < m);
                ret.push_back(i + 1);
                ret.push_back(i + 2);
                // cerr << i << " " << i + 1 << endl;
                --m;
            }
        }
        FOR(i, PW(k) - 1, n - 2) {
            assert(0 < m);
            ret.push_back(i + 1);
            ret.push_back(i + 2);
            --m;
        }
        if (0 < m) {
            ret.push_back(n);
            ret.push_back(1);
            --m;
        }
        REP(i, n) FOR(j, i + 2, n - 1) {
            if (m == 0) return ret;
            if (i + n - j < 2) continue;
            assert(0 < m);
            ret.push_back(i + 1);
            ret.push_back(j + 1);
            --m;
        }
        return ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int retrunValueARRAY[] = {-1};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(10, theObject.findAnyGraph(5, 4, 65),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(10, theObject.findAnyGraph(2, 1, 1),retrunValue);
    }
    {
        int retrunValueARRAY[] = {-1};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(11, theObject.findAnyGraph(2, 1, 2),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 1, 2};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(12, theObject.findAnyGraph(3, 2, 1),retrunValue);
    }
    {
        int retrunValueARRAY[] = {-1};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(13, theObject.findAnyGraph(3, 2, 2),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 1, 2, 2, 3};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(14, theObject.findAnyGraph(4, 3, 1),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 1, 2, 2, 3, 3, 0};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(15, theObject.findAnyGraph(4, 4, 1),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 2};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(16, theObject.findAnyGraph(4, 5, 1),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 2, 1, 3};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(17, theObject.findAnyGraph(4, 6, 1),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 2, 3, 1, 2};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(18, theObject.findAnyGraph(4, 3, 2),retrunValue);
    }
    {
        int retrunValueARRAY[] = {-1};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(19, theObject.findAnyGraph(4, 3, 3),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 2, 3, 1, 2, 3, 0};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(19, theObject.findAnyGraph(4, 4, 2),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 2, 3, 1, 2, 3, 0, 0, 2};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(20, theObject.findAnyGraph(4, 5, 2),retrunValue);
    }
    {
        int retrunValueARRAY[] = {0, 1, 2, 3, 1, 2, 3, 0, 0, 2, 1, 3};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(21, theObject.findAnyGraph(4, 6, 2),retrunValue);
    }
    {
        int retrunValueARRAY[] = {-1};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(22, theObject.findAnyGraph(4, 3, 3),retrunValue);
    }

    {
        int retrunValueARRAY[] = {1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1, 12, 1, 13, 1, 14, 1, 15, 1, 16, 1, 17, 2, 3, 2, 8, 3, 9, 8, 9, 10, 12, 12, 14 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BearSpans theObject;
        eq(0, theObject.findAnyGraph(17, 22, 1),retrunValue);
    }
//    {
//        int retrunValueARRAY[] = {6, 5, 7, 6, 1, 2, 3, 4, 8, 9, 3, 5, 7, 4, 1, 9, 6, 2, 6, 1, 1, 8, 4, 5 };
//        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        BearSpans theObject;
//        eq(1, theObject.findAnyGraph(9, 12, 3),retrunValue);
//    }
//    {
//        int retrunValueARRAY[] = {-1 };
//        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        BearSpans theObject;
//        eq(2, theObject.findAnyGraph(9, 12, 7),retrunValue);
//    }
//    {
//        int retrunValueARRAY[] = {-1 };
//        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        BearSpans theObject;
//        eq(3, theObject.findAnyGraph(1000, 999, 970),retrunValue);
//    }
//    {
//        int retrunValueARRAY[] = {1, 2 };
//        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        BearSpans theObject;
//        eq(4, theObject.findAnyGraph(2, 1, 1),retrunValue);
//    }
//    {
//        int retrunValueARRAY[] = {1, 2, 1, 3 };
//        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        BearSpans theObject;
//        eq(5, theObject.findAnyGraph(3, 2, 1),retrunValue);
//    }
//    {
//        int retrunValueARRAY[] = {-1 };
//        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        BearSpans theObject;
//        eq(6, theObject.findAnyGraph(3, 3, 2),retrunValue);
//    }
    return 0;
}
// END CUT HERE
