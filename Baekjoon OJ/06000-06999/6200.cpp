#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MOD = 1e9 + 7;
const ll INF = 1e18;

// ub = 101110011
//    = 

ll st, en;
ll dp[33][66][2], ub;
ll ans;

ll f(int x, int cnt, bool hit_ub) {
    // base case
    if (x == -1) return (cnt >= 0);

    // memoization
    ll& ret = dp[x][cnt + 33][hit_ub];
    if (ret != -1) return ret;

    // inductive step
    ret = 0;
    if (hit_ub) {
        if (ub & (1 << x)) {
            ret += f(x - 1, cnt - 1, 1);
            ret += f(x - 1, cnt + 1, 0);
        }
        else {
            ret += f(x - 1, cnt + 1, 1);
        }
    }
    else {
        ret += f(x - 1, cnt - 1, 0);
        ret += f(x - 1, cnt + 1, 0);
    }
    return ret;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    ub = en;
    for (int b = 0; ; b++) {
        if (ub < (1ll << (b + 1))) {
            ans += f(b - 1, -1, 1);
            break;
        }
        else {
            ans += f(b - 1, -1, 0);
        }
    }

    if (st == 1) return;

    memset(dp, -1, sizeof(dp));
    ub = st - 1;
    for (int b = 0; ; b++) {
        if (ub < (1ll << (b + 1))) {
            ans -= f(b - 1, -1, 1);
            break;
        }
        else {
            ans -= f(b - 1, -1, 0);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> st >> en;

    solve();

    cout << ans;
}