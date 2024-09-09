#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int n, k;
vector<ll> l, r;
vector<vector<ll>> dp;
vector<ll> smin, psum;
vector<ll> cc;

void init() {
    l.clear();
    r.clear();
    dp.clear();
    smin.clear();
    psum.clear();
    cc.clear();
}

void input() {
    cin >> n >> k;
    l.resize(n);
    r.resize(n);
    cc.push_back(0);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        cc.push_back(l[i]);
        cc.push_back(r[i]);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 0; i < n; i++) {
        l[i] = lower_bound(all(cc), l[i]) - cc.begin();
        r[i] = lower_bound(all(cc), r[i]) - cc.begin();
    }
}

void build_psum() {
    smin.resize(sz(cc) + 2, INF);
    psum.resize(sz(cc) + 2);
    for (int i = 0; i < n; i++) {
        smin[l[i]] = min(smin[l[i]], r[i]);
        psum[l[i]]++;
    }
    for (int i = sz(cc); i >= 0; i--) {
        smin[i] = min(smin[i], smin[i + 1]);
    }
    for (int i = 1; i <= sz(cc); i++) {
        psum[i] += psum[i - 1];
    }
}

void bottomup() {
    dp.resize(sz(cc) + 2, vector<ll>(k + 1, INF));
    
    // base case
    dp[0][0] = 0;

    // inductive step
    for (int i = 0; i <= sz(cc); i++) {
        if (smin[i + 1] == INF) continue;

        for (int j = i + 1; j <= smin[i + 1]; j++) {
            if (psum[j - 1] == psum[j]) continue;

            for (int p = 0; p < k; p++) {
                dp[j][p + 1] = min(dp[j][p + 1], dp[i][p] + cc[j] * (psum[j] - psum[i]));
            }
        }
    }

    // get answer
    ll ans = INF;
    for (int i = 0; i <= sz(cc); i++) {
        for (int j = 0; j <= k; j++) {
            if (psum[i] == n) ans = min(ans, dp[i][j]);
        }
    }

    cout << ans << '\n';
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

        build_psum();

        bottomup();
    }
}
