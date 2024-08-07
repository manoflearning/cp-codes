#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

int MAX;

int n;
string s;
int dp[19][1 << 18];

/*void init() {
    for (int i = 0; i < 19; i++) {
        memset(dp[i], -1, sizeof(dp[i]));
    }
}*/

/*int f(int v, int cntl) {
    int& ret = dp[v][cntl];
    if (ret != -1) return ret;
    if (v == n) return ret = 1;

    int cntr = (1 << (n - v)) - cntl - 1;

    int lb, rb;
    if (s[v] == '0') {
        if (cntr == 0) return ret = 0;

        lb = (cntl + 1) / 2;
        rb = min(cntl, cntr - 1) + (cntl - min(cntl, cntr - 1)) / 2;
    }
    if (s[v] == '1') {
        if (cntl == 0) return ret = 0;

        lb = max(0, (cntl - 1 - cntr) / 2);
        rb = (cntl & 1 ? cntl / 2 : cntl / 2 - 1);
    }

    for (int i = lb; i <= rb; i++) {
        if (f(v + 1, i)) return ret = 1;
    }

    return ret = 0;
}*/

int psum[1 << 18];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    //init();
    
	cin >> n >> s;
    MAX = (1 << n);

    psum[0] = 1;
    for (int i = 1; i < MAX; i++) {
        psum[i] = 1 + psum[i - 1];
    }
    
    for (int v = n - 1; v >= 0; v--) {
        for (int cntl = 0; cntl <= (1 << (n - v)) - 1; cntl++) {
            int cntr = (1 << (n - v)) - cntl - 1;

            int lb, rb;
            if (s[v] == '0') {
                if (cntr == 0) continue;

                lb = (cntl + 1) / 2;
                rb = min(cntl, cntr - 1) + (cntl - min(cntl, cntr - 1)) / 2;
            }
            if (s[v] == '1') {
                if (cntl == 0) continue;

                lb = max(0, (cntl - 1 - cntr) / 2);
                rb = (cntl & 1 ? cntl / 2 : cntl / 2 - 1);
            }
            //if (v == 2) cout << cntl << ' ' << cntr << ' ' << lb << ' ' << rb << '\n';
            if (rb >= lb && psum[rb] - (lb == 0 ? 0 : psum[lb - 1]) > 0) {
                dp[v][cntl] = 1;
            }
        }

        memset(psum, 0, sizeof(psum));

        psum[0] = dp[v][0];
        for (int cntl = 1; cntl <= (1 << (n - v)) - 1; cntl++) {
            psum[cntl] = dp[v][cntl] + psum[cntl - 1];
        }
    }

    for (int v = 1; v <= MAX; v++) {
        int cntl = v - 1, cntr = MAX - v;

        if (dp[0][cntl]) cout << v << ' ';
    }

	return 0;
}