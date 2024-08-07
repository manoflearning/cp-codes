#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 303030;
const int MOD = 998'244'353;

int n, p[MAXN];
int smin[MAXN];
ll ans = 0;

void init() {
    ans = 0;
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];
}

void buildSmin() {
    smin[n] = p[n];
    for (int i = n - 1; i >= 1; i--) 
        smin[i] = min(p[i], smin[i + 1]);
}

void bottomup() {
    vector<ll> dp(n + 1), dpsum(n + 1);

    // base case
    dp[1] = 1;
    dpsum[1] = dp[1];

    stack<int> stk;
    stk.push(1);
    ll stksum = dp[1];

    // inductive step
    for (int i = 2; i <= n; i++) {
        while (!stk.empty() && p[stk.top()] > p[i]) {
            stksum = (stksum - dp[stk.top()] + MOD) % MOD;
            stk.pop();
        }

        if (stk.empty()) {
            dp[i] = (dpsum[i - 1] + 1) % MOD;
        }
        else {
            dp[i] = (dpsum[i - 1] - dpsum[stk.top()]) % MOD;
            dp[i] = (dp[i] + MOD) % MOD;
            dp[i] = (dp[i] + stksum) % MOD;
        }

        stk.push(i);
        stksum = (stksum + dp[i]) % MOD;
        dpsum[i] = (dp[i] + dpsum[i - 1]) % MOD;
    }

    // get answer
    for (int i = 1; i <= n; i++) {
        if (p[i] <= smin[i]) {
            ans = (ans + dp[i]) % MOD;
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

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        buildSmin();

        bottomup();

        cout << ans << '\n';
    }
}