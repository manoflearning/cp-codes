#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int N = 101010;

int n;
array<ll, N> a, ps;
array<bitset<2 * N>, 2> dp;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ps[i] = a[i] + ps[i - 1];
    }

    ll ans = 0;

    int lsb = 0;

    // base case
    dp[1][0] = 1;
    dp[1][a[1]] = 1;
    ans = max(ans, ps[1] - lsb);

    // inductive step
    bitset<2 * N> mask{string(2 * N, '1')};
    for (int i = 2; i <= n; i++) {
        auto &prv = dp[(i - 1) & 1];
        auto &now = dp[i & 1];

        prv &= (mask <<= 1);
        now = (prv | (prv << a[i]));

        while (lsb < 2 * N && !now[lsb]) lsb++;

        if (lsb < 2 * N) ans = max(ans, ps[i] - lsb);
        else break;
    }

    cout << ans << '\n';
}
