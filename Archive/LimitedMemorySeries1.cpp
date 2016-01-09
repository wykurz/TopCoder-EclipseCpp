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

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define PW(x) (1ll << (x))
#define ALL(c) (c).begin(),(c).end()

class LimitedMemorySeries1 {
public:
    long long getSum(int n, int x0, int a, int b, vector <int> query)
    {
    	auto next = [&](int prev) {
    		ll c = prev;
    		return (int) ((c * a + b) % 1000000007);
    	};
    	constexpr int N = 1000000007;
    	constexpr int M = PW(18);
    	constexpr int B = N / M + 1;
    	int t[M] = {};
    	ll c = x0;
    	for (int i = 0; i < n; ++i) {
    		++t[c / B];
    		c = next(c);
    	}
    	for (int i = 1; i < M; ++i) t[i] += t[i - 1];
    	auto f = [&](int q) {
    		auto it = upper_bound(t, t + M, q);
    		assert(it != t + M);
    		if (it == t) return 0;
    		int i = distance(t, it);
    		if (q < *(it - 1)) return i - 1;
    		assert(it != t + M);
    		return i;
    	};
    	constexpr int W = 10;
		sort(ALL(query));
		int Q = query.size();
    	vector<vector<int>> qq((Q + W - 1) / W, vector<int>());
    	for (int i = 0; i < Q; ++i) qq[i / W].push_back(query[i]);
    	ll ret = 0;
    	for (auto& qb : qq) {
    		int u[W][B] = {};
    		set<int> idxset;
    		for (int q : qb) idxset.insert(f(q));
    		int r[W] = {};
    		int p[W] = {};
    		int h[W] = {};
    		int L = 0;
    		for (int idx : idxset) {
    			r[L] = idx ? t[idx - 1] : 0;
    			p[L] = t[idx];
    			h[L++] = (idx + 1) * B;
    		}
    		c = x0;
    		for (int i = 0; i < n; ++i, c = next(c)) {
    			auto it = upper_bound(h, h + L, c);
    			if (it == h + L) continue;
    			int j = distance(h, it);
    			if (c - h[j] + B < 0) continue;
    			++u[j][c - h[j] + B];
    		}
    		int i = 0;
    		for (int q : qb) {
    			while (i < L && p[i] <= q) ++i;
    			assert(i < L && q < p[i]);
    			int s = -1;
    			int w = q - r[i];
    			while (-1 < w) if (u[i][++s]) w -= u[i][s];
    			assert(s < B);
    			ret += (ll)(h[i] - B) + s;
    		}
    	}
    	return ret;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int queryARRAY[] = {928975, 2337421, 625830, 2782775, 1898605, 3610720, 2007834, 2520480, 854049, 2947327, 1565908, 2936121, 1673359, 3007937, 2077809, 4369908, 1233217, 60731, 1438429, 236364, 2798689, 636327, 4280277, 4047893, 3757752, 3509852, 446979, 4258707, 1293288, 1537333, 2923050, 2368166, 3322603, 3772727, 4187081, 4829314, 2215225, 307260, 4261761, 2315791, 3886278, 4819149, 4282614, 1796015, 1592589, 3714155, 3443160, 4308734, 2779749, 1459464, 2716620, 1379422, 1540849, 2711264, 4090151, 3787369, 1187683, 4476734, 4439765, 4784434, 2409211, 2718029, 3698076, 576160, 2748820, 1575818, 3613972, 1736099, 4611152, 4797081, 2666175, 3995732, 3785228, 1905475, 355235, 4367701, 4080824, 3693594, 2109486, 3623045, 757140, 3493284, 2434951, 2263034, 2394113, 2073975, 2467967, 4423563, 4736391, 1413957, 192774, 4676740, 2098281, 255412, 3365697, 4872467, 4337834, 2122209, 155552, 227019};
        vector <int> query( queryARRAY, queryARRAY+ARRSIZE(queryARRAY) );
        LimitedMemorySeries1 theObject;
        eq<ll>(4, theObject.getSum(4999997, 0, 0, 0, query),0L);
    }
    {
        int queryARRAY[] = {0, 1, 2, 3, 4};
        vector <int> query( queryARRAY, queryARRAY+ARRSIZE(queryARRAY) );
        LimitedMemorySeries1 theObject;
        eq<ll>(3, theObject.getSum(5, 2, 1, 0, query),10L);
    }
    {
        int queryARRAY[] = {0,3};
        vector <int> query( queryARRAY, queryARRAY+ARRSIZE(queryARRAY) );
        LimitedMemorySeries1 theObject;
        eq<ll>(0, theObject.getSum(5, 100, 1, 5, query),215L);
    }
    {
        int queryARRAY[] = {0,1,2,3};
        vector <int> query( queryARRAY, queryARRAY+ARRSIZE(queryARRAY) );
        LimitedMemorySeries1 theObject;
        eq<ll>(1, theObject.getSum(5, 123456789, 987654321, 1000000006, query),733028692L);
    }
    {
        int queryARRAY[] = {4854010,3139503,1855546,219904,846357,2624639,891260,217467,4940091,4802760,2424821,424076,
            3848272,2062765,2922407,4850301,1279972,4929307,2035456,3562859,1749594,4089499,3797495,1013980,
            1650805,1245213,3020379,4661668,427170,1176815,292944,2435328,420809,4170355,2635197,3940607,
            4311718,2098572,4868054,30319,4588969,1460677,1335028,3921495,3621970,4459335,966000,3686977,
            2316560,1634961,2280624,1940395,3321546,3168811,1856547,3859093,4340475,1382782,3482928,2517843,
            185008,1135373,2821050,3260484,4821220,1700954,3243343,2183615,394339,2630121,1811267,1060542,
            3898314,892312,2015580,11161,4965095,2128470,2320933,1095881,3938450,1887098,975426,2098073,3300937,
            1145560,2894728,1026181,3259403,4509345,3610224,3584456,1877483,2665752,2243671,616205,504849,3068426,
            1471925,4144568};
        vector <int> query( queryARRAY, queryARRAY+ARRSIZE(queryARRAY) );
        LimitedMemorySeries1 theObject;
        eq<ll>(2, theObject.getSum(5000000, 482995837, 512849030, 120583724, query),49684994148L);
    }
    return 0;
}
// END CUT HERE
