#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 66;

int n;
vector<int> a;

bool dp[1010 * N + 1010][N];
int opt[1010 * N + 1010][N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    a.resize(3 * n);
    for (auto &i : a) cin >> i;

    vector<int> ord(3 * n);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) {
        return a[i] < a[j];
    });

    // base case
    dp[0][0] = 1;

    // inductive step
    for (int i = n; i < 3 * n; i++) {
        for (int j = 500 * n; j >= 0; j--) {
            for (int k = n - 1; k >= 0; k--) {
                if (!dp[j][k]) continue;

                if (!dp[j + a[ord[i]]][k + 1]) {
                    dp[j + a[ord[i]]][k + 1] = 1;
                    opt[j + a[ord[i]]][k + 1] = ord[i];
                }
            }
        }
    }

    int opt_j = -1, opt_k = n;
    for (int j = 500 * n + 1; j <= 1000 * n; j++) {
        if (dp[j][opt_k]) {
            opt_j = j;
            break;
        }
    }

    vector<int> ans1, ans2, ans3;
    for (int i = 0; i < n; i++) {
        ans1.push_back(ord[i]);
    }
    while (opt_k) {
        ans2.push_back(opt[opt_j][opt_k]);
        opt_j = opt_j - a[opt[opt_j][opt_k]];
        opt_k--;
    }
    
    vector<bool> vis(3 * n);
    for (auto &i : ans1) vis[i] = 1;
    for (auto &i : ans2) vis[i] = 1;
    for (int i = 0; i < 3 * n; i++) {
        if (!vis[i]) ans3.push_back(i);
    }

    for (auto &i : ans1) cout << i + 1 << '\n';
    for (auto &i : ans2) cout << i + 1 << '\n';
    for (auto &i : ans3) cout << i + 1 << '\n';
}