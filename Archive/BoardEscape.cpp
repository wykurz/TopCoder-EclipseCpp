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
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define SQR(x) ((x) * (x))
#define PW(x) (1ll << (x))
#define BCNT(x) __builtin_popcountll(x)

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

const int dd[] = {1, 0, -1, 0};

constexpr int K = 3000;
int dp[K + 2][50][50];

class BoardEscape {
public:
	using pos = valarray<int>;
	string findWinner(vector <string> s, int k)
	{
		const int n = s.size();
		const int m = s[0].size();
		if (K < k) {
			if (k % 2) k = K + 1; else k = K;
		}
		ZERO(dp);
		FOR (kk, 1, k) {
			REP (i, n) {
				REP (j, m) {
					if (s[i][j] == 'E' || s[i][j] == '#') continue;
					int mex[5] = {0};
					for (int k = 0; k < 4; ++k) {
						int ii = i + dd[k];
						int jj = j + dd[k ^ 1];
						if (ii < 0 || n <= ii || jj < 0 || m <= jj || s[ii][jj] == '#') continue;
						mex[dp[kk - 1][ii][jj]] = 1;
					}
					while (mex[dp[kk][i][j]]) ++dp[kk][i][j];
				}
			}
		}
		int ret = 0;
		REP (i, n) {
			REP (j, m) {
				if (s[i][j] == 'T') {
					ret ^= dp[k][i][j];
				}
			}
		}
		if (ret == 0) return "Bob";
		return "Alice";
	}
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        string sARRAY[] = {"TE"};
        vector <string> s( sARRAY, sARRAY+ARRSIZE(sARRAY) );
        BoardEscape theObject;
        eq(0, theObject.findWinner(s, 2),"Alice");
    }
    {
        string sARRAY[] = {"TTE"};
        vector <string> s( sARRAY, sARRAY+ARRSIZE(sARRAY) );
        BoardEscape theObject;
        eq(3, theObject.findWinner(s, 6),"Alice");
    }
    {
        string sARRAY[] = {"T.T.T.",
            ".E.E.E"};
        vector <string> s( sARRAY, sARRAY+ARRSIZE(sARRAY) );
        BoardEscape theObject;
        eq(2, theObject.findWinner(s, 1),"Alice");
    }
    {
        string sARRAY[] = {"EEE.E.#.EE..EEE#E#.##E#ET.EEE.TEE#EE#E#.E.E#TTE#EE", "#E..#TEE#TEEEEEEEE.E##E.TE##ET#.E##EE#EE##TETEEET.", "#E##EETE#EET#E.E.EEEEETETEEEEE#.E##EE#E#E#EET#EE##", ".TEEE.TT##TEE##E.EE.#E.EEEET#EE.EEEEEEEEE#EE#E##E#", "T#.EE##E#ETEEE.EE#.#EET.EE##TETEEEEEEEE.E.T#.T.T##", "ET.#E#.#E####T#EEE.E.ETEE##E###ET#TTEEEET#E#.EE#TT", "T#EE#T.#E##EE#EET#EEE#EE#EE#..E##E###EE#TEEE#.EE##", "EE.ET#E.EEE#T#E#E####TETETEE.#ET#E##EEEEE##EETTEEE", "E#T#.T#EE.EE..TEEETEEEE.ETE##EEE#EETE#EE#EEEEEEETE", "#EE#.EET#E#.E.#T#EE#E#T#TE.T.#ETEEE#.EE#EETE#.E..#", "#EE#..#EEEEE##ET.EETTEE#TEE###.##E.EE#ETE#.#TE##ET", "E.#TEEEEETEE##E###E#E#EE#.EE..EEEEEE..EE#.EET.#EEE", "#E##EET.E.EEETE#E#TEEETEEEE.#EEEEE.EEEE.#EEE#E#.EE", "TEEEETEEE#E#EEEEEE###.##E#..E#TEEE#EEEEEEEEEEEE##E", "ETE##E#EEEEEE#E.EEEET#E.##EEEE#EE#E##E##EETE##EETE", "EEE.EE.#ET.EE#EEE.#E#T#TET#EEEEEEEEE###T#TE#E.E#EE", "#TE.####E.#EE#T#EE#E#E#TE#EE##E#EE#EE.E#..ETEEE.T#", "..E#EETTEEEE#.E.E#E####E..#.E#.E#ET.E.ETE#E#E#TE#E", "##E.#EEEET#.E.E.E.EEEE###EEEE#EEEE#EE#E.#.##E###EE", "EE.EEE.#.EEE.#TEEE..EEEE#.#.E#EEE#.#E.E#EEE#EEE#E.", "#E#E...#E#EE#..TTE#E##EE#TEETEEEE.EE#E#EETE..EE#.#", "ETE.#TE.#EEEEEEE.EEETTEEEEE.EE.#EE.#EEEEEETEEEE#E.", "ETE#ET#TE.E.TE##.T#E.#E##EE#T.EE#E#ETE####EEEEEET#", ".#EEE#EEEE#E#.E#TEEEEEEEE#EEEEEEE##E#.E#TT.EETE.#T", "#E...#E.EEEE#.EE.EE#.EEE##EEETTET.#E.EETEE#.E..E#E", "#.EE#.E#.TETE#EE#E##E#.E###.TETTEE#E#ETEE#.T#EE#.E", "#E###EEEE##T#..ETEEE.E#EEEEE#EETEEEEEEEEEEEEE.T.EE", "#EEEEEEEEETE#.#E##EEE.EEEEEETEE#TETEEEE.EET.#EEE#E", "E.#E#.#TT#.E#E##.E#EEE##TE#EE.EE#EEEEET.#TET###TET", "EE#.EEE.E.E#T#EETEEEEEE##EEEE#EEE#E#EE#E.EEEE#.##T", "ETTEE##EEETEEE#E.#EE#EE#..#E.E#E#.#EEEE#ETE#E.E###", "ETEEEE.####E.###E#T#E#ETTEEE#EEE.#EEE#EEEEETEE.EEE", ".E#E.#E##.#E#E.ETEE#EE#TETEEEEEEE##ETET#T.#EE##E#.", "#.ETE##EEE#ET#ETEE.#EE.E#.EET#E.E.#.EEE#E#ETEET##E", "T#.EE#E#E##E#E#EE.EE#T.TE.EEE.#EE#E#.EEEEE#TE.EE.#", "T####T.EE##ET.T#TE.E###EEEE#EEE##E##E.ETEEEEE####E", "E###EET###E##E#EEE#E##EEEE#EEE.TT.T#EEEEEEEEE.EE.E", "TEE#EE#..#T#EE.#ET.TE.EE#E#EE##.TE#ETTTEE#E#E#.E#.", "##EE##ET#E.#ETE#EEEETEETEE.EEEE#.E.EE#.EE##EE##EE#", "EEE#EE#..#.#E.TEE#E#TEETTEET##E#EEETETEEEE.EEETTEE", "EE.##EEETEEE.EE##TE#E###E.EEE.EEEEEE###E.EE#EEET.#", "EE#E.E#ETT###.#E#E####EE##.EE.EEEE#E#EEEEE.##EETEE", "EE#ETE.##EEE#EE#ET.#E.##E##E#EEE.T##E#EE.ETEEEE##E", "EE.EEEE##EEE#TEE#EET#.EET#ETT.EE..EETE.#EE#EEEE#.#", "ETETEEE.##EE#E#.EEEE.EEE#EEEEEEEEE#EETE.EE#E.E#EEE", "#.#EEE##E#TEETEEE#TE#.TEEE#EEE#TEEET#EET.#EET#TEEE", ".E#E.##EEE.E#EE##EE###EE#EE#E.EEE#EEEE#.E##ETEE#E#", "EETE..EE#EEEEEETEEE#ET.ETEEE#E#TE..EEETEE.#ET#TEE#", "E##.E.ETT#ETEE#ETT##.EEEEE#E.EEE##ETE#.E###EET.#E#", "#EE#EE#T#E#ETE#TTETETEE#E##T.EEEEE#ET.E#E#EE##EEE#"};
        vector <string> s( sARRAY, sARRAY+ARRSIZE(sARRAY) );
        BoardEscape theObject;
        eq(5, theObject.findWinner(s, 792608691),"Bob");
    }
    {
        string sARRAY[] = {"E#E",
            "#T#",
            "E#E"};
        vector <string> s( sARRAY, sARRAY+ARRSIZE(sARRAY) );
        BoardEscape theObject;
        eq(1, theObject.findWinner(s, 1000000),"Bob");
    }
    {
        string sARRAY[] = {"..........................",
            "......TTT..TTT..T...T.....",
            ".....T.....T..T.TT.TT.....",
            "......TTT..TTT..T.T.T.....",
            ".........T.T.T..T...T.....",
            "......TTT..T..T.T...T.....",
            "..........................",
            "...E#E#E#E#E#E#E#E#E#E#...",
            "..........................",
            "......TTT..TTT...TTT......",
            ".....T........T.T.........",
            "......TTT.....T..TTT......",
            ".....T...T...T..T...T.....",
            "......TTT....T...TTT......",
            "..........................",
            "...#E#E#E#E#E#E#E#E#E#E...",
            "..........................",
            "....TT...T...T..T.TTT.T...",
            "...T.....T...T..T.T...T...",
            "...T.TT..T...TTTT.TT..T...",
            "...T..T..T...T..T.T.......",
            "....TT...TTT.T..T.T...T...",
            ".........................."};
        vector <string> s( sARRAY, sARRAY+ARRSIZE(sARRAY) );
        BoardEscape theObject;
        eq(4, theObject.findWinner(s, 987654321),"Bob");
    }
    return 0;
}
// END CUT HERE
