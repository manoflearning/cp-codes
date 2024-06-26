// lsum := sum(l_i), rsum := sum(r_i)
// cnt0 := count(x < lsum OR rsum < x)
// cntall := count(x)
// if lsum <= cnt0 -> ans = 0
// 

// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXM = 101010;

int m;
int n[MAXM];
ll l[MAXM], r[MAXM];
__int128_t lsum = 0, rsum = 0;
vector<vector<ll>> a, c;

__int128_t cnt0[MAXM], cnt1[MAXM], cnt[MAXM];
__int128_t cnt0all = 0, cnt1all = 0;
map<ll, __int128_t> mp;
map<ll, vector<pii>> mp2;

void input() {
    cin >> m;
    a.resize(m + 1);
    c.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> n[i] >> l[i] >> r[i];
        lsum += l[i], rsum += r[i];
        a[i].resize(n[i] + 1);
        c[i].resize(n[i] + 1);
        for (int j = 1; j <= n[i]; j++) cin >> a[i][j];
        for (int j = 1; j <= n[i]; j++) cin >> c[i][j];
    }
}

void init() {
    for (int i = 1; i <= m; i++) {
        n[i] = l[i] = r[i] = 0;
        cnt0[i] = cnt1[i] = cnt[i] = 0;
    }
    lsum = rsum = 0;
    a.clear(); c.clear();
    cnt0all = cnt1all = 0;
    mp.clear();
    mp2.clear();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        input();

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n[i]; j++) {
                if (a[i][j] < lsum || rsum < a[i][j]) cnt0[i] += c[i][j];
                else {
                    cnt1[i] += c[i][j];
                    mp[a[i][j]] += c[i][j];
                    mp2[a[i][j]].push_back({ i, j });
                }
                cnt[i] += c[i][j];
            }

            cnt0[i] = min<__int128_t>(cnt0[i], r[i]);
            cnt0all += cnt0[i];

            if (cnt1[i] > r[i] - cnt0[i]) {
                __int128_t tmp = cnt1[i] - (r[i] - cnt0[i]);
                cnt1[i] = r[i] - cnt0[i];
                for (int j = 1; j <= n[i]; j++) {
                    if (lsum <= a[i][j] && a[i][j] <= rsum) {
                        mp[a[i][j]] -= min<__int128_t>(c[i][j], tmp);
                    }
                }
            }

            cnt1all += cnt1[i];
        }

        if (sz(mp) == rsum - lsum + 1) {
            ll ans = rsum;
            for (ll len = lsum; len <= rsum; len++) {
                __int128_t cntwithoutlen = cnt0all + cnt1all - mp[len];
                cntwithoutlen = min<__int128_t>(cntwithoutlen, len);
                
                ll lb = 0;
                for (auto it : mp2[len]) {
                    if (cnt[it.fr] - c[it.fr][it.sc] < l[it.fr]) {
                        lb += l[it.fr] - (cnt[it.fr] - c[it.fr][it.sc]);
                    }
                }

                ans = min<ll>(ans, max<ll>(len - cntwithoutlen, lb));
            }
            cout << ans << '\n';
        }
        else cout << 0 << '\n';

        init();
    }
}