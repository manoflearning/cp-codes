#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 998244353;
const int MAXN = 3e5 + 35;
ll fact[MAXN], inv[MAXN];
ll exp(ll x, ll e) {
    ll ret = 1;
    while(e) {
        if(e & 1) ret = ret * x % MOD;
        x = x * x % MOD; e >>= 1;
    }
    return ret;
}
ll C(ll k, ll r) {
    if(r < 0 || k < r) return 1;
    ll res = fact[k] * (inv[k - r] * inv[r] % MOD) % MOD;
    return res;
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for(ll i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv[MAXN - 1] = exp(fact[MAXN - 1], MOD - 2);
    for(ll i = MAXN - 1; i >= 1; i--) {
        inv[i - 1] = inv[i] * i % MOD;
    }

    ll E = 0;
    for(ll i = 8; i >= 2; i--) {
        ll res = C(8, i) * C(8, 10 - i) % MOD;
        if(i & 1) E = (E + res) % MOD;
    }
    cout << E << '\n';
}
