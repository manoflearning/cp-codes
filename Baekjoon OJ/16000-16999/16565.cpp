// N = 1, 2, 3 -> ans = 0
// 4 <= N < 8 -> ans = 13C1 * (52-4)C(N-4)

// 8 <= N < 12 
// ans = 13C1 * (52-4)C(N-4) - 13C2 * (52-8)C(N-8)

// 12 <= N < 16
// ans = 13C1 * (52-4)C(N-4) - 13C2 * (52-8)C(N-8) + 13C3 * (52-12)C(N-12)

// 16 <= N < 20 -> ans = 13C4 * (52-16)C(N-16)

// ...

// 36 <= N < 40 -> ans = 13C9 * (52-36)C(N-36)
// N >= 40 -> ans = 52CN (pigeon hole)

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 10'007;

int n, binom[101][101];

void preprocessing() {
    binom[0][0] = 1;
    // binom[1][0] = binom[1][1] = 1;
    for (int i = 1; i <= 100; i++) {
        for (int j = 0; j <= i; j++) {
            binom[i][j] = binom[i - 1][j];
            if (j > 0) binom[i][j] = (binom[i][j] + binom[i - 1][j - 1]) % MOD;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    cin >> n;
    
    if (n <= 3) cout << 0;
    // else if (40 <= n) cout << binom[52][n];
    else {
        int ans = 0;
        for (int cnt = 1; cnt <= 13; cnt++) {
            if (n < 4 * cnt) break;
            int res = binom[13][cnt] * binom[52 - 4 * cnt][n - 4 * cnt] % MOD;
            ans = (ans + (cnt & 1 ? res : -res)) % MOD;
        }
        ans = (ans + MOD) % MOD;
        
        // for (int x = 1; x <= 13; x++) {
        //     ans = (ans + binom[52 - 4 * x][n - 4]) % MOD;
        // }
        cout << ans;
    }
}