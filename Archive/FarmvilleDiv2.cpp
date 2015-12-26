// BEGIN CUT HERE

// END CUT HERE
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

// BEGIN CUT HERE
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
class FarmvilleDiv2 {
public:
    int minTime(vector <int> t, vector <int> c, int b)
    {
    	vector<pair<int, int>> p;
    	const int n = t.size();
    	for (int i = 0; i < n; ++i) {
    		p.push_back(make_pair(c[i], t[i]));
    	}
    	sort(p.begin(), p.end());
    	for (auto& tv: p) {
    		int& x = tv.first;
    		int& y = tv.second;
    		int d = min(y, b / x);
    		y -= d;
    		b -= d * x;
    	}
    	return accumulate(p.begin(), p.end(), 0, [](int a, pair<int, int>& tv) { return a + tv.second; });
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int timeARRAY[] = {100};
        vector <int> time( timeARRAY, timeARRAY+ARRSIZE(timeARRAY) );
        int costARRAY[] = {1};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        FarmvilleDiv2 theObject;
        eq(0, theObject.minTime(time, cost, 26),74);
    }
    {
        int timeARRAY[] = {100};
        vector <int> time( timeARRAY, timeARRAY+ARRSIZE(timeARRAY) );
        int costARRAY[] = {1};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        FarmvilleDiv2 theObject;
        eq(1, theObject.minTime(time, cost, 101),0);
    }
    {
        int timeARRAY[] = {2,1};
        vector <int> time( timeARRAY, timeARRAY+ARRSIZE(timeARRAY) );
        int costARRAY[] = {1,1};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        FarmvilleDiv2 theObject;
        eq(2, theObject.minTime(time, cost, 3),0);
    }
    {
        int timeARRAY[] = {1,2,3,4,5};
        vector <int> time( timeARRAY, timeARRAY+ARRSIZE(timeARRAY) );
        int costARRAY[] = {5,4,3,2,1};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        FarmvilleDiv2 theObject;
        eq(3, theObject.minTime(time, cost, 15),6);
    }
    {
        int timeARRAY[] = {100,100,100,100,100,100,100,100,100,100};
        vector <int> time( timeARRAY, timeARRAY+ARRSIZE(timeARRAY) );
        int costARRAY[] = {2,4,6,8,10,1,3,5,7,9};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        FarmvilleDiv2 theObject;
        eq(4, theObject.minTime(time, cost, 5000),50);
    }
    {
        int timeARRAY[] = {30,40,20,10};
        vector <int> time( timeARRAY, timeARRAY+ARRSIZE(timeARRAY) );
        int costARRAY[] = {10,20,30,40};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        FarmvilleDiv2 theObject;
        eq(5, theObject.minTime(time, cost, 5),100);
    }
    return 0;
}
// END CUT HERE
