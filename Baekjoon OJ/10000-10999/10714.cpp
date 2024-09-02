#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n;
vector<ll> a;
ll dp[4040][4040];

pair<int, int> next_lr(int l, int r) {
    if (0 <= l - 1 && r + 1 < sz(a)) {
        if (a[l - 1] > a[r + 1]) return { l - 1, r };
        else return { l, r + 1 };
    }
    else if (0 <= l - 1) return { l - 1, r };
    else if (r + 1 < sz(a)) return { l, r + 1 };
    else assert(0);
}

ll f(int l, int r) {
    auto& ret = dp[l][r];
    if (ret != -1) return ret;
    if ((r - l + 1) >= n) return ret = 0;

    ret = 0;
    if (0 <= l - 1) {
        auto [nl, nr] = next_lr(l - 1, r);
        ret = max(ret, a[l - 1] + f(nl, nr));
    }
    if (r + 1 < sz(a)) {
        auto [nl, nr] = next_lr(l, r + 1);
        ret = max(ret, a[r + 1] + f(nl, nr));
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
    for (auto& i : a) cin >> i;

    for (int i = 0; i < 2 * n; i++)
        a.push_back(a[i]);

    memset(dp, -1, sizeof(dp));

    ll ans = 0;
    for (int i = n; i < 2 * n; i++) {
        auto [nl, nr] = next_lr(i, i);
        ans = max(ans, a[i] + f(nl, nr));
    }

    cout << ans;
}