#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int MAX = 10101;

ll fac[MAX], inv[MAX], facInv[MAX];
ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int n;
vector<int> a, cnt, pcnt;
int ub;
vector<vector<ll>> dp;

void init() {
    a.clear();
    cnt.clear();
    pcnt.clear();
    dp.clear();
}

void input() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void coor_comp() {
    vector<int> cc;
    cc.push_back(-1);
    for (int i = 1; i <= n; i++)
        cc.push_back(a[i]);

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    ub = sz(cc) - 1;
    cnt.resize(sz(cc) + 5);
    pcnt.resize(sz(cc) + 5);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(all(cc), a[i]) - cc.begin();
        cnt[a[i]]++;
    }

    for (int i = ub; i >= 1; i--) {
        pcnt[i] = cnt[i] + pcnt[i + 1];
    }
}

void bottomup() {
    dp.resize(ub + 5, vector<ll>(n + 5));

    dp[ub - 1][2] = 1;
    for (int i = ub - 2; i >= 1; i--) {
        for (int j = 2; j <= n / 2; j++) {
            int slot_cnt = (j - 1) - (pcnt[i + 1] - j);

            if (j == n / 2) slot_cnt++;
            if (slot_cnt < 0) continue;

            if (slot_cnt >= cnt[i]) {
                dp[i][j] += dp[i + 1][j] * binom(slot_cnt, cnt[i]);
                dp[i][j] %= MOD;
            }
            if (slot_cnt >= cnt[i] - 1) {
                dp[i][j + 1] += dp[i + 1][j] * binom(slot_cnt, cnt[i] - 1) % MOD;
                dp[i][j + 1] %= MOD;
            }
        }
    }

    // dp[ub - 1][1] = 1;
    // for (int i = ub - 2; i >= 1; i--) {
    //     for (int j = 0; j <= n / 2; j++) {
    //         dp[i][j] += dp[i + 1][j + cnt[i]] * binom(j + cnt[i], j);
    //         dp[i][j] %= MOD;
    //         dp[i][j + 1] += dp[i + 1][j + cnt[i]] * binom(j + cnt[i], j + 1);
    //         dp[i][j] %= MOD;
    //     }
    // }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAX; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        coor_comp();

        if (cnt[ub] >= 2) {
            cout << 0 << '\n';
            continue;
        }
        if (cnt[ub - 1] >= 2) {
            cout << 0 << '\n';
            continue;
        }

        if (n == 2) {
            cout << 1 << '\n';
            continue;
        }

        bottomup();

        cout << dp[1][n / 2] << '\n';
    }
}
