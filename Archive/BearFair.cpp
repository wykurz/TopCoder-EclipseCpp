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

bool dp[27][27] = {false};

class BearFair {
public:
    string ret(bool ok)
    {
        return ok ? "fair" : "unfair";
    }
    string isFair(int n, int max, vector <int> s, vector <int> q)
    {
        vector<pair<int, int>> v;
        int Q = s.size();
        int L = n / 2 + 1;
        REP(i, Q) v.push_back(make_pair(s[i], q[i]));
        sort(ALL(v));
        REP(i, Q) {
            s[i] = v[i].first;
            q[i] = v[i].second;
            // cerr << "s[" << i << "] = " << s[i] << "; q[" << i << "] = " << q[i] << endl;
        }
        FOR(i, 1, Q - 1) {
            if (s[i - 1] == s[i] && q[i - 1] != q[i]) return ret(false);
            if (q[i] < q[i - 1]) return ret(false);
        }
        dp[0][0] = true;
        int query = 0;
        FOR(add, 1, max) {
            if (add & 1) RFOR(i, L, 0) RFOR(j, L, 0) dp[i][j + 1] |= dp[i][j];
            else         RFOR(i, L, 0) RFOR(j, L, 0) dp[i + 1][j] |= dp[i][j];
            if (query < Q && add == s[query]) {
                REP(i, L) REP(j, L) if (i + j != q[query]) dp[i][j] = false;
                while (query < Q && add == s[query]) ++query;
            }
        }
        for (; query < Q; ++query) {
            REP(i, L) REP(j, n - i + 1) if (i + j != q[query]) dp[i][j] = false;
        }
        return ret(dp[n / 2][n / 2]);
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int upToARRAY[] = {45, 40, 48, 32, 39, 22, 17, 29, 16, 20, 7, 11, 41, 46, 54, 9, 36, 52, 49, 19, 33, 26, 44, 30, 24, 28, 5, 34, 6, 43, 23, 18, 12, 51, 56, 14, 10, 37};
        vector <int> upTo( upToARRAY, upToARRAY+ARRSIZE(upToARRAY) );
        int quantityARRAY[] = {8, 7, 8, 7, 7, 5, 3, 6, 3, 5, 0, 0, 7, 8, 11, 0, 7, 9, 8, 4, 7, 6, 8, 7, 6, 6, 0, 7, 0, 7, 5, 3, 1, 8, 13, 1, 0, 7};
        vector <int> quantity( quantityARRAY, quantityARRAY+ARRSIZE(quantityARRAY) );
        BearFair theObject;
        eq(5, theObject.isFair(14, 842, upTo, quantity),"unfair");
    }
    {
        int upToARRAY[] = {1,2,3};
        vector <int> upTo( upToARRAY, upToARRAY+ARRSIZE(upToARRAY) );
        int quantityARRAY[] = {1,1,2};
        vector <int> quantity( quantityARRAY, quantityARRAY+ARRSIZE(quantityARRAY) );
        BearFair theObject;
        eq(2, theObject.isFair(2, 6, upTo, quantity),"unfair");
    }
    {
        int upToARRAY[] = {736,205,264,235,273,40,901,37,900,424,122,517,820,402,669,279,455,921,774,923,107,936,484,171,248,
           186,970,231,321,902,606,24,451,585,823,270,361,292,128,521,689,683,270,726,980,652,996,909,196,357};
        vector <int> upTo( upToARRAY, upToARRAY+ARRSIZE(upToARRAY) );
        int quantityARRAY[] = {35,9,9,9,9,3,46,3,46,18,7,25,39,18,32,9,20,49,37,49,7,49,24,8,9,8,49,9,12,46,29,2,20,29,39,9,16,11,7,27,33,32,9,34,49,32,50,47,8,16};
        vector <int> quantity( quantityARRAY, quantityARRAY+ARRSIZE(quantityARRAY) );
        BearFair theObject;
        eq(3, theObject.isFair(50, 1000, upTo, quantity),"fair");
    }
    {
        int upToARRAY[] = {3,6};
        vector <int> upTo( upToARRAY, upToARRAY+ARRSIZE(upToARRAY) );
        int quantityARRAY[] = {2,3};
        vector <int> quantity( quantityARRAY, quantityARRAY+ARRSIZE(quantityARRAY) );
        BearFair theObject;
        eq(1, theObject.isFair(4, 6, upTo, quantity),"unfair");
    }
    {
        int upToARRAY[] = {3,6};
        vector <int> upTo( upToARRAY, upToARRAY+ARRSIZE(upToARRAY) );
        int quantityARRAY[] = {2,4};
        vector <int> quantity( quantityARRAY, quantityARRAY+ARRSIZE(quantityARRAY) );
        BearFair theObject;
        eq(0, theObject.isFair(4, 6, upTo, quantity),"fair");
    }
    {
        int upToARRAY[] = {400,600};
        vector <int> upTo( upToARRAY, upToARRAY+ARRSIZE(upToARRAY) );
        int quantityARRAY[] = {4,0};
        vector <int> quantity( quantityARRAY, quantityARRAY+ARRSIZE(quantityARRAY) );
        BearFair theObject;
        eq(4, theObject.isFair(4, 1000, upTo, quantity),"unfair");
    }
    return 0;
}
// END CUT HERE
