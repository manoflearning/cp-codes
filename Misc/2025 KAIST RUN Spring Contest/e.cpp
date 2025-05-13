#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;

const int N = 101010;
const int M = 101010;
const ll INF = 1e18;

int n, m;
ll k;
vector<pii> dag[N];

pii e[M];
ll w[M];
int selected[M];

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll ret = power(x, y / 2);
    return ret * ret % MOD * (y & 1 ? x : 1) % MOD;
}

bool vis[N];
int vis_cnt = 0;

void dfs(int v) {
    vis[v] = 1;
    vis_cnt++;

    for (auto &i : dag[v]) {
        if (!selected[i.sc] || vis[i.fr]) continue;
        dfs(i.fr);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dag[u].push_back({v, i});
    }

    // subtask 1
    if (m == n - 1) {
        ll ans = (ll)(k + 1) * m % MOD * power(2, MOD - 2) % MOD;
        cout << ans << '\n';
    }
    // subtask 2
    else if (m <= 10 && k <= 2) {
        ll ans1 = 0, ans2 = 0;

        for (int b1 = 0; b1 < (1 << m); b1++) {
            for (int i = 0; i < m; i++) {
                w[i] = (b1 & (1 << i) ? 1 : k);
            }

            ll res = INF;
            for (int b2 = 0; b2 < (1 << m); b2++) {
                for (int i = 0; i < m; i++) {
                    selected[i] = (b2 & (1 << i) ? 1 : 0);
                }
                
                memset(vis, 0, sizeof(vis));
                vis_cnt = 0;
                
                dfs(1);

                if (vis_cnt == n) {
                    ll sum = 0;
                    for (int i = 0; i < m; i++) {
                        sum += w[i] * selected[i];
                    }
                    res = min(res, sum);
                }
            }

            assert(res != INF);
            ans1 = (ans1 + res) % MOD, ans2++;
        }
        cout << ans1 * power(ans2, MOD - 2) % MOD;
    }
    // subtask 3
    else {
        cout << "love love love" << '\n';
    }
}
