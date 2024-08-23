#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n, m;
int a[111], b[111];

int dp[111][111], opt[111][111];
int ssum_a[111][111], ssum_b[111][111];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> b[i];

    // suffix sum
    for (int i = 0; i < 111; i++)
        for (int j = 0; j < 111; j++)
            ssum_a[i][j] = ssum_b[i][j] = INF;

    for (int i = n; i >= 1; i--) {
        ssum_a[i][a[i]] = i;
        for (int j = 1; j <= 100; j++) {
            ssum_a[i][j] = min(ssum_a[i][j], ssum_a[i + 1][j]);
        }
    }
    for (int i = m; i >= 1; i--) {
        ssum_b[i][b[i]] = i;
        for (int j = 1; j <= 100; j++) {
            ssum_b[i][j] = min(ssum_b[i][j], ssum_b[i + 1][j]);
        }
    }

    // solve
    vector<int> ans;
    int i = 1, j = 1;
    while (i <= n && j <= m) {
        bool is_changed = 0;
        for (int k = 100; k >= 1; k--) {
            if (ssum_a[i][k] != INF && ssum_b[j][k] != INF) {
                i = ssum_a[i][k] + 1;
                j = ssum_b[j][k] + 1;
                ans.push_back(k);
                is_changed = 1;
                break;
            }
        }
        if (!is_changed) break;
    }

    cout << sz(ans) << '\n';
    for (auto& i : ans)
        cout << i << ' ';
}