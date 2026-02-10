#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using i128 = __int128_t;
using pii = pair<int, int>;
using vi = vector<int>;

ll dfs(int now, vector<bool> &vis, const vector<int> &p) {
    vis[now] = 1;

    if (!vis[p[now]]) return 1 + dfs(p[now], vis, p);
    else return 1;
}

i128 gcd(i128 x, i128 y) {
    if (!y) return x;
    return gcd(y, x % y);
}
i128 lcm(i128 x, i128 y) {
    return x * y / gcd(x, y);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<int> cnt_p(k);
    for (int i = 0; i < n; i++) {
        cnt_p[i % k]++;
    }
    vector<int> pcnt_p(k + 1);
    for (int i = 0; i < k; i++) {
        pcnt_p[i + 1] = cnt_p[i] + pcnt_p[i];
    }

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = (n - i + k - 1) / k - 1 + pcnt_p[i % k];

        // DEBUG
        // cout << i << ' ' << p[i] << '\n';
    }

    i128 ans = 1;
    vector<ll> x;
    vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            const i128 l = dfs(i, vis, p);
            x.push_back(l);

            ans = lcm(ans, l);

            // DEBUG
            // cout << i << ' ' << l << '\n';
        }
    }

    cout << (ll)ans << '\n';
}
