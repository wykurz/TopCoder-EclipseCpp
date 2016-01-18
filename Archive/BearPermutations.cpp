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

constexpr int L = 100 + 1;

ll bn[L][L];
// count * min idx * value
ll dp[L][L][2 * L];
// count * (value + min idx)
ll dpL[L][L + L];
// count * (value - min idx + (N - 1))
ll dpR[L][L + L];

class BearPermutations {
public:
    int countPermutations(int N, int S, int mod)
    {
        if (N < 2) return 0;
        auto add = [&](ll& a, ll b) { a = (a + b) % mod; };
        auto mul = [&](ll a, ll b) { return (a * b) % mod; };
        ZERO(bn);
        REP(n, N + 1) bn[n][0] = 1;
        FOR(n, 1, N) FOR(m, 1, n) add(bn[n][m], bn[n - 1][m] + bn[n - 1][m - 1]);
        ZERO(dp);
        dp[0][0][0] = 1;
        ZERO(dpL);
        ZERO(dpR);
        FOR(n, 1, N) {
            REP(w, N) REP(s, S + 1) {
                add(dpL[n - 1][s - w + (N - 1)], dp[n - 1][w][s]);
                add(dpR[n - 1][s + w], dp[n - 1][w][s]);
            }
            FOR(n1, 0, n - 1) {
                const int n2 = n - n1 - 1;
                const int w = n1;
                if (n1 == 0 || n2 == 0) REP(s, S + 1) REP(w2, N) add(dp[n][w][s], dp[n1 + n2][w2][s]);
                else REP(sw1, N + S + 1) REP(sw2, N + S + 1) {
                    int s = sw1 + sw2 - (N - 1) + n1 + 1;
                    if (S < s) continue;
                    add(dp[n][w][s], mul(mul(bn[n1 + n2][n1], dpL[n1][sw1]), dpR[n2][sw2]));
                }
            }
        }
        ll ret = 0;
        REP(w, N) REP(s, S + 1) add(ret, dp[N][w][s]);
        return (int) ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        BearPermutations theObject;
        eq(9, theObject.countPermutations(55, 67, 867907753),9880642);
    }
    {
        BearPermutations theObject;
        eq(11, theObject.countPermutations(31, 100, 879828539),311969414);
    }
    {
        BearPermutations theObject;
        eq(8, theObject.countPermutations(2, 0, 71876209),2);
    }
    {
        BearPermutations theObject;
        eq(7, theObject.countPermutations(3, 2, 71876209),2 * 3);
    }
    {
        BearPermutations theObject;
        eq(6, theObject.countPermutations(4, 50, 71876209),2 * 3 * 4);
    }
    {
        BearPermutations theObject;
        eq(9, theObject.countPermutations(5, 100, 71876209),2 * 3 * 4 * 5);
    }

    {
        BearPermutations theObject;
        eq(10, theObject.countPermutations(4, 4, 71876209),2 * 3 * 4);
    }

    {
        BearPermutations theObject;
        eq(0, theObject.countPermutations(3, 1, 71876209),4);
    }
    {
        BearPermutations theObject;
        eq(1, theObject.countPermutations(4, 0, 1000003),8);
    }
    {
        BearPermutations theObject;
        eq(2, theObject.countPermutations(4, 1, 483128897),8);
    }
    {
        BearPermutations theObject;
        eq(3, theObject.countPermutations(5, 3, 907283243),82);
    }
    {
        BearPermutations theObject;
        eq(4, theObject.countPermutations(5, 100, 101),19);
    }
    {
        BearPermutations theObject;
        eq(5, theObject.countPermutations(20, 30, 3),2);
    }
    return 0;
}
// END CUT HERE
