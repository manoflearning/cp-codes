#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const int MAXN = 1010101;

int n;
string s;

void init() {}

void input() { cin >> n >> s; }

// group1
int isMatch(int p1, int p2) {
    if (s[p1] == '(' && s[p2] == ')') return 1;
    if (s[p1] == '{' && s[p2] == '}') return 1;
    return 0;
}

int dp[212][212];
ll group1() {
    // init (group1 only)
    for (int i = 0; i < 212; i++)
        memset(dp[i], 0, sizeof(dp[i]));

    // base case
    for (int l = 0, r = 1; r < n; l++, r++) {
        if (isMatch(l, r)) dp[l][r] = 1;
    }

    // inductive step
    for (int len = 4; len <= n; len += 2) {
        for (int l = 0, r = len - 1; r < n; l++, r++) {
            if (s[l] == ')' || s[l] == '}') continue;
            if (s[r] == '(' || s[r] == '{') continue;
            if (isMatch(l, r) && dp[l + 1][r - 1]) {
                dp[l][r] = 1;
                continue;
            }
            for (int i = l + 1; i + 2 <= r; i += 2) {
                if (dp[l][i] && dp[i + 1][r]) { dp[l][r] = 1; break; }
            }
        }
    }

    // get result
    ll ret = 0;
    for (int l = 0; l < n; l++) {
        for (int r = l + 1; r < n; r += 2) {
            ret += dp[l][r];
        }
    }
    return ret;
}

// group2
bool isGroup2() {
    for (auto& c : s)
        if (c == '{' || c == '}') return false;
    return true;
}
ll cnt[2 * MAXN];
ll group2() {
    // solve
    ll ret = 0;

    int sum = MAXN, mn = MAXN;
    cnt[sum]++;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') sum++;
        else {
            ret += cnt[sum] * (cnt[sum] - 1) / 2;
            cnt[sum] = 0;
            sum--;
        }
        cnt[sum]++;
        mn = min(mn, sum);
    }

    for (int i = mn; i <= sum; i++) {
        ret += cnt[i] * (cnt[i] - 1) / 2;
        cnt[i] = 0; // init (group2 only)
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        if (n <= 200) cout << group1() << '\n';
        else if (isGroup2()) cout << group2() << '\n';
        else cout << 0 << '\n';

        cout << flush;
    }
}