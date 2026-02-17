#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;
constexpr int H = 353, W = 909;

struct Book {
    int h, t, idx;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    int n, h, w;
    cin >> n >> h >> w;

    vector<Book> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].h >> a[i].t;
        a[i].idx = i;
    }

    sort(all(a), [&](const Book &i, const Book &j) {
        return i.h > j.h;
    });

    int sum_t = 0;
    for (auto &i : a) sum_t += i.t;

    // vector<int> cc(1, INF);
    // for (auto &i : a) cc.push_back(i.h);
    // sort(all(cc));
    // cc.erase(unique(all(cc)), cc.end());

    vector<vector<vector<bool>>> dp(n + 1, vector<vector<bool>>(w + 1, vector<bool>(h + 1)));
    // base case
    dp[0][w][h] = 1;
    // inductive step
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= w; j++) {
            for (int k = 0; k <= h; k++) {
                if (!dp[i][j][k]) continue;

                if (a[i].h <= h && a[i].t <= j) {
                    dp[i + 1][j - a[i].t][k] = 1;
                }
                if (a[i].t <= k && (k < h || a[i].h <= j)) {
                    if (k < h) {
                        dp[i + 1][j][k - a[i].t] = 1;
                    } else {
                        dp[i + 1][j - a[i].h][k - a[i].t] = 1;
                    }
                }
            }
        }
    }

    for (int j = 0; j <= w; j++) {
        for (int k = max(0, h - sum_t + 1); k < h; k++) {
            if (dp[n][j][k]) {
                vector<int> u, s;

                int opt_j = j, opt_k = k;

                for (int i = n - 1; i >= 0; i--) {
                    if (a[i].h <= h && a[i].t + opt_j <= w && dp[i][a[i].t + opt_j][opt_k]) {
                        u.push_back(i);
                        opt_j += a[i].t;
                    } else if (a[i].t + opt_k < h && dp[i][opt_j][a[i].t + opt_k]) {
                        s.push_back(i);
                        opt_k += a[i].t;
                    } else if (a[i].t + opt_k == h && a[i].h + opt_j <= w && dp[i][a[i].h + opt_j][a[i].t + opt_k]) {
                        s.push_back(i);
                        opt_j += a[i].h;
                        opt_k += a[i].t;
                    } else {
                        assert(0);
                    }
                }

                reverse(all(s));
                // sort(all(u));
                // sort(all(s), [&](int i, int j) {
                //     return a[i].h > a[j].h;
                // });

                assert(!u.empty() && !s.empty());

                cout << "upright" << ' ';
                for (auto &i : u) cout << a[i].idx + 1 << ' ';
                cout << '\n';
                cout << "stacked" << ' ';
                for (auto &i : s) cout << a[i].idx + 1 << ' ';
                cout << '\n';

                exit(0);
            }
        }
    }
    cout << "impossible\n";
}
