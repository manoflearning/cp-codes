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

int n, par[202020]; 
vt<int> chd[202020];
ll a[202020], b[202020], asum[202020];
ll ans[202020], bsum[202020], top = 1;

void init() {
    FOR(i, 1, n + 1) {
        par[i] = 0;
        chd[i].clear();
        a[i] = b[i] = asum[i] = ans[i] = bsum[i] = 0;
    }
    n = 0, top = 1;
}

void input() {
    cin >> n;
    for (int v = 2; v <= n; v++) {
        cin >> par[v] >> a[v] >> b[v];
        chd[par[v]].push_back(v);
    }
}

void dfsa(int v) {
    asum[v] += a[v];
    EACH(i, chd[v]) {
        asum[i] += asum[v];
        dfsa(i);
    }
}

void dfsr(int v) {
    bsum[top] = b[v] + bsum[top - 1];
    top++;

    int l = 1, r = top - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (bsum[mid] <= asum[v]) l = mid;
        else r = mid - 1;
    }

    ans[v] = l - 1;

    EACH(i, chd[v]) dfsr(i);

    top--;
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

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        input();

        dfsa(1);

        dfsr(1);

        FOR(i, 2, n + 1) 
            cout << ans[i] << ' ';
        cout << '\n';

        init();
    }

	return 0;
}