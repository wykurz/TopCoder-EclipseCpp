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

class LengthUnitCalculator {
public:
	using Map = map<string, double>;
	bool f(Map& m)
	{
		Map m2;
		for (const auto& kv: m) {
			const auto& u = kv.first;
			const auto& v = kv.second;
			m2[u] = v;
			if (u == "ft") m2["in"] = 12 * v;
			if (u == "in") m2["ft"] = (1.0 / 12) * v;
			if (u == "yd") m2["ft"] = 3 * v;
			if (u == "ft") m2["yd"] = (1.0 / 3) * v;
			if (u == "mi") m2["yd"] = 1760 * v;
			if (u == "yd") m2["mi"] = (1.0 / 1760) * v;
		}
		if (m.size() == m2.size()) {
			return true;
		}
		swap(m, m2);
		return false;
	}

	double calc(int amount, string fromUnit, string toUnit)
    {
		Map m;
		m[fromUnit] = amount;
		while (!f(m)) {}
    	return m[toUnit];
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        LengthUnitCalculator theObject;
        eq(0, theObject.calc(1, "mi", "ft"),5280.0);
    }
    {
        LengthUnitCalculator theObject;
        eq(1, theObject.calc(1, "ft", "mi"),1.893939393939394E-4);
    }
    {
        LengthUnitCalculator theObject;
        eq(2, theObject.calc(123, "ft", "yd"),41.0);
    }
    {
        LengthUnitCalculator theObject;
        eq(3, theObject.calc(1000, "mi", "in"),6.336E7);
    }
    {
        LengthUnitCalculator theObject;
        eq(4, theObject.calc(1, "in", "mi"),1.5782828282828283E-5);
    }
    {
        LengthUnitCalculator theObject;
        eq(5, theObject.calc(47, "mi", "mi"),47.0);
    }
    return 0;
}
// END CUT HERE
