#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int r, c;
ll p;

double dp[1010][1010], prob[1010][1010];

double choice(int y1, int x1, int y2, int x2) {
    if (y1 == r - 1 || x1 == c - 1) return 1;

    int rp = r - y1, cp = c - x1;
    if (rp == cp) return 0.5;
    else if (rp < cp) {
        if (x1 + 1 == x2) return 0.625;
        else return 0.375;
    }
    else if (rp > cp) {
        if (y1 + 1 == y2) return 0.625;
        else return 0.375;
    }
    return 1;
}

double get_prob(int y1, int x1, int y2, int x2) {
    if (y2 > 0 && x2 > 0) {
        int y3 = (y1 == y2 ? y2 - 1 : y2);
        int x3 = (x1 == x2 ? x2 - 1 : x2);

        double res1 = prob[y1][x1] * choice(y1, x1, y2, x2);
        double res3 = prob[y3][x3] * choice(y3, x3, y2, x2);
        return res1 / (res1 + res3);
    }
    else return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> r >> c >> p;

    prob[0][0] = 1.0;
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            // cout << prob[y][x] << ' ';

            int rp = r - y, cp = c - x;

            if (y == r - 1 && x == c - 1) continue;
            else if (y == r - 1) prob[y][x + 1] += prob[y][x];
            else if (x == c - 1) prob[y + 1][x] += prob[y][x];
            else if (rp < cp) {
                prob[y + 1][x] += 0.375 * prob[y][x];
                prob[y][x + 1] += 0.625 * prob[y][x];
            }
            else if (rp > cp) {
                prob[y + 1][x] += 0.625 * prob[y][x];
                prob[y][x + 1] += 0.375 * prob[y][x];
            }
            else {
                prob[y + 1][x] += 0.5 * prob[y][x];
                prob[y][x + 1] += 0.5 * prob[y][x];
            }
        }
        // cout << '\n';
    }

    dp[0][0] = 0.0;
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            cout << dp[y][x] << ' ';

            int rp = r - y, cp = c - x;

            if (y == r - 1 && x == c - 1) continue;
            else if (x == c - 1) dp[y + 1][x] += (dp[y][x] + (double)p / 4) * get_prob(y, x, y + 1, x);
            else if (y == r - 1) dp[y][x + 1] += (dp[y][x] + (double)p / 4) * get_prob(y, x, y, x + 1);
            else if (rp < cp) {
                dp[y + 1][x] += dp[y][x] * get_prob(y, x, y + 1, x);
                dp[y][x + 1] += (dp[y][x] + (double)p / 40) * get_prob(y, x, y, x + 1);
            }
            else if (rp > cp) {
                dp[y + 1][x] += (dp[y][x] + (double)p / 40) * get_prob(y, x, y + 1, x);
                dp[y][x + 1] += dp[y][x] * get_prob(y, x, y, x + 1);
            }
            else {
                dp[y + 1][x] += dp[y][x] * get_prob(y, x, y + 1, x);
                dp[y][x + 1] += dp[y][x] * get_prob(y, x, y, x + 1);
            }
        }
        cout << '\n';
    }

    cout << fixed;
    cout.precision(8);

    cout << dp[r - 1][c - 1];
}