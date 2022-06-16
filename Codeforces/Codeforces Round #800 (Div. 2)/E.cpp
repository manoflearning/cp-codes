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

int n, m, vi[202020];
vt<int> adj[202020];
ll dp[202020];

void input() {
    cin >> n >> m;
    FOR(m) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
}

ll f(int v) {
    ll& ret = dp[v];
    if (ret != -1) return ret;
    if (v == n) return ret = 0;

    vi[v] = 1;
    
    ll degvi = 0;
    vt<ll> res;
    EACH(i, adj[v]) {
        if (vi[i]) degvi++;
        //if (!vi[i]) res.push_back(f(i));
    }
    EACH(i, adj[v]) res.push_back(f(i));

    if (res.empty()) return ret = INF;

    sort(all(res));

    map<ll, ll> mp;
    FOR(sz(res)) {
        if (res[i] == res[0]) continue;

        auto it = mp.find(-res[i] + res[0]);
        if (it != mp.end()) it->sc++;
        else mp.insert({ -res[i] + res[0], 1 });
    }

    ret = res[0] + 1 + degvi;
    EACH(i, mp) {
        if (-i.fr <= i.sc) return -i.fr + ret;
        else ret += i.sc;
    }
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

    FOR(202020) dp[i] = -1;

	input();

    cout << f(1);

	return 0;
}