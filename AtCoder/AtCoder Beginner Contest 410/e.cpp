#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 3030;
const int INF = 1e9 + 7;

int n, h, m;
int a[N], b[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> h >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    int ans = 0;

    vector<int> dp(h + 1, INF);
    
    // base case
    dp[0] = 0;

    // inductive step
    for (int i = 0; i < n; i++) {
        vector<int> tmp(h + 1, INF);
        for (int j = 0; j <= h; j++) {
            if (dp[j] == INF) continue;
            tmp[j] = min(tmp[j], dp[j] + b[i]);
            if (j + a[i] <= h) tmp[j + a[i]] = min(tmp[j + a[i]], dp[j]);
        }
        dp = tmp;

        // cout << i << '\n';
        // for (auto &i : dp) cout << i << ' ';
        // cout << '\n';

        for (int j = 0; j <= h; j++) {
            if (dp[j] <= m) {
                ans = i + 1;
            }
        }
    }

    cout << ans;
}
