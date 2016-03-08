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

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define ALL(c) (c).begin(),(c).end()

using ll = long long;

constexpr int K = 50;
constexpr int L = K * K;
// min, max, min-diff
int dp[K][K][L] = {};

class CliqueParty {
public:
    int maxsize(vector <int> a, int S)
    {
        ZERO(dp);
        int N = a.size();
        sort(ALL(a));
        int M = N * N;
        REP(i, N) FOR(j, i + 1, N - 1) {
            auto di = i * N + j; // a[i] < a[j]
            dp[i][j][di] = 2;
        }
        REP(i, N) FOR(j, 0, i - 2) FOR(k, j + 1, i - 1) REP(mindi, M) {
            int j2 = mindi / N;
            int k2 = mindi % N;
            if (a[k2] <= a[j2]) continue;
            ll mind = min(a[k2] - a[j2], a[i] - a[k]);
            ll maxd = a[i] - a[j];
            if (maxd <= S * mind) {
                auto mindi2 = mindi;
                if (a[i] - a[k] < a[k2] - a[j2]) mindi2 = k * N + i;
                dp[j][i][mindi2] = max(dp[j][i][mindi2], dp[j][k][mindi] + 1);
            }
        }
        int ret = 2;
        REP(i, N) FOR(j, i + 1, N - 1) REP(mindi, M) {
            ret = max(ret, dp[i][j][mindi]);
        }
        return ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int aARRAY[] = {504727104, 918416318, 708134056, 247352073, 913757300, 46583415, 294217385, 300060796, 318348305, 767577048, 795855561, 813068529, 522078490, 280800289, 516131708, 851500733, 131145455, 901087057, 158809899, 483375703, 625532534, 184139340, 166710286, 635698045, 534674661, 291103492, 903591874, 571474470, 810870273, 598468852, 554679266};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        CliqueParty theObject;
        eq(0, theObject.maxsize(a, 500801731),31);
    }
    {
        int aARRAY[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        CliqueParty theObject;
        eq(0, theObject.maxsize(a, 2),3);
    }
    {
        int aARRAY[] = {1,2,3};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        CliqueParty theObject;
        eq(0, theObject.maxsize(a, 2),3);
    }
    {
        int aARRAY[] = {1,2,3};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        CliqueParty theObject;
        eq(1, theObject.maxsize(a, 1),2);
    }
    {
        int aARRAY[] = {4,10,5,6};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        CliqueParty theObject;
        eq(2, theObject.maxsize(a, 2),3);
    }
    {
        int aARRAY[] = {1,2,3,4,5,6};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        CliqueParty theObject;
        eq(3, theObject.maxsize(a, 3),4);
    }
    {
        int aARRAY[] = {10,9,25,24,23,30};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        CliqueParty theObject;
        eq(4, theObject.maxsize(a, 7),4);
    }
    return 0;
}
// END CUT HERE
