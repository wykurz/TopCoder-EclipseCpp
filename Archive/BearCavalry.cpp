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

using ll = long long;
#define ALL(c) (c).begin(),(c).end()
constexpr int mod = 1000000007;

class BearCavalry {
public:

    int countAssignments(vector <int> ba, vector <int> ha)
    {
    	int b0 = ba[0];
    	vector<int> b(ba.begin() + 1, ba.end());
    	sort(ALL(b));
    	reverse(ALL(b));
    	const int n = ba.size();
    	ll ret = 0;
    	for (int i = 0; i < n; ++i) {
    		int h0 = ha[i];
    		const int L = b0 * h0;
    		vector<int> h;
    		for (int j = 0; j < n; ++j) if (j != i) h.push_back(ha[j]);
    		vector<int> c;
    		for (int bx : b) {
    			int cx = 0;
    			for (int hx : h) if (bx * hx < L) ++cx;
    			c.push_back(cx);
    		}
    		sort(ALL(c));
    		ll w = 1;
    		bool ok = true;
    		for (int j = 0; j < n - 1; ++j) if (c[j] < j + 1) ok = false;
    		if (!ok) continue;
    		for (int j = 0; j < n - 1; ++j) {
    			w *= (c[j] - j);
    			w %= mod;
    		}
    		ret += w;
    		ret %= mod;
    	}
    	return (int) ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int warriorsARRAY[] = {5,8,4,8};
        vector <int> warriors( warriorsARRAY, warriorsARRAY+ARRSIZE(warriorsARRAY) );
        int horsesARRAY[] = {19,40,25,20};
        vector <int> horses( horsesARRAY, horsesARRAY+ARRSIZE(horsesARRAY) );
        BearCavalry theObject;
        eq(0, theObject.countAssignments(warriors, horses),2);
    }
    {
        int warriorsARRAY[] = {1,1};
        vector <int> warriors( warriorsARRAY, warriorsARRAY+ARRSIZE(warriorsARRAY) );
        int horsesARRAY[] = {1,1};
        vector <int> horses( horsesARRAY, horsesARRAY+ARRSIZE(horsesARRAY) );
        BearCavalry theObject;
        eq(1, theObject.countAssignments(warriors, horses),0);
    }
    {
        int warriorsARRAY[] = {10,2,10};
        vector <int> warriors( warriorsARRAY, warriorsARRAY+ARRSIZE(warriorsARRAY) );
        int horsesARRAY[] = {100,150,200};
        vector <int> horses( horsesARRAY, horsesARRAY+ARRSIZE(horsesARRAY) );
        BearCavalry theObject;
        eq(2, theObject.countAssignments(warriors, horses),3);
    }
    {
        int warriorsARRAY[] = {10,20};
        vector <int> warriors( warriorsARRAY, warriorsARRAY+ARRSIZE(warriorsARRAY) );
        int horsesARRAY[] = {1,3};
        vector <int> horses( horsesARRAY, horsesARRAY+ARRSIZE(horsesARRAY) );
        BearCavalry theObject;
        eq(3, theObject.countAssignments(warriors, horses),1);
    }
    {
        int warriorsARRAY[] = {20,20,25,23,24,24,21};
        vector <int> warriors( warriorsARRAY, warriorsARRAY+ARRSIZE(warriorsARRAY) );
        int horsesARRAY[] = {20,25,25,20,25,23,20};
        vector <int> horses( horsesARRAY, horsesARRAY+ARRSIZE(horsesARRAY) );
        BearCavalry theObject;
        eq(4, theObject.countAssignments(warriors, horses),0);
    }
    {
        int warriorsARRAY[] = {970,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
           800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800};
        vector <int> warriors( warriorsARRAY, warriorsARRAY+ARRSIZE(warriorsARRAY) );
        int horsesARRAY[] = {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
           1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
           1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};
        vector <int> horses( horsesARRAY, horsesARRAY+ARRSIZE(horsesARRAY) );
        BearCavalry theObject;
        eq(5, theObject.countAssignments(warriors, horses),318608048);
    }
    return 0;
}
// END CUT HERE
