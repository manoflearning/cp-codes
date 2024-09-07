// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXD = 16;

int n, m;
ll c[1010];
int par[1010][MAXD + 1], dep[1010];
vector<int> chd[1010];

void dfs(int now, int prv) {
	dep[now] = dep[prv] + 1;
	for (auto i : chd[now]) dfs(i, now);
}

void buildSparseTable() {
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) u = par[u][i];
	if (u == v) return u;
	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 2; i <= n; i++) {
        cin >> par[i][0];
        chd[par[i][0]].push_back(i);
    }

    dfs(1, 0);
	buildSparseTable();

    int ans = 0;

    for (int v = 1; v <= n; v++) {
        int res = 0;

        priority_queue<pll> pq;
        for (int u = 1; u <= n; u++) {
            int lc = lca(u, v);
            pq.push({ dep[lc], u });
        }

        ll rem = m;

        ll d = dep[v];
        while (!pq.empty() && rem > 0) {
            vector<int> arr;
            while (!pq.empty() && pq.top().fr == d) {
                arr.push_back(pq.top().sc);
                pq.pop();
            }
            d--;

            sort(all(arr), [&](int p1, int p2) {
                return dep[p1] > dep[p2];
            });

            for (int l = 0, r = 0; l < sz(arr); l = r) {
                while (r < sz(arr) && dep[arr[r]] == dep[arr[l]]) {
                    r++;
                }

                sort(arr.begin() + l, arr.begin() + r, [&](int p1, int p2) {
                    return c[p1] < c[p2];
                });

                ll prv = 0;
                for (int i = l; i < r; i++) {
                    if (rem >= (c[arr[i]] - prv) * (ll)(r - i)) {
                        rem -= (c[arr[i]] - prv) * (ll)(r - i);
                        prv = c[arr[i]];
                        res++;
                    }
                    else { rem = 0; break; }
                }
            }
        }

        ans = max(ans, res);
    }
    assert(ans <= n);

    cout << ans;
}