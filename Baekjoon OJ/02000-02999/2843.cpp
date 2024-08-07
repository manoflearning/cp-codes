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

vt<int> p(303030, -1);

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    p[U] = V;
}

int n, m, nxt[303030], vi[303030];
pii q[303030];
vt<int> ans;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    FOR(i, 1, n + 1) cin >> nxt[i];
    cin >> m;
    FOR(i, m) cin >> q[i].fr >> q[i].sc;

    FOR(i, m) {
        if (q[i].fr == 2) vi[q[i].sc] = 1;
    }

    FOR(i, 1, n + 1)
        if (!vi[i] && nxt[i] != 0) {
            if (find(i) == find(nxt[i])) p[find(i)] = -INF;
            else merge(i, nxt[i]);
        }

    FOR(i, m - 1, -1, -1) {
        auto it = q[i];

        if (it.fr == 1) {
            if (find(it.sc) != find(nxt[it.sc])) ans.push_back(it.sc);
            else {
                if (p[find(it.sc)] == -INF) ans.push_back(INF);
                else ans.push_back(find(it.sc));
            }
        }
        if (it.fr == 2) {
            if (find(it.sc) == find(nxt[it.sc])) {
                p[find(it.sc)] = -INF;
                continue;
            }
            merge(it.sc, nxt[it.sc]);
        }
    }

    FOR(i, sz(ans) - 1, -1, -1) {
        if (ans[i] == INF) cout << "CIKLUS\n";
        else cout << ans[i] << '\n';
    }

	return 0;
}