#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const double PI = 3.14159265358979323846264338327950288;
const double INF = 1e18;
const double EPS = 1e-9;

int n;
struct Point {
    double x, y;
};
vector<Point> p;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    p.resize(n);
    for (auto &[x, y] : p) cin >> x >> y;

    double ans = 1e18;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            double theta;
            if (p[i].x != p[j].x) {
                theta = atan((double)(p[i].y - p[j].y) / (p[i].x - p[j].x));
            } else {
                theta = PI / 2;
            }

            vector<int> ord(n);
            iota(all(ord), 0);

            vector<Point> pp(n);
            for (int k = 0; k < n; k++) {
                pp[k].x = (p[k].x - p[i].x) * cos(-theta) - (p[k].y - p[i].y) * sin(-theta);
                pp[k].y = (p[k].x - p[i].x) * sin(-theta) + (p[k].y - p[i].y) * cos(-theta);
            }

            vector<vector<double>> dp(n, vector<double>(1 << n, INF));
            
            // base case
            for (int v = 0; v < n; v++)
                dp[v][1 << v] = 0;

            // inductive step
            for (int bit = 0; bit < (1 << n); bit++)  {
                for (int v = 0; v < n; v++) {
                    if (abs(dp[v][bit] - INF) < EPS) continue;

                    for (int nxt = 0; nxt < n; nxt++) {
                        if (bit & (1 << nxt)) continue;
                        int nbit = bit | (1 << nxt);
                        double dist = abs(pp[v].x - pp[nxt].x) + abs(pp[v].y - pp[nxt].y);
                        dp[nxt][nbit] = min(dp[nxt][nbit], dp[v][bit] + dist);
                    }
                }
            }

            for (int v = 0; v < n; v++)
                ans = min(ans, dp[v][(1 << n) - 1]);
        }
    }

    cout << fixed;
    cout.precision(10);
    cout << ans;
}
