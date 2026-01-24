#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<int> deg(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++, deg[v]++;
    }

    for (int v = 1; v <= n; v++) {
        ll res = 1;
        res *= (n - deg[v] - 1);
        res *= (n - deg[v] - 2);
        res *= (n - deg[v] - 3);
        res /= 6;

        cout << res << ' ';
    }

    return 0;
}
