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

struct wv {
    ll w; int v;
};

vt<wv> adj[50505];
int vi[50505];

ll dfs(int v, int cnt, int en) {
    if (v == en) return 0;
    
    ll ret = INF;
    if (cnt == 2) {
        EACH(i, adj[v]) {
            if (vi[i.v]) continue;
            if (i.v != en) continue;

            vi[i.v] = 1;
            ret = min(ret, i.w + dfs(i.v, cnt + 1, en));
            vi[i.v] = 0;
        }
    }
    else {
        EACH(i, adj[v]) {
            if (vi[i.v]) continue;
            vi[i.v] = 1;
            ret = min(ret, i.w + dfs(i.v, cnt + 1, en));
            vi[i.v] = 0;
        }
    }
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m, q;
    cin >> n >> m >> q;

    FOR(m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }

    while (q--) {
        int st, en;
        cin >> st >> en;

        ll ans = INF;

        // 1 bus
        EACH(i, adj[st]) {
            if (i.v == en) ans = min(ans, i.w);
        }

        // 2 bus
        

        if (ans == INF) cout << -1 << '\n';
        else cout << ans << '\n';
    }

	return 0;
}