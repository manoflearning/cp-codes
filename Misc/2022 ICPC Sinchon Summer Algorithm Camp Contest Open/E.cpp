#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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
string s;
vt<int> adj[505050], chd[505050], vdep[505050];
int par[505050], dep[505050], mxDep;
int nxt[505050];

void input() {
    cin >> n >> s;

    s.push_back('a');
    FOR(i, n - 1, -1, -1) {
        s[i + 1] = s[i];
    }

    FOR(n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfsInit(int v, int prv) {
    dep[v] = dep[prv] + 1;
    mxDep = max(mxDep, dep[v]);
    vdep[dep[v]].push_back(v);
    par[v] = prv;

    EACH(i, adj[v]) {
        if (i == prv) continue;
        chd[v].push_back(i);
        dfsInit(i, v);
    }
}

int f(int u, int v) {
    if (s[u] < s[v]) return 1;
    else if (s[u] > s[v]) return 0;

    if (nxt[u] == -1) return 1;
    if (nxt[v] == -1) return 0;

    return f(nxt[u], nxt[v]);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    FOR(505050) nxt[i] = -1;

    input();

    dfsInit(1, 0);

    for (int d = mxDep; d >= 1; d--) {
        EACH(v, vdep[d]) {
            if (chd[v].empty()) continue;

            int mxnxt = chd[v][0];
            FOR(i, 1, sz(chd[v])) {
                if (f(mxnxt, chd[v][i])) mxnxt = chd[v][i];
            }

            nxt[v] = mxnxt;
        }
    }

    int now = 1;
    while (1) {
        cout << s[now];
        if (nxt[now] == -1) break;
        now = nxt[now];
    }

	return 0;
}