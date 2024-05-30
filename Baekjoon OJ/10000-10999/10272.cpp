#include <bits/stdc++.h>
using namespace std;

const double INF = 1e18;

int N, x[515], y[515];
double dp[515][515];

void init() {
    for (int i = 0; i < 515; i++) {
        for (int j = 0; j < 515; j++) {
            dp[i][j] = INF;
        }
    }
}

void input() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> x[i] >> y[i];
}

inline double dist(int i, int j) {
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

double solve() {
    dp[0][0] = 0;

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            dp[i][j] = min(dp[i][j], dist(i, i-1) + dp[i-1][j]);
            dp[i][i-1] = min(dp[i][i-1], dist(i, j) + dp[i-1][j]);
        }
    }

    double ret = INF;
    for (int i = 0; i < N; i++) {
        ret = min(ret, dp[N-1][i] + dist(i, N-1));
    }

    return ret;
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
        init();

        input();

        cout << fixed;
        cout.precision(4);

        cout << solve() << '\n';
    }
}