#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int MOD = 1e9 + 7;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int x, n;
    cin >> x >> n;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];

    vector<bool> vis(n + 1);
    int ans = x;

    int q; cin >> q;
    while (q--) {
        int p; cin >> p;

        if (!vis[p]) {
            ans += w[p];
            vis[p] = 1;
        } else {
            ans -= w[p];
            vis[p] = 0;
        }

        cout << ans << '\n';
    }
}