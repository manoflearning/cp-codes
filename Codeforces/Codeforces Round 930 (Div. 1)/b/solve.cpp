#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// what: maintain a sorted set with order statistics (k-th / count < x) for distinct keys.
// time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// constraint: GNU pbds only.
// usage: oset s; s.order_of_key(x); s.find_by_order(k);
using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

int n;
string s;
vector<ll> pc0, pc1;
vector<ll> pl0, pl1;
vector<ll> ans;

void init() {
    // TODO
}

void input() { cin >> n >> s; }

ll sum(int l, int r, const vector<ll> &psum) {
    if (l > r) return 0;
    return psum[r] - (l == 0 ? 0 : psum[l - 1]);
}

void solve(bool is_rev) {
    // build psum
    pc0.assign(n, 0), pc1.assign(n, 0);
    pl0.assign(n, 0), pl1.assign(n, 0);

    oset st0, st1;
    for (int i = 0; i < n; i++) {
        pc0[i] = (s[i] == '>') + (i > 0 ? pc0[i - 1] : 0);
        pc1[i] = (s[i] == '<') + (i > 0 ? pc1[i - 1] : 0);
        pl0[i] = (s[i] == '>' ? i : 0) + (i > 0 ? pl0[i - 1] : 0);
        pl1[i] = (s[i] == '<' ? i : 0) + (i > 0 ? pl1[i - 1] : 0);

        if (s[i] == '>') st0.insert(i);
        else st1.insert(i);
    }

    // solve
    for (int i = 0; i < n; i++) {
        if (s[i] != '>') continue;

        ll cnt0 = sum(0, i - 1, pc0);
        ll cnt1 = sum(i + 1, n - 1, pc1);

        if (cnt0 < cnt1) {
            int ord1 = sum(0, i, pc1) + cnt0 + 1;
            auto it = st1.find_by_order(ord1 - 1);
            assert(it != st1.end());
            int mx1 = *it;

            ll res = 1;
            res += 2 * sum(i + 1, mx1, pl1);
            res -= 2 * sum(0, i - 1, pl0);
            res -= sum(i, i, pl0);

            ans[is_rev ? n - i - 1 : i] = res;
        } else {
            auto it = st0.find_by_order(cnt0 - cnt1);
            assert(it != st0.end());
            int mn0 = *it;

            ll res = 1;
            res += n - 1;
            res += 2 * sum(i + 1, n - 1, pl1);
            res -= 2 * sum(mn0, i - 1, pl0);
            res -= sum(i, i, pl0);

            ans[is_rev ? n - i - 1 : i] = res;
        }        
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        ans.assign(n, 0);

        solve(0);
        for (auto &c : s)
            c = (c == '>' ? '<' : '>');
        reverse(all(s));
        solve(1);

        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}
