#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int MAXN = 202020;

ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
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

int N, M;
string A, B;
int cntA[26], cntB[26];
vector<ll> dp[26], psum[26];

void bottomup() {
    for (int i = 0; i < 26; i++) {
        dp[i].resize(cntB[i] + 1);
        psum[i].resize(cntB[i] + 2);
    }

    // base case
    if (cntA[25] <= cntB[25]) {
        dp[25][cntB[25] - cntA[25]] = 1;
    }
    for (int i = cntB[25]; i >= 0; i--) {
        psum[25][i] = (dp[25][i] + psum[25][i + 1]) % MOD;
    }

    // inductive step
    for (int i = 24; i >= 0; i--) {
        for (int j = 0; j <= cntA[i]; j++) {
            if (cntB[i] < j) break;
            int k = cntA[i] - j;
            if (k >= sz(psum[i + 1])) continue;
            dp[i][cntB[i] - j] = binom(cntA[i], j) * psum[i + 1][k] % MOD;
        }

        for (int j = cntB[i]; j >= 0; j--) {
            psum[i][j] = (dp[i][j] + psum[i][j + 1]) % MOD;
        }
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

    cin >> N >> M >> A >> B;

    for (auto& i : A) cntA[i - 'A']++;
    for (auto& i : B) cntB[i - 'A']++;

    bottomup();

    ll ans = psum[0][0];
    ans = ans * fac[N] % MOD;
    for (int i = 0; i < 26; i++)
        ans = ans * facInv[cntA[i]] % MOD;
    
    cout << ans << '\n';
}