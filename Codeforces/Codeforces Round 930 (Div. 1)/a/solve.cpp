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

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

// // what: maintain a sorted set with order statistics (k-th / count < x) for distinct keys.
// // time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// // constraint: GNU pbds only.
// // usage: oset s; s.order_of_key(x); s.find_by_order(k);
// using oset = tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update>;

// constexpr ll INF = 1e18;

char query(int a, int b, int c, int d) {
    cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    cout.flush();
    char ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    random_device rd;
    mt19937_64 eng(rd());

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        // vector<int> p(n);
        // iota(all(p), 0);

        int t = 1;
        while ((1 << t) < n) t++;

        int mx = 0;
        for (int i = 1; i < n; i++) {
            char res = query(mx, mx, i, i);
            if (res == '<') mx = i;
        }

        vector<int> mx2;
        mx2.push_back(mx == 0 ? 1 : 0);
        for (int i = 1; i < n; i++) {
            if (i == mx) continue;
            char res = query(mx, mx2.back(), mx, i);
            if (res == '=') mx2.push_back(i);
            else if (res == '<') {
                mx2.clear();
                mx2.push_back(i);
            }
        }

        int mn = mx2[0];
        for (int i = 1; i < sz(mx2); i++) {
            char res = query(mn, mn, mx2[i], mx2[i]);
            if (res == '>') mn = mx2[i];
        }

        cout << "! " << mx << ' ' << mn << '\n';
        cout.flush();

        // oset st;
        // st.insert({-INF, -INF});
        // st.insert({INF, INF});
        // st.insert({0, p[0]});
        // for (int i = 1; i < n; i++) {
        //     int l = 1, r = sz(st) - 1;
        //     while (l < r) {
        //         int mid = (l + r) >> 1;
                
        //         auto it = st.find_by_order(mid);

        //         int a = it->sc;
        //         char res = query(a, a, p[i], p[i]);
        //         assert(res != '=');
        //         if (res == '<') l = mid + 1;
        //         else r = mid;
        //     }

        //     auto it = st.find_by_order(l);
        //     assert(it != st.begin());
        //     ll x = it->fr, y = (--it)->fr;
        //     st.insert({(x + y) / 2, p[i]});
        // }

        // auto it_i = st.find_by_order((1 << (t - 1)));
        // auto it_j = st.find_by_order((1 << (t - 1)) + 1);

        // cout << "! " << it_i->sc << ' ' << it_j->sc << '\n';
        // cout.flush();
    }
}