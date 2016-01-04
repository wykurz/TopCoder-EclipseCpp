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

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define REP(k, a) for (int k = 0; k < (a); ++k)

template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

constexpr size_t MAX_V = 51;
constexpr size_t MAX_E = 2 * MAX_V - 1 + 2;

double dp[MAX_V][MAX_E][MAX_E];
double ff[MAX_E][MAX_E];

class DiameterOfRandomTree {
public:
    double getExpectation(vector <int> a, vector <int> b)
    {
    	ZERO(dp);
    	const int n = a.size();
    	const int m = 2 * n + 1;
    	for (int x = 0; x < n + 1; ++x) {
    		dp[x][0][0] = 1.0;
    	}
    	auto add = [&](int x, int y) {
    		ZERO(ff);
    		REP(l1, m) REP(d1, m) {
    			if (dp[x][l1][d1] < 1e-12) continue;
    			REP(l2, m) REP(d2, m) {
    				FOR(s, 1, 2) {
    					int l = max(l1, l2 + s);
    					int d = max(max(d1, d2), l1 + l2 + s);
    					ff[l][d] += 0.5 * dp[x][l1][d1] * dp[y][l2][d2];
    				}
    			}
    		}
    		COPY2D(ff, dp[x]);
    	};
    	vector<bool> v(n, false);
    	function<void(int)> dfs = [&](int x) -> void {
    		v[x] = true;
    		REP(i, n) if (x == a[i] || x == b[i]) {
    			int y = a[i] != x ? a[i] : b[i];
    			if (v[y]) continue;
    			dfs(y);
    			add(x, y);
    		}
        	// printNode(x);
    	};
    	dfs(0);
    	double ret = 0;
    	REP(l, m) REP(d, m) ret += dp[0][l][d] * max(l, d);
    	return ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int aARRAY[] = {0,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(7, theObject.getExpectation(a, b),3.0);
    }
    {
        int aARRAY[] = {0,1,2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(5, theObject.getExpectation(a, b),4.5);
    }
    {
        int aARRAY[] = {0,1,2,3};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(0, theObject.getExpectation(a, b),6.0);
    }
    {
        int aARRAY[] = {0,0};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(6, theObject.getExpectation(a, b),3.0);
    }
    {
        int aARRAY[] = {0,0,0};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(1, theObject.getExpectation(a, b),3.375);
    }
    {
        int aARRAY[] = {0,0,0,1,4};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,5};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(2, theObject.getExpectation(a, b),6.25);
    }
    {
        int aARRAY[] = {0,0,0,0,0,0,0,0};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,5,6,7,8};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(3, theObject.getExpectation(a, b),3.9609375);
    }
    {
        int aARRAY[] = {0,0,0,1,2,3,5,6,8};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,5,6,7,8,9};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(4, theObject.getExpectation(a, b),10.53125);
    }
    return 0;
}
// END CUT HERE
