#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 235'813;
const int MAXN = 101010;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
ll lcm(ll x, ll y) { return x * y * gcd(x, y); }

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) { // O(1)
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}
void preprocessing() {
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }
}

int n;
ll a[MAXN], b[MAXN];
ll sum = 0;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int ans = 0;

void solve() {
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] * ((n - i + 1) & 1 ? 1 : -1) * binom(n - 1, i - 1) % MOD;
        b[i] = (b[i] + MOD) % MOD;
        sum = (sum + b[i]) % MOD;
    }
    
    for (int i = 1; i <= n; i++) {
        ll now = (sum + MOD - b[i]) % MOD;
        
        ll l = now, r = MOD - now;
        ll w = binom(n - 1, i - 1) * ((n - i + 1) & 1 ? 1 : -1);

        ll x = -now * power(w, MOD - 2) % MOD;
        if (x < 0) x += MOD;

        bool isHot = false;
        if (-100'000 <= x && x <= 100'000 && x != a[i]) isHot = true;
        x -= MOD;
        if (-100'000 <= x && x <= 100'000 && x != a[i]) isHot = true;

        if (isHot) ans++;

        // bool isHot = false;

        // if ((n - i + 1) & 1) {
        //     if (l % w == 0 && l / w <= a[i] + 100'000) isHot = true;
        //     if (r % w == 0 && r / w <= 100'000 - a[i]) isHot = true;
        // }
        // else {
        //     if (r % w == 0 && r / w <= a[i] + 100'000) isHot = true;
        //     if (l % w == 0 && l / w <= 100'000 - a[i]) isHot = true;
        // }

        // if (isHot) ans++;

        // ll lcl = l * power(w, MOD - 2);
        // ll lcr = r * power(w, MOD - 2);

        // bool isHot = false;
        // if ((n - i + 1) & 1) {
        //     if (lcl / w <= a[i] + 100'000) isHot = true;
        //     if (lcr / w <= 100'000 - a[i]) isHot = true;
        // }
        // else {
        //     if (lcr / w <= a[i] + 100'000) isHot = true;
        //     if (lcl / w <= 100'000 - a[i]) isHot = true;
        // }
        
        // if (isHot) ans++;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    input();

    solve();

    cout << ans;
}