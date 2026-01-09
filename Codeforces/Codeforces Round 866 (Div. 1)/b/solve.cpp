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

bool is_valid(const ll h, const ll w, bool is_h_cut, multiset<pll> &st1, multiset<pll> &st2) {
    // cout << h << ' ' << w << endl;
    if (st1.empty()) return h * w == 0;

    ll nlen = (is_h_cut ? w : h);

    vector<pll> dels;
    if (is_h_cut) {
        auto it = st1.lower_bound({h, -1});
        if (it == st1.end() || it->fr != h) return 0;
        if (st1.lower_bound({h + 1, - 1}) != st1.end()) return 0;
        while (it != st1.end() && it->fr == h) {
            nlen -= it->sc;
            dels.push_back(*it);
            it++;
        }
    } else {
        auto it = st2.lower_bound({w, -1});
        if (it == st2.end() || it->fr != w) return 0;
        if (st2.lower_bound({w + 1, - 1}) != st2.end()) return 0;
        while (it != st2.end() && it->fr == w) {
            nlen -= it->sc;
            dels.push_back({it->sc, it->fr});
            it++;
        }
    }

    if (dels.empty()) return 0;

    for (auto &[a, b] : dels) {
        st1.erase(st1.find({a, b}));
        st2.erase(st2.find({b, a}));
    }

    return is_valid(is_h_cut ? h : nlen, is_h_cut ? nlen : w, !is_h_cut, st1, st2);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<pll> arr(n, {0, 0});

        ll mx_a = 0, mx_b = 0;
        ll area = 0;
        for (auto &i : arr) {
            cin >> i.fr >> i.sc;
            mx_a = max(mx_a, i.fr);
            mx_b = max(mx_b, i.sc);
            area += i.fr * i.sc;
        }

        vector<pll> ans;
        if (area % mx_a == 0) {
            multiset<pll> st1, st2;
            for (auto &i : arr) {
                st1.insert(i);
                st2.insert({i.sc, i.fr});
            }
            if (is_valid(mx_a, area / mx_a, 1, st1, st2))
                ans.push_back({mx_a, area / mx_a});
        }
        if (area % mx_b == 0 && mx_a != area / mx_b) {
            multiset<pll> st1, st2;
            for (auto &i : arr) {
                st1.insert(i);
                st2.insert({i.sc, i.fr});
            }
            if (is_valid(area / mx_b, mx_b, 0, st1, st2))
                ans.push_back({area / mx_b, mx_b});
        }

        cout << sz(ans) << '\n';
        for (const auto &[h, w] : ans) {
            cout << h << ' ' << w << '\n';
        }
    }
}