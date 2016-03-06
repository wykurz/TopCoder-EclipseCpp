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

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FILL1D(a, v) std::fill_n(a, sizeof(a) / sizeof(a[0]), v)
#define FILL2D(a, v) std::fill_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), v)
#define FILL3D(a, v) std::fill_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), v)
#define FILL4D(a, v) std::fill_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), v)
#define COPY1D(a, b) std::copy_n(a, sizeof(a) / sizeof(a[0]), b)
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])
#define COPY3D(a, b) std::copy_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), &b[0][0][0])
#define COPY4D(a, b) std::copy_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), &b[0][0][0][0])
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
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

class FiringEmployees {
public:
    int fire(vector <int> m, vector <int> s, vector <int> p)
    {
        int N = m.size();
        vector<ll> v(N + 1);
        REP(i, N) v[i + 1] = p[i] - s[i];
        function<ll(int)> f = [&](int i) {
            REP(j, N) {
                if (i == m[j]) v[i] += f(j + 1);
            }
            return max(ll(0), v[i]);
        };
        return f(0);
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int managerARRAY[] = {0,1};
        vector <int> manager( managerARRAY, managerARRAY+ARRSIZE(managerARRAY) );
        int salaryARRAY[] = {1,10};
        vector <int> salary( salaryARRAY, salaryARRAY+ARRSIZE(salaryARRAY) );
        int productivityARRAY[] = {5,5};
        vector <int> productivity( productivityARRAY, productivityARRAY+ARRSIZE(productivityARRAY) );
        FiringEmployees theObject;
        eq(2, theObject.fire(manager, salary, productivity),4);
    }
    {
        int managerARRAY[] = {0,0,0};
        vector <int> manager( managerARRAY, managerARRAY+ARRSIZE(managerARRAY) );
        int salaryARRAY[] = {1,2,3};
        vector <int> salary( salaryARRAY, salaryARRAY+ARRSIZE(salaryARRAY) );
        int productivityARRAY[] = {3,2,1};
        vector <int> productivity( productivityARRAY, productivityARRAY+ARRSIZE(productivityARRAY) );
        FiringEmployees theObject;
        eq(0, theObject.fire(manager, salary, productivity),2);
    }
    {
        int managerARRAY[] = {0,1,2,3};
        vector <int> manager( managerARRAY, managerARRAY+ARRSIZE(managerARRAY) );
        int salaryARRAY[] = {4,3,2,1};
        vector <int> salary( salaryARRAY, salaryARRAY+ARRSIZE(salaryARRAY) );
        int productivityARRAY[] = {2,3,4,5};
        vector <int> productivity( productivityARRAY, productivityARRAY+ARRSIZE(productivityARRAY) );
        FiringEmployees theObject;
        eq(1, theObject.fire(manager, salary, productivity),4);
    }
    {
        int managerARRAY[] = {0,1,2,1,2,3,4,2,3};
        vector <int> manager( managerARRAY, managerARRAY+ARRSIZE(managerARRAY) );
        int salaryARRAY[] = {5,3,6,8,4,2,4,6,7};
        vector <int> salary( salaryARRAY, salaryARRAY+ARRSIZE(salaryARRAY) );
        int productivityARRAY[] = {2,5,7,8,5,3,5,7,9};
        vector <int> productivity( productivityARRAY, productivityARRAY+ARRSIZE(productivityARRAY) );
        FiringEmployees theObject;
        eq(3, theObject.fire(manager, salary, productivity),6);
    }
    {
        int managerARRAY[] = {0,0,1,1,2,2};
        vector <int> manager( managerARRAY, managerARRAY+ARRSIZE(managerARRAY) );
        int salaryARRAY[] = {1,1,1,2,2,2};
        vector <int> salary( salaryARRAY, salaryARRAY+ARRSIZE(salaryARRAY) );
        int productivityARRAY[] = {2,2,2,1,1,1};
        vector <int> productivity( productivityARRAY, productivityARRAY+ARRSIZE(productivityARRAY) );
        FiringEmployees theObject;
        eq(4, theObject.fire(manager, salary, productivity),3);
    }
    return 0;
}
// END CUT HERE
