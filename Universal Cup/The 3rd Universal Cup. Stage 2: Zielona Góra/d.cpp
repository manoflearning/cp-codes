#pragma gcc optimize("Ofast")
#pragma gcc optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

int n;
ll a[303030], pxor[303030];
ll dp[303030], pdp[66][2];

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
    for (int i = 1; i <= n; i++)
        pxor[i] = a[i] ^ pxor[i - 1];

    // naive sol
    // dp[0] = 1;
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         dp[i] = (dp[i] + (pxor[i] ^ pxor[j]) % MOD * dp[j]) % MOD;
    //     }
    // }

    // sol
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int b = 0; (1ll << b) <= 1e18; b++) {
            bool bit = (pxor[i - 1] & (1ll << b)) ? 1 : 0;
            pdp[b][bit] = (pdp[b][bit] + dp[i - 1]) % MOD;
        }

        for (int b = 0; (1ll << b) <= 1e18; b++) {
            bool bit = (pxor[i] & (1ll << b)) ? 1 : 0;
            dp[i] = (dp[i] + (1ll << b) % MOD * pdp[b][!bit]) % MOD;
        }
    }

    cout << dp[n];
}