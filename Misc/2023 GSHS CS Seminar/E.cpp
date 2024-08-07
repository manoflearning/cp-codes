#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXN = 303030;

int n, m;
ll a[MAXN], dp[MAXN];
int prv[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void solve() {
    memset(dp, -1, sizeof(dp));

    dp[0] = 0;

    deque<pll> dq1, dq2;
    dq1.push_back({ 0 - a[1], 1 });
    dq2.push_back({ 0 + a[1], 1 });
    for (int i = 1; i <= n; i++) {
        if (!dq1.empty() && dq1.front().sc <= i - m) dq1.pop_front();
        if (!dq2.empty() && dq2.front().sc <= i - m) dq2.pop_front();

        if (!dq1.empty() && dp[i] < a[i] + dq1.front().fr) {
            dp[i] = a[i] + dq1.front().fr;
            prv[i] = dq1.front().sc - 1;
        }
        if (!dq2.empty() && dp[i] < -a[i] + dq2.front().fr) {
            dp[i] = -a[i] + dq2.front().fr;
            prv[i] = dq2.front().sc - 1;
        }

        if (i == n) break;

        while (!dq1.empty() && dq1.back().fr <= dp[i] - a[i + 1]) dq1.pop_back();
        dq1.push_back({ dp[i] - a[i + 1], i + 1 });
        while (!dq2.empty() && dq2.back().fr <= dp[i] + a[i + 1]) dq2.pop_back();
        dq2.push_back({ dp[i] + a[i + 1], i + 1 });
    }
}

void output() {
    cout << dp[n] << '\n';
    vector<pll> ans;
    int now = n;
    while (now > 0) {
        ans.push_back({ prv[now] + 1, now });
        now = prv[now];
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto& i : ans) {
        cout << i.fr << ' ' << i.sc << '\n';
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    output();
}