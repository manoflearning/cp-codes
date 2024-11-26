#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998244353;
const int MAXN = 101;

int n, m, k;
string w;

ll dp[MAXN][1 << 3][1 << 4];

void modify(int i, int bit, int vis, int nbit) {
    int nvis = (bit << 1) | nbit;
    dp[i + 1][nbit][nvis] = (
        dp[i + 1][nbit][nvis] + dp[i][bit][vis]
    ) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k >> w;

    // base case
    for (int bit = 0; bit < (1 << k); bit++) {
        dp[k][bit][0] = 1;
    }

    // inductive step
    for (int i = k; i + 1 < MAXN; i++) {
        for (int bit = 0; bit < (1 << k); bit++) {
            for (int vis = 0; vis < (1 << (k + 1)); vis++) {
                modify(i, bit, vis, (bit << 1) % (1 << k));
                modify(i, bit, vis, (bit << 1) % (1 << k) + 1);
            }
        }
    }

    
}
