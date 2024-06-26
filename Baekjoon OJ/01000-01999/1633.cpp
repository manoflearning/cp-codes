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

vt<ll> w1, w2;
ll dp[66][16][16];
vt<int> c;

void init() {
    FOR(66) FOR(j, 16) FOR(k, 16) dp[i][j][k] = -1;
}

ll f(int idx, int acnt, int bcnt) {
    ll& ret = dp[idx][acnt][bcnt];
    if (ret != -1) return ret;
    if (acnt == 0 && bcnt == 0) return ret = 0;
    if (idx == sz(c)) return ret = -INF;

    ret = 0;
    int i = c[idx];
    if (acnt > 0) ret = max(ret, f(idx + 1, acnt - 1, bcnt) + w1[i]);
    if (bcnt > 0) ret = max(ret, f(idx + 1, acnt, bcnt - 1) + w2[i]);
    ret = max(ret, f(idx + 1, acnt, bcnt));

    return ret;
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

    init();

    vt<int> a, b;
	for (int i = 0; ; i++) {
        int u, v;
        cin >> u >> v;
        if (cin.eof()) break;
        a.push_back(sz(w1));
        b.push_back(sz(w1));
        w1.push_back(u);
        w2.push_back(v);
    }

    sort(all(a), [&](int u, int v) {
        return w1[u] > w1[v];
    });
    sort(all(b), [&](int u, int v) {
        return w2[u] > w2[v];
    });

    FOR(30) {
        c.push_back(a[i]);
        c.push_back(b[i]);
    }

    sort(all(c));
    c.erase(unique(all(c)), c.end());

    cout << f(0, 15, 15);

	return 0;
}