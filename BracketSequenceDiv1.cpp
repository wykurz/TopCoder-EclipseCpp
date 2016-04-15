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

ll dp[40][40][40];

char t[256];

class BracketSequenceDiv1 {
public:
    string s;
    ll f(bool need, int i, int j)
    {
        if (j <= i) return need ? -1 : 0;
        if (-1 != dp[need][i][j]) return dp[need][i][j];
        ll res = 0;
        if (t[int(s[i])] == s[j]) res += f(false, i + 1, j - 1);
        auto val = f(need, i + 1, j);
        res += -1 != val ? val : 0;
        val = f(need, i, j - 1);
        res += -1 != val ? val : 0;
        val = f(need, i + 1, j - 1);
        res -= -1 != val ? val : 0;
        if ((j - i) % 2 == 1) {
            bool ok = true;
            REP(k, j - i / 2 + 1) {
                if (j - k < i + k) break;
                if (s[i + k] == ')' || s[i + k] == ']' || t[int(s[i + k])] != s[j - k]) {
                    ok = false;
                    break;
                }
            }
            if (ok) res += 1;
        }
        dp[need][i][j] = res;
        return res;
    }
    ll count(string s_)
    {
        FILL3D(dp, -1);
        t['('] = ')';
        t[')'] = 'x';
        t['['] = ']';
        t[']'] = 'x';
        s = s_;
        auto res = f(true, 0, s.size() - 1);
        REP(z, 2) REP(i, s.size()) REP(j, s.size()) cerr << z << ":: " << i << ", " << j << ": " << dp[z][i][j] << endl;
        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        BracketSequenceDiv1 theObject;
        eq<ll>(0, theObject.count("()[]"),3L);
    }
    {
        BracketSequenceDiv1 theObject;
        eq<ll>(1, theObject.count("())"),2L);
    }
//    {
//        BracketSequenceDiv1 theObject;
//        eq<ll>(2, theObject.count("()()"),4L);
//    }
//    {
//        BracketSequenceDiv1 theObject;
//        eq<ll>(3, theObject.count("([)]"),2L);
//    }
//    {
//        BracketSequenceDiv1 theObject;
//        eq<ll>(4, theObject.count("())[]][]([]()]]()]]]"),3854L);
//    }
    return 0;
}
// END CUT HERE
