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
const int MAXN = 202020;
ll fac[MAXN], inv[MAXN], facInv[MAXN], pow2[MAXN];
ll binom(int n, int r) {
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // Preprocessing in O(N)
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    pow2[0] = 1, pow2[1] = 2;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
        pow2[i] = 2 * pow2[i - 1] % MOD;
    }

    int n; cin >> n;

    vector<string> a(n);
    for (auto &i : a) cin >> i;

    int cnt_b = 0, cnt_w = 0;
    for (auto &i : a) for (auto &c : i) {
        if (c == 'B') cnt_b++;
        if (c == 'W') cnt_w++;
    }

    if (cnt_b > n || cnt_w > n) {
        cout << 0;
        exit(0);
    }
    
    ll s = binom(2 * n - (cnt_b + cnt_w), n - cnt_b);

    bool bb_or_ww = 0, bw = 0, wb = 0;
    int qq = 0;
    for (auto &i : a) {
        if (i == "BB" || i == "WW") bb_or_ww = 1;
        if (i == "BW" || i == "B?" || i == "?W") bw = 1;
        if (i == "WB" || i == "W?" || i == "?B") wb = 1;
        if (i == "??") qq++;
    }

    ll t = 0;
    if (bb_or_ww) {
        t = 0;
    } else if (bw && wb) {
        t = pow2[qq];
    } else if (bw || wb) {
        t = (pow2[qq] + MOD - 1) % MOD;
    } else {
        t = (pow2[qq] + MOD - 2) % MOD;
    }

    cout << (s - t + MOD) % MOD;
}
