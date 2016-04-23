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

#define REP(k, a) for (int k = 0; k < (a); ++k)

class KeyDungeonDiv2 {
public:
    int countDoors(vector <int> R, vector <int> G, vector <int> keys)
    {
        int n = R.size();
        int r = keys[0];
        int g = keys[1];
        int w = keys[2];
        int res = 0;
        REP(i, n) {
            int rl = max(R[i] - r, 0);
            int gl = max(G[i] - g, 0);
            if (rl + gl <= w) ++res;
        }
        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int doorRARRAY[] = {3, 5, 4, 2, 8};
        vector <int> doorR( doorRARRAY, doorRARRAY+ARRSIZE(doorRARRAY) );
        int doorGARRAY[] = {4, 2, 3, 8, 1};
        vector <int> doorG( doorGARRAY, doorGARRAY+ARRSIZE(doorGARRAY) );
        int keysARRAY[] = {0, 0, 10};
        vector <int> keys( keysARRAY, keysARRAY+ARRSIZE(keysARRAY) );
        KeyDungeonDiv2 theObject;
        eq(2, theObject.countDoors(doorR, doorG, keys),5);
    }
    {
        int doorRARRAY[] = {2, 0, 5, 3};
        vector <int> doorR( doorRARRAY, doorRARRAY+ARRSIZE(doorRARRAY) );
        int doorGARRAY[] = {1, 4, 0, 2};
        vector <int> doorG( doorGARRAY, doorGARRAY+ARRSIZE(doorGARRAY) );
        int keysARRAY[] = {2, 3, 1};
        vector <int> keys( keysARRAY, keysARRAY+ARRSIZE(keysARRAY) );
        KeyDungeonDiv2 theObject;
        eq(0, theObject.countDoors(doorR, doorG, keys),3);
    }
    {
        int doorRARRAY[] = {0, 1, 2, 0};
        vector <int> doorR( doorRARRAY, doorRARRAY+ARRSIZE(doorRARRAY) );
        int doorGARRAY[] = {0, 2, 3, 1};
        vector <int> doorG( doorGARRAY, doorGARRAY+ARRSIZE(doorGARRAY) );
        int keysARRAY[] = {0, 0, 0};
        vector <int> keys( keysARRAY, keysARRAY+ARRSIZE(keysARRAY) );
        KeyDungeonDiv2 theObject;
        eq(1, theObject.countDoors(doorR, doorG, keys),1);
    }

    {
        int doorRARRAY[] = {4, 5, 4, 6, 8};
        vector <int> doorR( doorRARRAY, doorRARRAY+ARRSIZE(doorRARRAY) );
        int doorGARRAY[] = {2, 1, 2, 3, 5};
        vector <int> doorG( doorGARRAY, doorGARRAY+ARRSIZE(doorGARRAY) );
        int keysARRAY[] = {1, 2, 1};
        vector <int> keys( keysARRAY, keysARRAY+ARRSIZE(keysARRAY) );
        KeyDungeonDiv2 theObject;
        eq(3, theObject.countDoors(doorR, doorG, keys),0);
    }
    {
        int doorRARRAY[] = {41,44,41,57,58,74,84,100,58,2,43,32,82,97,44,13,35,98,96,81,43,77,18,51,27,
            27,39,39,45,82,59,20,28,93,6,39,64,78,28,85,17,56,3,68,4,0,36,80,41,77};
        vector <int> doorR( doorRARRAY, doorRARRAY+ARRSIZE(doorRARRAY) );
        int doorGARRAY[] = {67,15,53,36,88,29,26,57,68,99,97,27,51,70,3,49,65,75,35,92,66,0,23,96,38,86,
            98,31,26,75,30,2,92,78,100,99,38,26,85,74,77,15,16,48,100,88,55,93,99,54};
        vector <int> doorG( doorGARRAY, doorGARRAY+ARRSIZE(doorGARRAY) );
        int keysARRAY[] = {39,31,34};
        vector <int> keys( keysARRAY, keysARRAY+ARRSIZE(keysARRAY) );
        KeyDungeonDiv2 theObject;
        eq(4, theObject.countDoors(doorR, doorG, keys),17);
    }
    return 0;
}
// END CUT HERE
