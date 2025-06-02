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

int dp[5050];
int dp_gcd[5050][5050];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 1; i < 5050; i++) {
        dp[i] = -1;
        for (int j = 1; j < 5050; j++) {
            dp_gcd[i][j] = gcd(i, j);
        }
    }

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &i : a) cin >> i;

        int g = a[0];
        for (auto &i : a) g = gcd(g, i);
        
        int cnt_g = 0;
        for (auto &i : a) if (i == g) cnt_g++;

        set<int> vis;
        queue<int> qu;
        for (auto &i : a) {
            qu.push(i);
            dp[i] = 0;
            vis.insert(i);
        }

        while (!qu.empty()) {
            int v = qu.front();
            qu.pop();

            for (auto &i : a) {
                int u = dp_gcd[i][v];
                if (dp[u] != -1) continue;
                qu.push(u);
                dp[u] = 1 + dp[v];
                vis.insert(u);
            }
        }

        cout << dp[g] + (cnt_g == 0 ? n - 1 : n - cnt_g) << '\n';

        for (auto &i : vis) dp[i] = -1;
    }
}
