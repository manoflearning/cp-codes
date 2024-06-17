#pragma gcc optimize("Ofast")
#pragma gcc optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

// int flag;
// struct Seg {
//     void init(int n) {}
//     void add(int l, int r, ll x, int n = 1, int nl = 1, int nr = flag) {}
//     ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {}
// }seg;

int n;
ll a[303030], pxor[303030];
ll dp[303030];

ll XOR(int l, int r) { return pxor[r] ^ pxor[l - 1]; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // prefix xor
    // for (int i = 1; i <= n; i++)
        // pxor[i] = a[i] ^ pxor[i - 1];

    // solve
    unordered_map<ll, ll> mp;
    mp[a[1]] = 1;
    // seg.init(n);
    // seg.add(1, 1, XOR(1, n) % MOD * 1);
    for (int i = 2; i <= n; i++) {
        auto tmp = mp;
        mp.clear();

        for (auto& [x, y] : tmp) {
            mp[a[i]] += x % MOD * y; // range [i, i]
            mp[a[i]] %= MOD;
            mp[x ^ a[i]] += y; // range [j, i]
            mp[x ^ a[i]] %= MOD;
        }

        // ll res = seg.query(1, i - 1) ^ XOR(i, n);
        // seg.add(i, i, XOR(i, n));
    }

    // output
    ll ans = 0;
    for (auto& [x, y] : mp) {
        ans = (ans + x % MOD * y) % MOD;
    }

    cout << ans;
}