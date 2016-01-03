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
#define FILL1D(a, v) std::fill_n(a, sizeof(a) / sizeof(a[0]), v);
#define FILL2D(a, v) std::fill_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), v);
#define FILL3D(a, v) std::fill_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), v);
#define FILL4D(a, v) std::fill_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), v);
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

double dd[50][101];
double ee[50][101];
double ff[101];

class DiameterOfRandomTree {
public:
    double getExpectation(vector <int> a, vector <int> b)
    {
    	ZERO(ee);
    	ZERO(dd);
    	const int n = a.size();
    	for (int x = 0; x < n + 1; ++x) {
    		dd[x][0] = 1.0;
    		ee[x][0] = 1.0;
    	}
    	auto printNode = [&](int x) {
    		for (int l = 0; l <= 2 * n; ++l)
    			cerr << "dd[" << x << "][" << l << "] = " << dd[x][l] << "\n";
    		cerr << "\n";
    		for (int l = 0; l <= 2 * n; ++l)
    			cerr << "ee[" << x << "][" << l << "] = " << ee[x][l] << "\n";
    		cerr << "===================================" << endl;
    	};
    	auto printAll = [&]() {
    		for (int x = 0; x <= n; ++x) {
    			printNode(x);
    		}
    	};
    	auto csum = [&](int x) {
			for (int l = 1; l <= 2 * n; ++l) {
				dd[x][l] += dd[x][l - 1];
				ee[x][l] += ee[x][l - 1];
			}
    	};
    	auto diff = [&](int x) {
			for (int l = 2 * n; 1 <= l; --l) {
				dd[x][l] -= dd[x][l - 1];
				ee[x][l] -= ee[x][l - 1];
			}
    	};
    	auto pmax = [&](int x, int y) {
    		csum(x); csum(y);
			for (int l = 0; l <= 2 * n; ++l)
				dd[x][l] *= dd[y][l];
			diff(x); diff(y);
    	};
    	auto psum = [&](int x, int y) {
    		ZERO(ff);
    		for (int l = 0; l <= 2 * n; ++l) {
    			for (int l1 = 0; l1 <= l; ++l1) {
    				int l2 = l - l1;
    				ff[l] += dd[x][l1] * dd[y][l2];
    			}
    		}
    		for (int l = 1; l <= 2 * n; ++l)
    			ff[l] += ff[l - 1];
    		csum(x);
			for (int l = 0; l <= 2 * n; ++l)
				ee[x][l] *= ff[l];
			diff(x);
    	};
    	auto pext = [&](int y) {
    		ff[0] = 0;
			for (int l = 1; l <= 2 * n; ++l) {
				ff[l] = 0.5 * dd[y][l - 1];
			}
			for (int l = 2; l <= 2 * n; ++l) {
				ff[l] += 0.5 * dd[y][l - 2];
			}
			for (int l = 0; l <= 2 * n; ++l) {
				dd[y][l] = ff[l];
			}
    	};
    	vector<bool> v(n, false);
    	function<void(int)> dfs = [&](int x) -> void {
    		v[x] = true;
    		vector<int> t;
    		for (int i = 0; i < n; ++i) {
    			if (x == a[i] || x == b[i]) {
    				int y = a[i] != x ? a[i] : b[i];
    				if (v[y]) continue;
    				t.push_back(y);
    				dfs(y);
    			}
    		}
    		printNode(x);
    		for (int y : t)	{
    			pext(y);
    			// printNode(y);
    		}
        	for (int i = 0; i < t.size(); ++i) {
        		psum(x, t[i]);
        		pmax(x, t[i]);
        		printNode(x);
    		}
        	printNode(x);
    	};
    	dfs(0);
    	double ret = 0;
    	for (int x = 0; x <= n; ++x) {
    		double rx = 0;
    		for (int l = 0; l <= 2 * n; ++l)
    			rx += l * ee[x][l];
    		chmax(ret, rx);
    	}
    	return ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
//    {
//        int aARRAY[] = {0,1,2};
//        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
//        int bARRAY[] = {1,2,3};
//        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
//        DiameterOfRandomTree theObject;
//        eq(5, theObject.getExpectation(a, b),4.5);
//    }
//    {
//        int aARRAY[] = {0,1,2,3};
//        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
//        int bARRAY[] = {1,2,3,4};
//        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
//        DiameterOfRandomTree theObject;
//        eq(0, theObject.getExpectation(a, b),6.0);
//    }
    {
        int aARRAY[] = {0,0};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        DiameterOfRandomTree theObject;
        eq(6, theObject.getExpectation(a, b),3.0);
    }
//    {
//        int aARRAY[] = {0,0,0};
//        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
//        int bARRAY[] = {1,2,3};
//        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
//        DiameterOfRandomTree theObject;
//        eq(1, theObject.getExpectation(a, b),3.375);
//    }
//    {
//        int aARRAY[] = {0,0,0,1,4};
//        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
//        int bARRAY[] = {1,2,3,4,5};
//        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
//        DiameterOfRandomTree theObject;
//        eq(2, theObject.getExpectation(a, b),6.25);
//    }
//    {
//        int aARRAY[] = {0,0,0,0,0,0,0,0};
//        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
//        int bARRAY[] = {1,2,3,4,5,6,7,8};
//        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
//        DiameterOfRandomTree theObject;
//        eq(3, theObject.getExpectation(a, b),3.9609375);
//    }
//    {
//        int aARRAY[] = {0,0,0,1,2,3,5,6,8};
//        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
//        int bARRAY[] = {1,2,3,4,5,6,7,8,9};
//        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
//        DiameterOfRandomTree theObject;
//        eq(4, theObject.getExpectation(a, b),10.53125);
//    }
    return 0;
}
// END CUT HERE
