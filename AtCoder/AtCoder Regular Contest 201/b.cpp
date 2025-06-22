#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;
const int X = 59;

int n;
ll w;
ll dp[X + 1][2];
vector<ll> x_to_y[X + 2];

void init() {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i <= X; i++) {
        x_to_y[i].clear();
    }
}

ll f(int x, bool y) {
    auto &ret = dp[x][y];
    if (ret != -1) return ret;
    if (x == 0) {
        if ((y && (w & 1)) || !y) return ret = (!x_to_y[0].empty() ? x_to_y[0].back() : 0);
        else return ret = 0;
    }

    ret = 0;

    if (y) {
        if (w & (1ll << x)) {
            ll res1 = (!x_to_y[x].empty() ? x_to_y[x].back() : 0) + f(x - 1, 1);
            ll res2 = f(x - 1, 0);
            ret = max(res1, res2);
        } else {
            // cout << w << ' ' << x << ' ' << "fuck\n";
            ret = f(x - 1, 1);
        }
    } else {
        ll res = 0;

        vector<vector<ll>> acc(x + 2);
        for (int i = 0; i <= x; i++) {
            acc[i] = x_to_y[i];
        }

        for (int i = 0; i <= x; i++) {
            ll val1 = 0, val2 = 0;
            for (int j = 0; j < i; j++) {
                if (!acc[j].empty()) val1 += acc[j].back();
            }
            val2 = (!acc[i].empty() ? acc[i].back() : 0);

            if (val1 > val2) {
                for (int j = 0; j < i; j++) {
                    if (!acc[j].empty()) acc[j].pop_back();
                }
            } else {
                if (!acc[i].empty()) acc[i].pop_back();
            }

            res += max(val1, val2);

            while (sz(acc[i]) >= 2) {
                ll x = acc[i].back();
                acc[i].pop_back();
                ll y = acc[i].back();
                acc[i].pop_back();
                acc[i + 1].push_back(x + y);
            }

            sort(all(acc[i + 1]));
        }

        // cout << x << ' ' << res << '\n';

        ret = res;
    }
    // cout << w << ' ' << x << ' ' << ret << '\n';
    return ret;
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

        cin >> n >> w;
        for (int i = 0; i < n; i++) {
            ll x, y;
            cin >> x >> y;
            x_to_y[x].push_back(y);
        }

        for (int x = 0; x <= X; x++) {
            sort(all(x_to_y[x]));
        }

        cout << f(X, 1) << '\n';
    }
}
