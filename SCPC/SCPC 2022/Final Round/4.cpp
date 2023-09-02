// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

int n;
vector<int> a;

int ub;
vector<int> cnt;

void init() {}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

void cc() {
    vector<int> c = a;
    c.push_back(-1);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (auto& i : a) {
        i = lower_bound(all(c), i) - c.begin();
    }
    ub = sz(c) - 1;
}

int dp[15][2][1 << 15];
int G1() {
    memset(dp, -1, sizeof(dp));

    for (int v = 0; v < n; v++) {
        dp[v][0][1 << v] = 0;
        dp[v][1][1 << v] = 1;
    }

    for (int t = 0; t < n - 1; t++) { // O(n * n * 2 * n * 2^n);
        for (int v = 0; v < n; v++) {
            for (int isB = 0; isB < 2; isB++) {
                for (int bit = 0; bit < (1 << n); bit++) {
                    if (dp[v][isB][bit] == -1) continue;
                    for (int u = 0; u < n; u++) {
                        if ((1 << u) & bit) continue;
                        if (isB != (a[v] >= a[u])) continue;
                        
                        int canB = (a[v] <= a[u]);
                        dp[u][0][bit | (1 << u)] = max(dp[u][0][bit | (1 << u)], dp[v][isB][bit]);
                        if (!canB) continue;
                        dp[u][1][bit | (1 << u)] = max(dp[u][1][bit | (1 << u)], 1 + dp[v][isB][bit]);
                    }
                }
            }
        }
    }
    
    int ret = 0;
    for (int v = 0; v < n; v++) {
        for (int isB = 0; isB < 2; isB++) {
            for (int bit = 0; bit < (1 << n); bit++) {
                if (dp[v][isB][bit] == -1) continue;
                for (int u = 0; u < n; u++) {
                    ret = max(ret, dp[v][isB][bit]);
                }
            }
        }
    }
    return ret;
}

// int solve() {
//     int ret = 0;
//     for (int st = 1; st <= n; st++) {
//         if (!cnt[st]) continue;
//         cnt[st]--;
//         for (int en = st; en <= n; en++) {
//             if (!cnt[en]) continue;
//             cnt[en]--;
//             ret = max(ret, f(st, en));
//             cnt[en]++;
//         }
//         cnt[st]++;
//     }
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        sort(all(a));

        if (n <= 15) cout << G1() << '\n';
        else cout << 0 << '\n';

        // cc();

        // cnt.resize(n + 1);
        // for (auto& i : a) cnt[i]++;

        //cout << solve() << '\n';

        cout << flush;
    }
}