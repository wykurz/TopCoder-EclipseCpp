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
#define REP(k, a) for (int k = 0; k < (a); ++k)

class AlmostFibonacciKnapsack {
public:

    ll f(int n)
    {
        array<ll, 2> w = {2, 3};
        REP(i, n) {
            auto tmp = w[1];
            w[1] = w[0] + w[1] - 1;
            w[0] = tmp;
        }
        return w[0];
    }

    int g(ll x, int maxi)
    {
        array<ll, 2> w = {2, 3};
        int i = 0;
        ll y = w[0];
        while (i < maxi && w[1] <= x) {
            y += w[1];
            auto tmp = w[1];
            w[1] = w[0] + w[1] - 1;
            w[0] = tmp;
            ++i;
        }
        if (x < w[0] || y < x) return -1;
        return i;
    }

    vector<int> h(ll x, int maxi = 93)
    {
        if (0 == x) return {};
        while (0 <= maxi) {
            // cerr << x << " " << maxi << endl;
            auto i = g(x, maxi);
            if (-1 == i) {
                --maxi;
                continue;
            }
            auto res = h(x - f(i), i - 1);
            if (res != vector<int>{-2}) {
                res.push_back(i);
                return res;
            }
            --maxi;
        }
        return {-2};
    }

    vector <int> getIndices(long long x)
    {
        auto res = h(x);
        REP(i, res.size()) res[i] += 1;
        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int retrunValueARRAY[] = {2, 11};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        AlmostFibonacciKnapsack theObject;
        eq(0, theObject.getIndices(148L),retrunValue);
    }
    {
        int retrunValueARRAY[] = {1 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        AlmostFibonacciKnapsack theObject;
        eq(1, theObject.getIndices(2L),retrunValue);
    }
    {
        int retrunValueARRAY[] = {3, 5};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        AlmostFibonacciKnapsack theObject;
        eq(2, theObject.getIndices(13L),retrunValue);
    }
    {
        int retrunValueARRAY[] = {2 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        AlmostFibonacciKnapsack theObject;
        eq(3, theObject.getIndices(3L),retrunValue);
    }
    {
        int retrunValueARRAY[] = {3, 14, 15, 9, 26, 53, 5, 8 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        AlmostFibonacciKnapsack theObject;
        eq(4, theObject.getIndices(86267769395L),retrunValue);
    }
    return 0;
}
// END CUT HERE
