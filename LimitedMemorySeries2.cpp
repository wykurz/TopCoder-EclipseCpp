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

constexpr ll mod = 1e9 + 7;
// constexpr int N = 1e7 + 1;
constexpr int N = 20;
// constexpr int K = 400;
constexpr int K = 3;
constexpr int L = N / K + 1;

class LimitedMemorySeries2 {
public:

    ll pmax1v[L] = {-1};
    int pmax1i[L] = {-1};

    ll pmax2v[K] = {-1};
    int pmax2i[K] = {-1};

    int getSum(int N, long long x0, long long a, long long b)
    {
        auto next = [=](ll prev_) {
            // return ((prev_ ^ a) + b) & (PW(50) - 1);
            return (prev_ + 1) % 5;
        };

        auto nextr = [=](ll prev_) {
            // return ((prev_ ^ a) + b) & (PW(50) - 1);
            return (prev_ - 1 + 5) % 5;
        };

        auto funcs = make_tuple(next, nextr);

        ll curr = x0;
        FOR(i, 1, N - 1) curr = next(curr);
        ll last = curr; // TODO

        pmax1v[0] = x0;
        pmax1i[0] = 0;
        pmax2v[0] = x0;
        pmax2i[0] = 0;
        ll ret = 0;

        int pm1i = 0;
        int pm2i = 0;
        curr = x0;
        FOR(i, 1, N - 1) {
            ll prev = curr;
            curr = next(prev);
            pm2i = min(i % K, pm2i + 1);
            while (0 < pm2i && pmax2v[pm2i - 1] < curr) --pm2i;
            pmax2v[pm2i] = curr;
            pmax2i[pm2i] = i;
            if (0 < pm2i) {
                ret += i - pmax2i[pm2i - 1] - 1;
                continue;
            }
            pm1i = min(i / K, pm1i + 1);
            // We know we're max in current bucket.
            while (0 < pm1i && pmax1v[pm1i - 1] < curr) --pm1i;
            pmax1v[pm1i] = curr;
            pmax1i[pm1i] = i;
            if (0 < pm1i) {
                int mv = pmax1v[pm1i - 1];
                int mi = pmax1i[pm1i - 1];
                int lmi = mi;
                REP(j, 2 * K) {
                    if (i <= mi) break;
                    if (curr <= mv) lmi = mi;
                    mv = next(mv);
                    ++mi;
                }
                ret += i - lmi - 1;
                continue;
            }
            ret += i;
        }
        return ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        LimitedMemorySeries2 theObject;
        eq(0, theObject.getSum(10, 0L, 0L, 0L), 20);
    }

//    {
//        LimitedMemorySeries2 theObject;
//        eq(0, theObject.getSum(10, 0L, 0L, 0L), 16);
//    }

//    {
//        LimitedMemorySeries2 theObject;
//        eq(0, theObject.getSum(6, 2L, 23L, 1L),2);
//    }
//    {
//        LimitedMemorySeries2 theObject;
//        eq(1, theObject.getSum(100, 0L, 0L, 1L),0);
//    }
//    {
//        LimitedMemorySeries2 theObject;
//        eq(2, theObject.getSum(234234, 1125899906842623L, 123456789123456L, 987654321549687L),1144970);
//    }
//    {
//        LimitedMemorySeries2 theObject;
//        eq(3, theObject.getSum(10000000, 12345678912345L, 98765094309812L, 34893049812392L),65420804);
//    }
    return 0;
}
// END CUT HERE
