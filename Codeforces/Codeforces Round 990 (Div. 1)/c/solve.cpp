#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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
using ordered_set = tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>;

void m_erase(ordered_set &OS, int val){
    int index = OS.order_of_key(val);
    ordered_set::iterator it = OS.find_by_order(index);
    OS.erase(it);
}

constexpr int INF = 1e9 + 7;

int n;
vector<pii> a;
vector<int> cc_x;

int mx_x = -INF;

void init() {
    a.clear();
    cc_x.clear();
}

void input() {
    cin >> n;

    a.resize(n);
    for (auto &i : a) {
        cin >> i.fr >> i.sc;
    }
}

void coor_comp() {
    for (auto &i : a) {
        cc_x.push_back(i.fr);
        // cc_y.push_back(i.sc);
    }
    sort(all(cc_x));
    // sort(all(cc_y));
    cc_x.erase(unique(all(cc_x)), cc_x.end());
    // cc_y.erase(unique(all(cc_y)), cc_y.end());
    for (auto &i : a) {
        i.fr = lower_bound(all(cc_x), i.fr) - cc_x.begin();
        // i.sc = lower_bound(all(cc_y), i.sc) - cc_y.begin();

        mx_x = max(mx_x, i.fr);
    }
}

pair<bool, pii> f(int mid) {
    int cnt_l = 0, cnt_r = n;

    ordered_set st_l, st_r;
    for (auto &i : a) st_r.insert(i.sc);

    int idx = 0;
    for (int x = 0; x <= mx_x; x++) {
        while (idx < sz(a) && a[idx].fr < x) {
            st_l.insert(a[idx].sc);
            m_erase(st_r, a[idx].sc);
            idx++;
        }

        if (2 * mid > sz(st_r)) break;

        if (2 * mid <= sz(st_l)) {
            int y_dl = *st_l.find_by_order(mid - 1) + 1;
            int y_ul = *st_l.find_by_order(sz(st_l) - mid);
            if (y_dl > y_ul) continue;
            int y_dr = *st_r.find_by_order(mid - 1) + 1;
            int y_ur = *st_r.find_by_order(sz(st_r) - mid);
            if (y_dr > y_ur) continue;

            bool is_valid = 0;
            if (y_dr <= y_ul && y_ul <= y_ur) {
                return {1, {x, y_ul}};
            }
            if (y_dr <= y_dl && y_dl <= y_ur) {
                return {1, {x, y_dl}};
            }
            if (y_dl <= y_ur && y_ur <= y_ul) {
                return {1, {x, y_ur}};
            }
            if (y_dl <= y_dr && y_dr <= y_ul) {
                return {1, {x, y_dr}};
            }
        }
    }
    return {0, {0, 0}};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        coor_comp();

        sort(all(a));

        int l = 0, r = n / 4;
        while (l < r) {
            int mid = (l + r + 1) >> 1;

            auto [res, _] = f(mid);
            if (res) l = mid;
            else r = mid - 1;
        }

        auto [_, opt] = f(l);

        cout << l << '\n';
        cout << cc_x[opt.fr] << ' ' << opt.sc << '\n';
    }
}
