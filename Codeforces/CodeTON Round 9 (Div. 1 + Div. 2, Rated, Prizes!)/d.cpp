#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

bool is_valid(const vector<int> &a) {
    for (int i = 1; i < sz(a); i++) {
        for (int j = i + 1; j < sz(a); j++) {
            if (a[gcd(i, j) - 1] == gcd(a[i], a[j])) {
                cout << i << ' ' << j << '\n';
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<int> s(m);
        for (auto &i : s) cin >> i;
        reverse(all(s));

        vector<int> ans(n + 1);

        vector<bool> vis(n + 1);
        ans[1] = s[0];
        for (int i = 2; i <= n; i++) {
            vector<int> div;
            for (int j = 1; j * j <= i; j++) {
                if (i % j == 0) {
                    div.push_back(j);
                    if (i * i != j) div.push_back(i / j);
                }
            }

            for (auto &j : div) vis[ans[j]] = 1;

            for (auto &j : s) {
                if (!vis[j]) { ans[i] = j; break; }
            }

            for (auto &j : div) vis[ans[j]] = 0;
        }

        bool is_valid = 1;
        for (int i = 1; i <= n; i++)
            is_valid &= (ans[i] > 0);

        if (is_valid) {
            for (int i = 1; i <= n; i++) {
                cout << ans[i] << ' ';
            }
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
        
    }
}
