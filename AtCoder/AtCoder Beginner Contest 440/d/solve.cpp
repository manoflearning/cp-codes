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

// what: maintain a sorted set with order statistics (k-th / count < x) for distinct keys.
// time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// constraint: GNU pbds only.
// usage: oset s; s.order_of_key(x); s.find_by_order(k);
using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    // oset st{};

    vector<ll> a(n);
    for (auto &i : a) {
        cin >> i;
        // st.insert(i);
    }
    sort(all(a));

    while (q--) {
        ll x, y;
        cin >> x >> y;

        ll l = x + y - 1, r = x + n + y;
        while (l < r) {
            ll mid = (l + r) >> 1;

            ll cnt = mid - x + 1;

            ll cnt2 = 0;

            const int ub = upper_bound(all(a), mid) - a.begin();
            const int lb = lower_bound(all(a), x) - a.begin();
            cnt2 = ub - lb;
            // auto it1 = st.upper_bound(mid);
            // if (it1 != st.begin()) {
            //     it1--;
            //     cnt2 += st.order_of_key(*it1) + 1;
            //     cnt2 -= st.order_of_key(x);
            // }

            if (cnt - cnt2 < y) l = mid + 1;
            else r = mid;
        }
        cout << l << '\n';
    }
}