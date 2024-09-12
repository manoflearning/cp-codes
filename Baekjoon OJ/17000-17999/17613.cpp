// f(2^t-1, 2^{t+1}-2])
// = t + f(0, 2^t-1)
// = t + max(f(0, 2^{t-1}-1), f(2^{t-1}, 2^t-1]))

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

int n;
vector<pii> a;
map<pii, int> dp;

int f(int l, int r, int t) {
    if (dp.count({ l, r })) return dp[{ l, r }];
    if (l == r && l == (1 << t) - 1) return dp[{ l, r }] = t;

    int& ret = dp[{ l, r }];
    for (int nt = 1; (1 << nt) - 1 <= r; nt++) {
        int nl = max((1 << nt) - 1, l - (1 << t) + 1);
        int nr = min((1 << (nt + 1)) - 2, r - (1 << t) + 1);
        if (nl > nr) continue;
        ret = max(ret, t + f(nl, nr, nt));
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

    cin >> n;
    a.resize(n);
    for (auto& i : a)
        cin >> i.fr >> i.sc;

    for (auto& i : a) {
        int ans = 0;
        for (int t = 1; (1 << t) - 1 <= i.sc; t++) {
            int l = max((1 << t) - 1, i.fr);
            int r = min((1 << (t + 1)) - 2, i.sc);
            if (l > r) continue;
            ans = max(ans, f(l, r, t));
        }
        cout << ans << '\n';
    }
}
