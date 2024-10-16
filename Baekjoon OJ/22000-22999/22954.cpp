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

struct vidx {
    int v, idx;
};

int n, m, vi[101010];
vt<vidx> adj[101010];

void input() {
    cin >> n >> m;
    FOR(m) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({ v, i + 1 });
        adj[v].push_back({ u, i + 1 });
    }
}

void dfs(int v) {
    vi[v] = 1;
    EACH(i, adj[v]) {
        if (!vi[i.v]) dfs(i.v);
    }
}

int comCnt() {
    int ret = 0;
    FOR(i, 1, n + 1) {
        if (!vi[i]) {
            dfs(i);
            ret++;
        }
    }
    return ret;
}

vt<int> vv, ee;
int deg[101010];

void dfs2(int v) {
    vi[v] = 1;
    vv.push_back(v);
    EACH(i, adj[v]) {
        if (!vi[i.v]) { 
            deg[v]++, deg[i.v]++;
            ee.push_back(i.idx);
            dfs2(i.v);
        }
    }
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

    if (n == 1 || n == 2) {
        cout << -1;
        return 0;
    }

    int cCnt = comCnt();

    if (cCnt >= 3) {
        cout << -1;
        return 0;
    }

    if (cCnt == 1) {        
        memset(vi, 0, sizeof(vi));
        dfs2(1);
        int x = -1;
        cout << 1 << ' ' << n - 1 << '\n';
        FOR(i, 1, n + 1) {
            if (deg[i] == 1) {
                cout << i << '\n';
                x = i;
                cout << '\n';
                break;
            }
        }
        
        FOR(i, 1, n + 1) if (i != x) cout << i << ' ';
        cout << '\n';
        EACH(i, ee) {
            int bit = 0;
            EACH(j, adj[x]) if (j.idx == i) bit = 1;
            if (!bit) cout << i << ' ';
        }
        cout << '\n';
    }
    else if (cCnt == 2) {
        memset(vi, 0, sizeof(vi));
        vt<vt<int>> ans;
        
        FOR(i, 1, n + 1) {
            if (!vi[i]) {
                vv.clear(); ee.clear();
                dfs2(i);
                ans.push_back(vv);
                ans.push_back(ee);
            }
        }
        
        if (sz(ans[0]) == sz(ans[2])) {
            cout << -1;
            return 0;
        }

        cout << sz(ans[0]) << ' ' << sz(ans[2]) << '\n';
        EACH(i, ans) {
            EACH(j, i) cout << j << ' ';
            cout << '\n';
        }
    }

	return 0;
}