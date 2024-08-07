// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const int MAXN = 5050;
const int MOD = 1e9 + 7;

int n, k;
ll C[MAXN][MAXN];

void preprocess() {
    C[0][0] = 1;
    C[1][0] = C[1][1] = 1;
    for (int i = 2; i < MAXN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i - 1; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
        C[i][i] = 1;
    }
}

void init() {}

void input() { cin >> n >> k; }

ll bottomup() {
    if (k < n - 1 || 2 * n - 1 <= k) return 0;
    
    vector<ll> prv(n);
    prv[0] = 1;
    
    for (int len = 2; len <= n; len++) {
        vector<ll> now(n);
        now[0] = 2 * prv[0] % MOD;
        for (int cnt = 1; cnt < sz(now); cnt++) {
            now[cnt] = (2 * prv[cnt] + (len - 2) * prv[cnt - 1]) % MOD;
        }
        prv = now;
    }
    return prv[k - (n - 1)];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocess();

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        cout << bottomup() << '\n';

        cout << flush;
    }
}