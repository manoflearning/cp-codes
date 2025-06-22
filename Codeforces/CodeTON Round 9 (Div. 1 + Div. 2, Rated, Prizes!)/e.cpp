#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        // base case
        // vector<ll> cnt_gte_1(n + 1);
        ll sum1 = 0, sum2 = 0;
        
        // inductive step
        for (int i = 3; i <= n; i++) {
            // vector<ll> tmp_gte_1(i + 1);

            // for (int j = 2; j <= i - 1; j++) {
            //     tmp_gte_1[j] = (tmp_gte_1[j] + cnt_gte_1[j]) % MOD;
            //     tmp_gte_1[i] = (tmp_gte_1[i] + j * cnt_gte_1[j]) % MOD;
            // }

            // sum1 = (sum1 + sum1) % MOD;
            sum1 = (sum1 + sum2) % MOD;
            sum2 = (sum2 + i * sum2) % MOD;

            // cnt_gte_1 = tmp_gte_1;
            // cnt_gte_1[i - 1] = (cnt_gte_1[i - 1] + 1) % MOD;

            sum1 = (sum1 + 1) % MOD;
            sum2 = (sum2 + (i - 1)) % MOD;

            // DEBUG
            // cout << "n = " << i << '\n';
            // for (auto &j : cnt_gte_1) cout << j << ' ';
            // cout << '\n';
            // cout << sum1 << ' ' << sum2 << '\n';
            // cout << '\n';
        }

        // DEBUG
        // cout << "n = " << n << '\n';
        // for (auto &i : cnt_gte_1) cout << i << ' ';
        // cout << '\n';
        // cout << '\n';

        // ll ans = 0;
        // for (auto &i : cnt_gte_1) {
        //     ans = (ans + i) % MOD;
        // }
        // cout << (ans + 1) << '\n';
        cout << (sum1 + 1) << '\n';
    }
}
