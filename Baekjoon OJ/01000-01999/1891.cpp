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

int d;
string st, en;
ll sx, sy;
ll xdiff, ydiff;

void numToCo() {
    FOR(i, d) {
        auto it = st[d - i - 1];
        if (it == '1') sx += (1ll << i);
        if (it == '2') continue;
        if (it == '3') sy += (1ll << i);
        if (it == '4') sx += (1ll << i), sy += (1ll << i);
    }
}

void coToNum() {
    en.resize(d);

    FOR(i, d) {
        //int bx = (1ll << i) & sx, by = (1ll << i) & sy;
        int bx = 0, by = 0;
        if ((1ll << i) & sx) bx = 1;
        if ((1ll << i) & sy) by = 1;

        if (bx && !by) en[d - i - 1] = '1';
        if (!bx && !by) en[d - i - 1] = '2';
        if (!bx && by) en[d - i - 1] = '3';
        if (bx && by) en[d - i - 1] = '4';
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> d >> st;
    cin >> xdiff >> ydiff;
    
    numToCo();

    sx += xdiff, sy -= ydiff;

    if (sx < 0 || (1ll << d) <= sx || sy < 0 || (1ll << d) <= sy) {
        cout << -1;
        return 0;
    }

    coToNum();

    cout << en;

	return 0;
}