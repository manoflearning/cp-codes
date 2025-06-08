#pragma gcc optimize("O3")
#pragma gcc optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int n, m, p;
vector<int> h;
int min_h, sum_h;
vector<vector<double>> dp1;
vector<vector<double>> dp2;

void init() {
    min_h = INF, sum_h = 0;
    dp1.clear();
    dp2.clear();
}

void input() {
    cin >> n >> m >> p;
    h.resize(n);
    for (auto &i : h) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // chrono::duration<double, milli> cal_dp1, cal_dp2;

    cout << fixed;
    cout.precision(6);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        for (auto &i : h) {
            min_h = min(min_h, i);
            sum_h += i;
        }

        const double P = (double)p / 100, Q = (double)(100 - p) / 100;

        {
            // auto st = chrono::high_resolution_clock::now();

            dp1.resize(m + 1, vector<double>(sum_h - n * min_h + 1));
            
            // base case
            dp1[0][0] = 1;

            // inductive step
            for (int i = 0; i + 1 <= m; i++) {
                for (int j = 0; j + 1 <= sum_h - n * min_h; j++) {
                    if (i < j) break;
                    dp1[i + 1][j] += dp1[i][j] * P;
                    dp1[i + 1][j + 1] += dp1[i][j] * Q;
                }
            }

            // auto et = chrono::high_resolution_clock::now();
            // cal_dp1 += et - st;
        }

        {
            // auto st = chrono::high_resolution_clock::now();

            dp2.resize(m + 1, vector<double>(n * (min_h - 1) + 1));

            // base case
            dp2[0][n * (min_h - 1)] = 1;

            // inductive step
            for (int i = 1; i <= m; i++) {
                for (int j = 0; j <= n * (min_h - 1); j++) {
                    double res1 = dp2[i - 1][j], res2 = dp2[i - 1][j];
                    if (j + n <= n * (min_h - 1)) res1 = max(res1, dp2[i - 1][j + n]);
                    if (j + 1 <= n * (min_h - 1)) res2 = max(res2, dp2[i - 1][j + 1]);
                    dp2[i][j] = res1 * P + res2 * Q;
                }
            }

            // auto et = chrono::high_resolution_clock::now();
            // cal_dp2 += et - st;
        }

        double ans = 0;
        for (int i = 0; i <= m; i++) {
            int cnt_op1 = min(min_h - 1, max(0, i - (sum_h - n * min_h)));
            ans += dp1[i][sum_h - n * min_h] * dp2[m - i][cnt_op1 * n];
        }

        cout << ans << '\n';
    }

    // cout << fixed;
    // cout.precision(0);
    // cout << cal_dp1.count() << "ms\n";
    // cout << cal_dp2.count() << "ms\n";
}
