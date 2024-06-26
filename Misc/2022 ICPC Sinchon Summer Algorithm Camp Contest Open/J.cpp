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

const int sq = sqrt(505050);

int n;
ll a[505050], sum1, sum2;
ll sumv[505050];
vt<int> adj[505050], adj2[505050];

void input() {
    cin >> n;
    FOR(i, 1, n + 1) {
        double x; cin >> x;
        a[i] = x * 100 + 0.5;
    }

    FOR(n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void print() {
    cout << (double)sum1 / 100 + (double)sum2 / 10000 << '\n';
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cout << fixed;
    cout.precision(6);

	input();

    FOR(i, 1, n + 1) 
        sum1 += a[i];

    FOR(u, 1, n + 1) {
        EACH(v, adj[u]) {
            sum2 += a[u] * (100 - a[v]);
            sum2 += (100 - a[u]) * a[v];

            sumv[v] += a[u];
        }
    }
    sum2 >>= 1;

    FOR(u, 1, n + 1) {
        EACH(v, adj[u]) {
            if (sz(adj[u]) >= sq && sz(adj[v]) >= sq) {
                adj2[u].push_back(v);
            }
        }
    }

    print();

    int q; cin >> q;
    while (q--) {
        int v; double x;
        cin >> v >> x;

        ll val = x * 100 + 0.5;

        sum1 += val - a[v];

        if (sz(adj[v]) < sq) {
            EACH(u, adj[v]) {
                sum2 += a[u] * (a[v] - val);
                sum2 += (100 - a[u]) * (val - a[v]);
            }
        }
        else {
            sum2 += sumv[v] * (a[v] - val);
            sum2 += (100 * sz(adj[v]) - sumv[v]) * (val - a[v]);
        }

        EACH(u, adj2[v]) {
            sumv[u] += val - a[v];
        }
        a[v] = val;

        print();
    }

	return 0;
}