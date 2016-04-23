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
#include <utility>

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

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define ALL(c) (c).begin(),(c).end()

int c[26];

class ColorfulGarden {
public:
    vector <string> rearrange(vector <string> g)
    {
        ZERO(c);
        int n = g[0].size();
        REP(i, n) {
            ++c[int(g[0][i] - 'a')];
            ++c[int(g[1][i] - 'a')];
        }
        REP(i, 26) if (n < c[i]) return { };
        vector<string> res = {"", ""};
        REP(j, n) REP(i, 2) {
            int x = -1;
            REP(y, 26) {
                if (0 < i && y == res[i - 1][j] - 'a') continue;
                if (0 < j && y == res[i][j - 1] - 'a') continue;
                if (0 <= x && c[y] <= c[x]) continue;
                x = y;
            }
            if (x < 0 || c[x] == 0)
            {
                REP(y, 26) if (0 < c[y]) x = y;
                res[1] += char('a' + x);
                auto tmp = res[0][j];
                res[0][j] = res[1][j];
                res[1][j] = tmp;
            }
            else
            {
                --c[x];
                res[i] += char('a' + x);
            }
        }
        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        string gardenARRAY[] = {"aaabbbccabbbaabaaccccbcbbbcaacbcabacccacaabbcbabaa",
            "baacccacacbacacbbabbcccccbaaacbacacbbcabcbcccccaab"};
        vector <string> garden( gardenARRAY, gardenARRAY+ARRSIZE(gardenARRAY) );
        string retrunValueARRAY[] = {"babab", "ababa" };
        vector <string> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        ColorfulGarden theObject;
        eq(3, theObject.rearrange(garden),retrunValue);
    }

//    {
//        string gardenARRAY[] = {"ababab",
//            "bababa"};
//        vector <string> garden( gardenARRAY, gardenARRAY+ARRSIZE(gardenARRAY) );
//        string retrunValueARRAY[] = {"bababa", "ababab" };
//        vector <string> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        ColorfulGarden theObject;
//        eq(3, theObject.rearrange(garden),retrunValue);
//    }
//    {
//        string gardenARRAY[] = {"abcdefghijklm",
//            "nopqrstuvwxyz"};
//        vector <string> garden( gardenARRAY, gardenARRAY+ARRSIZE(gardenARRAY) );
//        string retrunValueARRAY[] = {"abcdefghijklm", "nopqrstuvwxyz" };
//        vector <string> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        ColorfulGarden theObject;
//        eq(3, theObject.rearrange(garden),retrunValue);
//    }
//    {
//        string gardenARRAY[] = {"abcd",
//            "abcd"};
//        vector <string> garden( gardenARRAY, gardenARRAY+ARRSIZE(gardenARRAY) );
//        string retrunValueARRAY[] = {"abcd", "dcba" };
//        vector <string> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        ColorfulGarden theObject;
//        eq(2, theObject.rearrange(garden),retrunValue);
//    }
//    {
//        string gardenARRAY[] = {"aa",
//            "bb"};
//        vector <string> garden( gardenARRAY, gardenARRAY+ARRSIZE(gardenARRAY) );
//        string retrunValueARRAY[] = {"ab", "ba" };
//        vector <string> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
//        ColorfulGarden theObject;
//        eq(0, theObject.rearrange(garden),retrunValue);
//    }
//    {
//        string gardenARRAY[] = {"xxxx",
//            "xxxx"};
//        vector <string> garden( gardenARRAY, gardenARRAY+ARRSIZE(gardenARRAY) );
//        ColorfulGarden theObject;
//        eq(1, theObject.rearrange(garden),vector <string>());
//    }
//    {
//        string gardenARRAY[] = {"aaa",
//            "aab"};
//        vector <string> garden( gardenARRAY, gardenARRAY+ARRSIZE(gardenARRAY) );
//        ColorfulGarden theObject;
//        eq(4, theObject.rearrange(garden),vector <string>());
//    }
    return 0;
}
// END CUT HERE
