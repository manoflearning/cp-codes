#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MOD = 1e9 + 7;
const ll INF = 1e18;

const int MAXN = 111;

int N;
ll X, Y, Z;
ll A[MAXN], B[MAXN];
ll cost = 0;

void input() {
    cin >> N >> X >> Y >> Z;
    for (int i = 1; i <= N; i++)
        cin >> A[i] >> B[i];
}

void bottom_up() {
    vector<vector<ll>> dp(101, vector<ll>(2020, INF));

    // base case
    int diff = abs(A[1] - B[1]);
    for (int now = 0; now <= diff; now++) {
        int nxt = diff - now;
        if (A[1] > B[1]) dp[1][1010 + nxt] = min(dp[1][1010 + nxt], now * Y);
        if (A[1] < B[1]) dp[1][1010 - nxt] = min(dp[1][1010 - nxt], now * X);
        if (diff == 0) dp[1][1010] = 0;
    }

    // inductive step
    for (int i = 2; i <= N; i++) {
        int diff = abs(A[i] - B[i]);
        for (int now = 0; now <= diff; now++) {
            if (A[i] >= B[i]) {
                for (int j = 0; j < 2020; j++) {
                    if (dp[i - 1][j] == INF) continue;
                    ll res = 0;
                    res += dp[i - 1][j] + Z * abs(1010 - j); // prv cost
                    res += now * Y; // now cost

                    dp[i][j + (diff - now)] = min(dp[i][j + (diff - now)], res);
                }
            }
            if (A[i] < B[i]) {
                for (int j = 0; j < 2020; j++) {
                    if (dp[i - 1][j] == INF) continue;
                    ll res = 0;
                    res += dp[i - 1][j] + Z * abs(1010 - j); // prv cost
                    res += now * X; // now cost

                    dp[i][j - (diff - now)] = min(dp[i][j - (diff - now)], res);
                }
            }
            if (diff == 0) {
                for (int j = 0; j < 2020; j++) {
                    if (dp[i - 1][j] == INF) continue;
                    ll res = 0;
                    res += dp[i - 1][j] + Z * abs(1010 - j);

                    dp[i][j] = min(dp[i][j], res);
                }
            }
        }
    }

    // calculate total cost
    cost = dp[N][1010];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    bottom_up();

    cout << cost;
}