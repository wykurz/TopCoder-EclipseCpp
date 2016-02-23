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
using ll = long long;
#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define PW(x) (1ll << (x))
#define BCNT(x) __builtin_popcountll(x)

constexpr int L = 2000;
constexpr int M = 2000 / 64 + 1;
ll G[L][M] = {};
ll H[L] = {};

class SmilesTheFriendshipUnicorn {
public:
    string ret(bool ex)
    {
        return ex ? "Yay!" : ":(";
    }
    string hasFriendshipChain(int N, vector <int> A, vector <int> B)
    {
        ZERO(G);
        ZERO(H);
        int E = A.size();
        REP(i, E) {
            G[A[i]][B[i] / 64] |= PW(B[i] % 64);
            G[B[i]][A[i] / 64] |= PW(A[i] % 64);
        }
        REP(i, N) {
            int cnt = 0;
            REP(j, M) cnt += BCNT(G[i][j]);
            if (1 < cnt) {
                // cerr << i << " ok" << endl;
                H[i] = true;
            }
        }
        REP(i, N) {
            if (!H[i]) continue;
            FOR(j, i + 1, N - 1) {
                if (!H[j]) continue;
                ll tmpi = G[i][j / 64];
                G[i][j / 64] &= ~PW(j % 64);
                ll tmpj = G[j][i / 64];
                G[j][i / 64] &= ~PW(i % 64);
                int mid = 0;
                int leafi = 0;
                int leafj = 0;
                REP(k, M) {
                    mid += BCNT(G[i][k] & G[j][k]);
                    leafi += BCNT(G[i][k] & ~G[j][k]);
                    leafj += BCNT(G[j][k] & ~G[i][k]);
                }
                if (1 <= mid && 2 <= leafi + mid && 2 <= leafj + mid) {
                    // cerr << i << " " << j << " " << mid << " " << leafi << " " << leafj << endl;
                    return ret(true);
                }
                G[i][j / 64] = tmpi;
                G[j][i / 64] = tmpj;
            }
        }
        return ret(false);
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int AARRAY[] = {0, 1, 2, 3, 1};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {1, 2, 3, 0, 4};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        SmilesTheFriendshipUnicorn theObject;
        eq(1, theObject.hasFriendshipChain(5, A, B),"Yay!");
    }
    {
        int AARRAY[] = {0, 0, 1, 1, 1};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {1, 2, 2, 3, 4};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        SmilesTheFriendshipUnicorn theObject;
        eq(0, theObject.hasFriendshipChain(5, A, B),":(");
    }

    {
        int AARRAY[] = {0, 1, 2, 3};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {1, 2, 3, 4};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        SmilesTheFriendshipUnicorn theObject;
        eq(0, theObject.hasFriendshipChain(5, A, B),"Yay!");
    }
    {
        int AARRAY[] = {0, 0, 0, 0, 0};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {1, 2, 3, 4, 5};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        SmilesTheFriendshipUnicorn theObject;
        eq(2, theObject.hasFriendshipChain(6, A, B),":(");
    }
    {
        int AARRAY[] = {1, 3, 4, 3, 4, 3, 0, 2};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {7, 7, 7, 4, 6, 5, 4, 7};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        SmilesTheFriendshipUnicorn theObject;
        eq(3, theObject.hasFriendshipChain(8, A, B),"Yay!");
    }
    {
        int AARRAY[] = {0, 1, 1, 5, 4, 5};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {5, 2, 3, 6, 1, 1};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        SmilesTheFriendshipUnicorn theObject;
        eq(4, theObject.hasFriendshipChain(7, A, B),":(");
    }
    {
        int AARRAY[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41}
           ;
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 0};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        SmilesTheFriendshipUnicorn theObject;
        eq(5, theObject.hasFriendshipChain(42, A, B),"Yay!");
    }
    return 0;
}
// END CUT HERE
