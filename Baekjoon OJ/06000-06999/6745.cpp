#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 111, MAXM = 111;
const ll INF = 1e18;

int n, m;
ll a[MAXN], b[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];
}

bool f(ll x) {
    vector<vector<ll>> dp(MAXN, vector<ll>(MAXM, -INF));

    dp[1][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -INF) continue;
            for (ll p = 0; p <= m - j && p * a[i] <= x; p++) {
                ll q = (x - p * a[i]) / b[i];
                dp[i + 1][j + p] = max(dp[i + 1][j + p], dp[i][j] + q);
            }
        }
    }
    return dp[n + 1][m] >= m;
}

ll bs() {
    ll l = 1, r = INF;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (f(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
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
        input();

        cout << bs() << '\n';
    }
}
