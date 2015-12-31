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

const int dd[] = {1, 0, -1, 0};

class DoubleOrOneEasy {
public:
	int f(int x, int x2)
	{
		int ret = 0;
		while (2 * x <= x2) {
			if (x2 & 1) x2 -= 1;
			else x2 /= 2;
			++ret;
		}
		ret += x2 - x;
		return ret;
	}
	int g(int x, int mp)
	{
		int ret = 0;
		while (0 < x && 0 < mp) {
			if (x & 1) x -= 1;
			else {
				x /= 2;
				--mp;
			}
			++ret;
		}
		ret += x;
		ret += mp;
		return ret;
	}
    int minimalSteps(int a_, int b_, int a2_, int b2_)
    {
    	int a = a_;
    	int b = b_;
    	int a2 = a2_;
    	int b2 = b2_;
    	if (b < a) {
    		swap(a, b);
    		swap(a2, b2);
    	}
    	if (b2 < a2) return -1;
    	if (a2 < a || b2 < b) return -1;
    	if (a == b) {
    		if (a2 != b2) return -1;
    		return f(a, a2);
    	}
    	// a2 = ((((a + i1) * 2^j1 + i2) * 2^j2 + i3) * 2^j3 + ... + in) * 2^jn
    	// b2 = ((((b + i1) * 2^j1 + i2) * 2^j2 + i3) * 2^j3 + ... + in) * 2^jn
    	// x2 = x * 2^(j1 + ... + jn) + i1 * 2^(j1 + ... + jn) + ... + in * 2^jn
    	// b2 - a2 = (b - a) * 2^(j1 + ... + jn)
    	int d = b - a;
    	int d2 = b2 - a2;
    	if (d2 % d != 0) return -1;
    	int m = d2 / d;
    	if (a2 < a * m) return -1;
    	if (a2 - a * m != b2 - b * m) return -1;
    	int pw = 0;
    	while (PW(pw) < m) ++pw;
    	if (PW(pw) != m) return -1;
    	return g(a2 - a * m, pw);
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        DoubleOrOneEasy theObject;
        eq(9, theObject.minimalSteps(100, 100, 1, 1),-1);
    }
    {
        DoubleOrOneEasy theObject;
        eq(9, theObject.minimalSteps(1, 2, 8, 16),3);
    }
    {
        DoubleOrOneEasy theObject;
        eq(6, theObject.minimalSteps(100, 200, 399, 799),-1);
    }
    {
        DoubleOrOneEasy theObject;
        eq(5, theObject.minimalSteps(1, 111111111, 8, 888888888),3);
    }
    {
        DoubleOrOneEasy theObject;
        eq(7, theObject.minimalSteps(100, 200, 499, 899), 28);
    }
    {
        DoubleOrOneEasy theObject;
        eq(4, theObject.minimalSteps(1, 111111111, 9, 999999999),-1);
    }
//    {
//        DoubleOrOneEasy theObject;
//        eq(0, theObject.minimalSteps(112, 12, 61336, 35736), 182);
//    }
    {
        DoubleOrOneEasy theObject;
        eq(8, theObject.minimalSteps(10, 15, 40, 50), 11);
    }
    {
        DoubleOrOneEasy theObject;
        eq(3, theObject.minimalSteps(15, 10, 50, 40), 11);
    }
    {
        DoubleOrOneEasy theObject;
        eq(0, theObject.minimalSteps(100, 1000, 101, 1001),1);
    }
    {
        DoubleOrOneEasy theObject;
        eq(1, theObject.minimalSteps(100, 1000, 202, 2002),2);
    }
    {
        DoubleOrOneEasy theObject;
        eq(2, theObject.minimalSteps(2, 2, 1, 1),-1);
    }
    return 0;
}
// END CUT HERE
