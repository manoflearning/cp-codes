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
    ll w;
    int v;
};

struct dw {
    int d;
    ll w;
    bool operator<(const dw& rhs) const {
        if (d != rhs.d) return d > rhs.d;
        return w < rhs.w;
    }
};

int n, m;
vt<wv> adj[50505];
int mxd = 0;
ll mnw = 1e18;

void input() {
    cin >> n >> m;
    FOR(n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

dw f(int v, int prv, int d, ll w) {
    if (sz(adj[v]) == 1 && v != 1) {
        if (d > mxd || (d == mxd && w < mnw)) mxd = d, mnw = w;
        return { 0, 0 };
    }

    vt<dw> a;
    EACH(i, adj[v]) {
        if (i.v == prv) continue;
        dw res = f(i.v, v, d + 1, w + i.w);
        a.push_back({ res.d + 1, res.w + i.w });
    }

    if (sz(a) > 1) {
        sort(a.begin(), a.end());

        int D = a[0].d + a[1].d + 1;
        ll W = a[0].w + a[1].w;
        if (D > mxd || (D == mxd && W < mnw)) {
            mxd = D, mnw = W;
        }
    }

    return a[0];
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

    f(1, 0, 1, 0);
    
    //cout << mxd << ' ' << mnw << '\n';
    cout << (mnw + m - 1) / m;

	return 0;
}