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
    ll w, v;
};

ll n, q, ibit;
vt<wv> adj[101010];
ll lb[101010], con[101010];

void init() {
    FOR(101010) lb[i] = -1;
    ibit = (1 << 31) - 1;
}

void input() {
    cin >> n >> q;

    while (q--) {
        ll u, v, w;
        cin >> u >> v >> w;

        if (u == v) {
            con[u] = lb[u] = w;
            continue;
        }

        if (u > v) swap(u, v);
        adj[v].push_back({ w, u });
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

    input();
    
    FOR(i, n, 0, -1) {
        if (lb[i] == -1 && adj[i].empty()) continue;

        ll res = ibit;
        EACH(j, adj[i]) res &= j.w;

        if (lb[i] != -1) {
            if (adj[i].empty()) res = lb[i];
            else res |= lb[i];
        }

        con[i] = res;

        EACH(j, adj[i]) {
            if (lb[j.v] == -1) lb[j.v] = 0;
            lb[j.v] |= j.w - (j.w & res);
        }
    }

    FOR(i, 1, n + 1) {
        if (adj[i].empty()) continue;

        ll left = 0;
        for (int b = 30; b >= 0; b--) {
            int res = 1;
            EACH(j, adj[i]) {
                if ((j.w & (1 << b)) == (1 << b) 
                && (con[j.v] & (1 << b)) != (1 << b)) res = 0;
            }

            if (res) left |= (1 << b);
        }
        
        con[i] -= (con[i] & left);
        if (lb[i] != -1) con[i] |= lb[i];
    }

    FOR(i, 1, n + 1)
        cout << con[i] << ' ';

	return 0;
}