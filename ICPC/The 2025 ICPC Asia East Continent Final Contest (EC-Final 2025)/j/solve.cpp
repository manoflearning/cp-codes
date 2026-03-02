#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

pair<int,pii> f(int now, int prv, int is1, const vector<vi> &t, vector<vector<pair<int,pii>>> &dp) {
    auto &ret = dp[now][is1];
    if (ret.first != -1) return ret;
    if (sz(t[now]) + (prv == -1) == 1) return ret = {1, {now, now}};

    ret.second = {now, now};


    ll sum = 1;
    int cnt = 0;

    vi zrr;
    for (const int nxt : t[now]) {
        if(nxt == prv) continue;
        sum += f(nxt, now, 0, t, dp).first;
        cnt += f(nxt, now, 0, t, dp).first == f(nxt, now, 1, t, dp).first;

        if(f(nxt, now, 0, t, dp).first == f(nxt, now, 1, t, dp).first) zrr.push_back(f(nxt, now, 1, t, dp).second.first);
    }

    ret.first = sum;

    int mi = 2 - is1;

    if (cnt >= mi) {
        cnt -= mi;
        sum -= mi;

        ret.second.first = zrr[0];
        if(is1 == 0) ret.second.second = zrr[1];
    }

    sum -= cnt / 2;

    ret.first = sum;

    if(is1 == 0) {
        ret = min(ret, f(now, prv, 1, t, dp));
    }

    return ret;
}

void prtdfs(int now, int prv, int is1, const vector<vi> &t, vector<vector<pair<int,pii>>> &dp) {
    // cout << now << is1 << ' ' << dp[now][is1].first << '\n';
    if(is1 == 0) cout << dp[now][is1].second.first + 1 << ' ' << dp[now][is1].second.second + 1 << '\n';

    vi zrr;

    for(const int nxt : t[now]) {
        if(nxt == prv) continue;

        if(dp[nxt][0].second.first == dp[now][is1].second.first) { prtdfs(nxt, now, 1, t, dp); continue;}
        if(dp[nxt][0].second.first == dp[now][is1].second.second) { prtdfs(nxt, now, 1, t, dp); continue; }

        if(dp[nxt][0].first == dp[nxt][1].first) {
            zrr.push_back(nxt);
        }
        else prtdfs(nxt, now, 0, t, dp);
    }

    if(sz(zrr) & 1) prtdfs(zrr.back(), now, 0, t, dp);

    for(int i = 0; i + 1 < sz(zrr); i += 2) {
        cout << dp[zrr[i]][1].second.first + 1 << ' ' << dp[zrr[i + 1]][1].second.first + 1 << '\n';
        prtdfs(zrr[i], now, 1, t, dp);
        prtdfs(zrr[i + 1], now, 1, t, dp);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<vi> t(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;

            t[u].push_back(v);
            t[v].push_back(u);
        }

        vector<vector<pair<int,pii>>> dp(n, vector<pair<int,pii>>(2, pair<int,pii>{-1, pii{-1, -1}}));

        cout << f(0, -1, 0, t, dp).first << '\n';
        prtdfs(0, -1, 0, t, dp);
    }
}
