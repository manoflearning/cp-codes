#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 5050;
const int MOD = 998'244'353;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x % MOD;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}
// ll gcd(ll x, ll y) {
//     if (!y) return x;
//     return gcd(y, x % y);
// }

const int MAXN = 5050, MAXD = 13; // 2^MAXD = 8192

int n, dep[MAXN], par[MAXN][MAXD + 1];
vector<int> adj[MAXN];
int sz_chd[MAXN];

int dp_lca[MAXN][MAXN];

void dfs(int now, int prv) {
  par[now][0] = prv;
  dep[now] = dep[prv] + 1;
  sz_chd[now] = 1;
  for (auto i : adj[now]) {
    if (i == prv) continue;
    dfs(i, now);
    sz_chd[now] += sz_chd[i];
  }
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

inline ll nc2_neg1(ll n) {
    return n * (n - 1) / 2 - (n - 1);
}
inline ll nc2_neg2(ll n) {
    return n * (n - 1) / 2 - (n - 2);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    buildSparseTable();

    ll acc = 0;

    ll q1 = (n - 1) * nc2_neg2(n) % MOD;
    ll q2 = q1 * q1 % MOD;

    // case 1: first turn die
    for (int v = 2; v <= n; v++) {
        int t1 = sz_chd[v];
        int t2 = n - t1;

        ll p = (nc2_neg1(t1) + nc2_neg1(t2)) % MOD * q1 % MOD;
        acc = (acc + p) % MOD;
    }

    // case 2.1.: q_1 != p_2
    for (int v = 2; v <= n; v++) {
        for (int u = v + 1; u <= n; u++) {
            dp_lca[v][u] = dp_lca[u][v] = lca(u, v);
        }
    }
    for (int v = 2; v <= n; v++) {
        for (int u = 2; u <= n; u++) {
            if (v == u) continue;

            int lc = dp_lca[u][v];

            ll t1 = -1;
            ll t2 = -1;
            ll t3 = -1;

            if (lc == v || lc == u) {
                if (lc == v) {
                    t1 = n - sz_chd[v];
                    t2 = sz_chd[u];
                } else {
                    t1 = sz_chd[v];
                    t2 = n - sz_chd[u];
                }
            } else {
                t1 = sz_chd[v];
                t2 = sz_chd[u];
            }
            t3 = n - (t1 + t2);

            {
                ll p = 0;
                p = (p + t1 * t2 * nc2_neg1(t1 + t2));
                p = (p + t1 * t2 * nc2_neg1(t3));
                p = (p + t1 * t3 * nc2_neg1(t1 + t3));
                p = (p + t1 * t3 * nc2_neg1(t2));

                acc = (acc + p) % MOD;
            }
        }
    }

    // case 2.2.: q_1 == p_2
    for (int v = 2; v <= n; v++) {
        ll t1 = sz_chd[v];
        ll t2 = n - t1;

        ll p = 0;
        p = (p + t1 * t2 * nc2_neg1(t1));
        p = (p + t1 * t2 * nc2_neg1(t2));

        acc = (acc + p) % MOD;
    }

    cout << (1 - acc * power(q2, MOD - 2) % MOD + MOD) % MOD;
}
