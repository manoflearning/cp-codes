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

using omset = tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update>;
int om_uid = 0;
void m_insert(omset &os, int val) {
    os.insert({val, om_uid++});
}
void m_erase(omset &os, int val) {
    auto it = os.lower_bound({val, INT32_MIN});
    os.erase(it);
}
int m_order(const omset &os, int val) {
    return os.order_of_key({val, INT32_MIN});
}
int m_kth(const omset &os, int k) {
    return os.find_by_order(k)->fr;
}

map<int, vector<int>> mp;
pair<bool, pii> f(int mid) {
    bool res = 0;
    int ans_x = 0, ans_y = 0;

    omset st_l, st_r;
    for (auto &[_, v] : mp)
        for (auto &i : v) m_insert(st_r, i);

    for (auto &[k, v] : mp) {
        for (auto &i : v) {
            m_insert(st_l, i);
            m_erase(st_r, i);
        }

        if (sz(st_l) < 2 * mid) continue;
        if (sz(st_r) < 2 * mid) break;

        int y_ld = m_kth(st_l, mid - 1);
        int y_lu = m_kth(st_l, sz(st_l) - mid);
        if (y_ld == y_lu) continue;

        int y_rd = m_kth(st_r, mid - 1);
        int y_ru = m_kth(st_r, sz(st_r) - mid);
        if (y_rd == y_ru) continue;

        if (y_ld <= y_rd && y_rd < y_lu) {
            res = 1;
            ans_x = k + 1, ans_y = y_rd + 1;
        }
        if (y_rd <= y_ld && y_ld < y_ru) {
            res = 1;
            ans_x = k + 1, ans_y = y_ld + 1;
        }
    }

    return {res, {ans_x, ans_y}};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        mp.clear();
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            mp[x].push_back(y);
        }

        
        int l = 0, r = n / 4;
        while (l < r) {
            int mid = (l + r + 1) >> 1;

            bool res = f(mid).fr;

            if (res) l = mid;
            else r = mid - 1;
        }

        cout << l << '\n';
        auto [ans_x, ans_y] = f(l).sc;
        cout << ans_x << ' ' << ans_y << '\n';
    }
}