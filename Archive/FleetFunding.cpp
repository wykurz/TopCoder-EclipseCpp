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
#define ALL(c) (c).begin(),(c).end()

class FleetFunding {
public:
    int maxShips(int M, vector <int> tk, vector <int> ta, vector <int> tb)
    {
        int N = tk.size();
        vector<tuple<int, int, int>> s;
        REP(i, N) {
            int a = ta[i] - 1;
            int b = tb[i] - 1;
            int k = tk[i];
            s.emplace_back(b, a, k);
        }
        sort(ALL(s));
        auto f = [&](int m) {
            auto t(s);
            REP(i, M) {
                int l = m;
                REP(j, N) {
                    int a, b, k;
                    tie(b, a, k) = t[j];
                    if (i < a || b < i) continue;
                    int tmp = min(l, k);
                    l -= tmp;
                    k -= tmp;
                    t[j] = tie(b, a, k);
                }
                if (0 < l) return false;
            }
            return true;
        };
        int x = 0;
        int y = (std::accumulate(ALL(tk), 0)) / M  + 1;
        while (x < y) {
            int z = (x + y) / 2;
            if (z == x || z == y) {
                return x;
            }
            if (f(z)) x = z;
            else y = z;
        }
        return x;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int kARRAY[] = {8947, 367308, 50118, 96466, 887715};
        vector <int> k( kARRAY, kARRAY+ARRSIZE(kARRAY) );
        int aARRAY[] = {149, 91, 1, 2, 82};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2553, 2062, 2576, 2346, 2326};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FleetFunding theObject;
        eq(5, theObject.maxShips(2576, k, a, b),255);
    }
    {
        int kARRAY[] = {2,4,6,8,10,1,3,5,7,9};
        vector <int> k( kARRAY, kARRAY+ARRSIZE(kARRAY) );
        int aARRAY[] = {1,2,3,4,5,6,7,8,9,10};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,5,6,7,8,9,10};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FleetFunding theObject;
        eq(2, theObject.maxShips(10, k, a, b),1);
    }
    {
        int kARRAY[] = {2};
        vector <int> k( kARRAY, kARRAY+ARRSIZE(kARRAY) );
        int aARRAY[] = {1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FleetFunding theObject;
        eq(0, theObject.maxShips(2, k, a, b),1);
    }
    {
        int kARRAY[] = {2,2,2};
        vector <int> k( kARRAY, kARRAY+ARRSIZE(kARRAY) );
        int aARRAY[] = {1,2,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {3,3,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FleetFunding theObject;
        eq(0, theObject.maxShips(3, k, a, b),2);
    }
    {
        int kARRAY[] = {10,9,8,7,6,5,4,3,2,1};
        vector <int> k( kARRAY, kARRAY+ARRSIZE(kARRAY) );
        int aARRAY[] = {1,1,1,1,1,1,1,1,1,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,1,1,1,1,1,1,1,1,1};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FleetFunding theObject;
        eq(1, theObject.maxShips(1, k, a, b),55);
    }

    {
        int kARRAY[] = {374778,169109,529984,498638,29462,465769,29285,394948,307944,459189,
           349316,766627,686851,404285,850199,359378,3014,248257,558856,27393,32370,
           574862,337134,965567,32223,935678,389898,973497,990575,483190,122899,
           857994,991217,149619,415870};
        vector <int> k( kARRAY, kARRAY+ARRSIZE(kARRAY) );
        int aARRAY[] = {92,4997,11,28545,933,210,2,124,114,4513,32959,1,57,17,13,133,1843,41851,
           3,9296,9757,28,3,769,10,11102,683,6173,11821,3982,214,2,4304,439,1998};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {81034,54474,70239,79597,47317,82938,83883,74652,84033,84422,84456,84457,
           81095,83743,79210,84255,84455,45596,84456,82959,67062,80330,44090,84445,
           84454,84450,45931,77190,83025,83567,83639,84333,83355,70982,84456};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FleetFunding theObject;
        eq(3, theObject.maxShips(84457, k, a, b),186);
    }
    {
        int kARRAY[] = {1000000,1000000,1000000,1000000,1000000};
        vector <int> k( kARRAY, kARRAY+ARRSIZE(kARRAY) );
        int aARRAY[] = {1,1,1,2,2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,1,2,2,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        FleetFunding theObject;
        eq(4, theObject.maxShips(2, k, a, b),2500000);
    }
    return 0;
}
// END CUT HERE
