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

int n;
int a[1001001], ind[1001001];
vt<int> adj[1001001];
int vi[1001001], fi[1001001];
vt<int> cy;
ll cnt, len[1001001];

void input() {
    cin >> n >> cnt;
    FOR(n) {
        cin >> a[i + 1];
        if (a[i + 1] != i + 1) {
            int u = a[i + 1], v = i + 1;
            adj[u].push_back(v);
            ind[v]++;
            //cout << u << ' ' << v << '\n';
        }
    }
}

void dfs(int v) {
	vi[v] = 1;
	for (int next : adj[v]) {
		if (!vi[next]) dfs(next);
		else if (!fi[next]) cy.push_back(next);
	}
	fi[v] = 1;
}

ll f(int v, int prv) {
    ll ret = (prv == -1 ? cnt : cnt - 1);

    EACH(i, adj[v]) {
        ret = ret * f(i, v) % MOD;
    }
    return ret;
}

int isCycle[1001001];
int cycle[1001001], top = 0;

int dfs2(int v) {
    vi[v] = 1;

    int ret = 0;
    EACH(i, adj[v]) {
        if (vi[i]) ret = 1;
        else ret |= dfs2(i);
    }
    
    if (ret) {
        cycle[top++] = v;
        isCycle[v] = 1;
    }

    return ret;
}

ll f2(int v) {
    top = 0;
    dfs2(v);

    ll ret = 1;
    FOR(j, top) {
        int v = cycle[j];
        EACH(i, adj[v]) {
            if (isCycle[i]) continue;
            ret = (ret * f(i, v)) % MOD;
        }
    }
    
    ret = ret * len[top] % MOD;
    
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
    
    input();

    FOR(i, 1, n + 1)
        if (!vi[i]) dfs(i);

    memset(vi, 0, sizeof(vi));

    ll ans = 1;
    // 싸이클 X
    FOR(i, 1, n + 1) {
        if (ind[i] == 0) {
            ans = (ans * f(i, -1)) % MOD;
        }
    }

    // 싸이클 O
    len[2] = cnt * (cnt - 1) % MOD;
    len[3] = cnt * (cnt - 1) % MOD;
    len[3] = len[3] * max(0ll, cnt - 2) % MOD;
    
    FOR(i, 4, n + 1) {
        len[i] = (len[i - 1] * max(0ll, cnt - 2) + len[i - 2] * (cnt - 1)) % MOD;
    }

    EACH(i, cy) {
        ans = (ans * f2(i)) % MOD;
    }

    cout << ans;

	return 0;
}