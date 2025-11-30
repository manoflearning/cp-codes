#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define all(x) (x).begin(), (x).end()

constexpr int N = 202020;

int n, q, ro = 1;
vector<int> t[N];
vector<pll> arr[N];
ll ans[N];

ll in[N], out[N], idx;

void dfs(int v, int prv) {
    in[v] = ++idx;

    for (auto &i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);

        arr[v].push_back({in[i], out[i] - in[i] + 1});
    }

    out[v] = idx;

    arr[v].push_back({1, n - (out[v] - in[v] + 1)});

    for (auto &i : arr[v]) {
        ans[v] += i.second * (n - 1 - i.second);
    }
    ans[v] /= 2;
    ans[v] += n - 1;

    arr[v].push_back({out[v] + 1, n - (out[v] - in[v] + 1)});
    sort(all(arr[v]));
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 0; i < q; i++) {
        int op, x;
        cin >> op >> x;

        if (op == 1) {
            ro = x;
        } else {
            if (ro == x) {
                // cout << "fuck\n";
                cout << ans[x] << '\n';
            } else {
                int j = upper_bound(all(arr[x]), pll{in[ro], 1e18}) - arr[x].begin() - 1;
                // cout << "j = " << j << '\n';
                cout << ans[x] - (n - 1 - arr[x][j].second) * arr[x][j].second - arr[x][j].second << '\n';
            }
        }
    }
}
