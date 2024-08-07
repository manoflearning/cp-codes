// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const ll INF = 1e18;
const int MAXN = 101010;

int n;
vector<vector<int>> t;
vector<ll> w;
vector<vector<int>> ord;
vector<ll> ans;

int q;
vector<int> qu;

void init() {
    t.clear();
    w.clear();
    qu.clear();
    ord.clear();
    ans.clear();
}

void input() {
    cin >> n;

    t.resize(n + 1);
    w.resize(n + 1);
    ord.resize(n + 1);
    ans.resize(n + 1);

    for (int v = 2; v <= n; v++) {
        int p; cin >> p;
        t[p].push_back(v);
    }
    for (int v = 1; v <= n; v++) cin >> w[v];

    cin >> q;
    qu.resize(q);
    for (auto& i : qu) cin >> i;
}

void solve() {
    for (int v = n; v >= 1; v--) {
        for (auto u : t[v]) {
            vector<vector<ll>> dp(sz(ord[v]) + 1, vector<ll>(sz(ord[u]) + 1, INF));
            dp[sz(ord[v])][sz(ord[u])] = 0;
            for (int i = sz(ord[v]); i >= 0; i--) {
                for (int j = sz(ord[u]); j >= 0; j--) {
                    int ti = i + j + 1;
                    if (i < sz(ord[v])) dp[i][j] = min(dp[i][j], ti * w[ord[v][i]] + dp[i + 1][j]);
                    if (j < sz(ord[u])) dp[i][j] = min(dp[i][j], ti * w[ord[u][j]] + dp[i][j + 1]);
                }
            }

            vector<int> tmp;
            int p1 = 0, p2 = 0;
            while (p1 < sz(ord[v]) || p2 < sz(ord[u])) {
                if (p1 == sz(ord[v])) tmp.push_back(ord[u][p2++]);
                else if (p2 == sz(ord[u])) tmp.push_back(ord[v][p1++]);
                else if (dp[p1][p2] == (p1 + p2 + 1) * w[ord[v][p1]] + dp[p1 + 1][p2]) tmp.push_back(ord[v][p1++]);
                else tmp.push_back(ord[u][p2++]);
            }

            ord[v] = tmp;

            ord[u].clear();
            ord[u].shrink_to_fit();
        }

        ord[v].push_back(v);

        for (int i = 0; i < sz(ord[v]); i++) {
            ans[v] += (i + 1) * w[ord[v][i]];
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        solve();

        for (auto& i : qu)
            cout << ans[i] << ' ';
        cout << '\n';

        cout << flush;
    }
}