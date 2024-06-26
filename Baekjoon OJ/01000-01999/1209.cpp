#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n;
vector<ll> a, b;
ll dp[2020][2020];

void init() {
    for (int i = 0; i < 2020; i++) {
        for (int j = 0; j < 2020; j++) {
            dp[i][j] = -1;
        }
    }
}

ll f(int now, int idx) {
    ll& ret = dp[now][idx];
    if (ret != -1) return ret;
    if (now == n + 1) return ret = 0;

    ret = INF;

    ret = min(ret, f(now + 1, idx) + abs(a[now] - b[idx]));
    if (idx + 1 <= n)
        ret = min(ret, f(now, idx + 1));

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    cin >> n;
    a.resize(n + 1, -INF);
    for (int i = 1; i <= n; i++) cin >> a[i];

    b = a;
    sort(b.begin(), b.end());

    ll ans = INF;
    ans = min(ans, f(1, 1));

    sort(b.begin() + 1, b.end(), [&](ll u, ll v) {
        return u > v;
    });

    init();

    ans = min(ans, f(1, 1));

    cout << ans;

    return 0;
}