#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int SZN = 101010;
const int MOD = 1e9 + 7;

string n;
ll dp[SZN][2][2];

void init() {
    memset(dp, -1, sizeof(dp));
}

void input() { cin >> n; }

ll f(int i, bool is_st, bool is_max) {
    auto &ret = dp[i][is_st][is_max];
    if (ret != -1) return ret;
    if (i == sz(n)) return ret = 1;

    ret = 0;

    if (is_st) {
        if (is_max) {
            for (int x = 1; x <= 2; x++) {
                if (x + '0' < n[i]) {
                    ret += f(i + 1, 0, 0);
                    ret %= MOD;
                } else if (x + '0' == n[i]) {
                    ret += f(i + 1, 0, 1);
                    ret %= MOD;
                }
            }
        } else {
            ret = 2 * f(i + 1, 0, 0);
            ret %= MOD;
        }
    } else {
        if (is_max) {
            for (int x = 0; x <= 2; x++) {
                if (x + '0' < n[i]) {
                    ret += f(i + 1, 0, 0);
                    ret %= MOD;
                } else if (x + '0' == n[i]) {
                    ret += f(i + 1, 0, 1);
                    ret %= MOD;
                }
            }
        } else {
            ret = 3 * f(i + 1, 0, 0);
            ret %= MOD;
        }
    }
    
    return ret;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        cout << "Case #" << tt << endl;
        
        ll ans = 0;
        for (int i = 0; i < sz(n); i++) {
            ans = (ans + f(i, 1, (i == 0 ? 1 : 0))) % MOD;
        }
        cout << ans << endl;
    }
}
