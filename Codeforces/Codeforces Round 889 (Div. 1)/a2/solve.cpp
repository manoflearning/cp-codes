#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int INF = 1e9 + 7;

bool yes(vector<ll> a, const vector<pii> &ans) {
    if (sz(ans) > 31) return 0;
    for (auto [i, j] : ans) {
        a[i] += a[j];
    }
    for (int i = 1; i + 1 < sz(a); i++) {
        if (a[i] > a[i + 1]) return 0;
    }
    return 1;
}

bool neg_to_pos(int n, vector<ll> a, int pos) {
    if (pos == -1) return 0;

    int ret = 0;

    ll mn_neg = INF, cnt_n = 0;
    for (int i = 1; i <= n; i++) {
        mn_neg = min(mn_neg, a[i]);
        if (a[i] < 0) cnt_n++;
    }

    while (a[pos] < -mn_neg) {
        a[pos] *= 2;
        ret++;
    }

    return (ret + cnt_n <= 12 ? 1 : 0);
}

bool pos_to_neg(int n, vector<ll> a, int neg) {
    if (neg == -1) return 0;

    int ret = 0;

    ll mx_pos = -INF, cnt_p = 0;
    for (int i = 1; i <= n; i++) {
        mx_pos = max(mx_pos, a[i]);
        if (a[i] > 0) cnt_p++;
    }

    while (mx_pos + a[neg] > 0) {
        a[neg] *= 2;
        ret++;
    }

    return (ret + cnt_p <= 12 ? 1 : 0);
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        int pos = -1, neg = -1;
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];

            if (a[i] > 0) {
                if (pos == -1 || a[pos] < a[i]) pos = i;
            }
            if (a[i] < 0) {
                if (neg == -1 || a[neg] > a[i]) neg = i;
            }
        }

        vector<pii> ans;

        auto b = a;
        if (neg_to_pos(n, b, pos)) {
            ll mn_neg = INF;
            for (int i = 1; i <= n; i++) {
                mn_neg = min(mn_neg, b[i]);
            }

            while (b[pos] < -mn_neg) {
                b[pos] *= 2;
                ans.push_back({pos, pos});
            }

            for (int i = 1; i <= n; i++) {
                if (b[i] < 0) {
                    b[i] += b[pos];
                    ans.push_back({i, pos});
                }
            }

            for (int i = 1; i + 1 <= n; i++) {
                if (b[i] > b[i + 1]) {
                    b[i + 1] += b[i];
                    ans.push_back({i + 1, i});
                }
            }
        } else if (pos_to_neg(n, b, neg)) {
            ll mx_pos = -INF, cnt_p = 0;
            for (int i = 1; i <= n; i++) {
                mx_pos = max(mx_pos, b[i]);
                if (b[i] > 0) cnt_p++;
            }

            while (mx_pos + b[neg] > 0) {
                b[neg] *= 2;
                ans.push_back({neg, neg});
            }

            for (int i = 1; i <= n; i++) {
                if (b[i] > 0) {
                    b[i] += b[neg];
                    ans.push_back({i, neg});
                }
            }

            for (int i = n; i - 1 >= 1; i--) {
                if (b[i - 1] > b[i]) {
                    b[i - 1] += b[i];
                    ans.push_back({i - 1, i});
                }
            }
        } else if (pos == -1 && neg == -1) {
            // do nothing    
        } else {
            assert(0);
        }

        cout << sz(ans) << '\n';
        for (const auto &[i, j] : ans) {
            cout << i << ' ' << j << '\n';
        }

        // cout.flush();
        assert(yes(a, ans));
    }
}
