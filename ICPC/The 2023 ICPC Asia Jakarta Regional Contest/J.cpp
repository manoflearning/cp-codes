#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int MAXN = 5050;

int N, A[MAXN];
ll dp[MAXN][MAXN][2], power2[MAXN];

void init() {
    memset(dp, -1, sizeof(dp));
    power2[0] = 1;
    for (int i = 1; i < MAXN; i++)
        power2[i] = 2 * power2[i - 1] % MOD;
}

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];
}

ll f(int i, int inQueue, bool isFirst) {
    ll& ret = dp[i][inQueue][isFirst];
    if (ret != -1) return ret;
    if (i == N + 1) return ret = 1;
    if (inQueue == 0) return ret = 0;

    ret = 0;
    if (inQueue >= 2) {
        ret = (ret + f(i, inQueue - 1, true)) % MOD;
    }
    if (isFirst || A[i - 1] < A[i]) {
        ret = (ret + power2[inQueue - 1] * f(i + 1, inQueue + 1, false)) % MOD;
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    cout << f(2, 1, true);
}