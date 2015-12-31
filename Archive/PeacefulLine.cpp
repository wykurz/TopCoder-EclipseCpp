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

class PeacefulLine {
public:
    string makeLine(vector <int> x)
    {
    	bool ok = true;
    	int n = x.size();
    	int h = (n + 1) / 2;
    	for (int a: x) {
    		int c = 0;
    		for (int b: x) {
    			if (a == b) {
    				++c;
    			}
    		}
    		if (h < c) {
    			ok = false;
    			break;
    		}
    	}
    	return ok ? "possible" : "impossible";
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int xARRAY[] = {25,12,3,25,25,12,12,12,12,3,25};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        PeacefulLine theObject;
        eq(5, theObject.makeLine(x),"possible");
    }
    {
        int xARRAY[] = {1,2,3,4};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        PeacefulLine theObject;
        eq(0, theObject.makeLine(x),"possible");
    }
    {
        int xARRAY[] = {1,1,1,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        PeacefulLine theObject;
        eq(1, theObject.makeLine(x),"impossible");
    }
    {
        int xARRAY[] = {1,1,2,2,3,3,4,4};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        PeacefulLine theObject;
        eq(2, theObject.makeLine(x),"possible");
    }
    {
        int xARRAY[] = {3,3,3,3,13,13,13,13};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        PeacefulLine theObject;
        eq(3, theObject.makeLine(x),"possible");
    }
    {
        int xARRAY[] = {3,7,7,7,3,7,7,7,3};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        PeacefulLine theObject;
        eq(4, theObject.makeLine(x),"impossible");
    }
    {
        int xARRAY[] = {3,3,3,3,13,13,13,13,3};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        PeacefulLine theObject;
        eq(6, theObject.makeLine(x),"possible");
    }
    return 0;
}
// END CUT HERE
