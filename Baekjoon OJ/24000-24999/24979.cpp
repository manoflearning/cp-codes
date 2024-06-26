#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

string s;
int q;
int pc[202020], po[202020], pw[202020];

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> s >> q;

    pc[1] = (s[0] == 'C');
    po[1] = (s[0] == 'O');
    pw[1] = (s[0] == 'W');

    FOR(i, 1, sz(s)) {
        pc[i + 1] = pc[i];
        po[i + 1] = po[i];
        pw[i + 1] = pw[i];

        if (s[i] == 'C') pc[i + 1]++;
        if (s[i] == 'O') po[i + 1]++;
        if (s[i] == 'W') pw[i + 1]++;
    }

    FOR(q) {
        int l, r;
        cin >> l >> r;
        
        int cc = pc[r] - pc[l - 1];
        int co = po[r] - po[l - 1];
        int cw = pw[r] - pw[l - 1];
        
        if (cc & 1 && co % 2 == 0 && cw % 2 == 0) cout << 'Y';
        else if (cc % 2 == 0 && co & 1 && cw & 1) cout << 'Y';
        else cout << 'N';
    }

	return 0;
}