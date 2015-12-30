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

class WaterTank {
public:
    double minOutputRate(vector <int> t, vector <int> x, int C)
    {
    	int n = t.size();
    	auto f = [t, x, C, n](double r) {
    		double c = 0;
    		for (int i = 0; i < n; ++i) {
    			double er = x[i] - r;
    			c += t[i] * er;
    			if (C < c) return false;
    			c = max(0.0, c);
    		}
    		return c <= C;
    	};
    	const double D = 1e-9;
    	double r = 1e7;
    	double d = 1e7;
    	while (D < d && !(f(r) && !f(r - D))) {
    		if (f(r - d)) r -= d;
    		else d /= 2;
    	}
    	return max(0.0, r);
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int tARRAY[] = {3,3};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        int xARRAY[] = {1,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        WaterTank theObject;
        eq(0, theObject.minOutputRate(t, x, 3),0.9999999999999999);
    }
	{
        int tARRAY[] = {1,2,3,4,5};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        int xARRAY[] = {5,4,3,2,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        WaterTank theObject;
        eq(1, theObject.minOutputRate(t, x, 10),1.9999999999999996);
    }
    {
        int tARRAY[] = {5949,3198,376,3592,4019,3481,5609,3840,6092,4059};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        int xARRAY[] = {29,38,96,84,10,2,39,27,76,94};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        WaterTank theObject;
        eq(2, theObject.minOutputRate(t, x, 1000000000),0.0);
    }
    {
        int tARRAY[] = {9,3,4,8,1,2,5,7,6};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        int xARRAY[] = {123,456,789,1011,1213,1415,1617,1819,2021};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        WaterTank theObject;
        eq(3, theObject.minOutputRate(t, x, 11),2019.1666666666665);
    }
    {
        int tARRAY[] = {100};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        int xARRAY[] = {1000};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        WaterTank theObject;
        eq(4, theObject.minOutputRate(t, x, 12345),876.55);
    }
    return 0;
}
// END CUT HERE
