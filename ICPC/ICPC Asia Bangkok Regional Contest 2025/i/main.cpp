#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

string x; 
vector<array<int, 4>> res;

bool f(int mid) {
    res.clear();

    set<int> st_c;
    for (int i = 0; i < sz(x); i++) {
        if (x[i] == 'C') st_c.insert(i);
    }

    set<pair<int, int>> pair_l;
    for (int i = 0; i < sz(x); i++) {
        if (sz(pair_l) == mid) break;

        if (x[i] == 'I') {
            auto it = st_c.lower_bound(i);
            if (it == st_c.end()) return 0;
            pair_l.insert({i, *it});
            st_c.erase(it);
        }
    }
    // cout << mid << ' ' << sz(pair_l) << '\n';
    if (sz(pair_l) < mid) return 0;

    set<pair<int, int>> pair_r;
    for (int i = sz(x) - 1; i >= 0; i--) {
        if (sz(pair_r) == mid) break;

        if (x[i] == 'P') {
            auto it = st_c.lower_bound(i);
            if (it == st_c.end()) continue;
            pair_r.insert({i, *it});
            st_c.erase(it);
        }
    }

    for (auto &i : pair_l) {
        auto it = pair_r.lower_bound({i.sc, 0});
        if (it == pair_r.end()) return 0;
        res.push_back({i.fr, i.sc, it->fr, it->sc});
        pair_r.erase(it);
    }

    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> x;

        int l = 0, r = sz(x) / 4;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (f(mid)) l = mid;
            else r = mid - 1;
        }

        f(l);

        assert(sz(res) == l);

        cout << sz(res) << '\n';
        for (auto &i : res) {
            cout << i[0] + 1 << ' ' << i[1] + 1 << ' ' << i[2] + 1 << ' ' << i[3] + 1 << '\n';
        }
    }
}