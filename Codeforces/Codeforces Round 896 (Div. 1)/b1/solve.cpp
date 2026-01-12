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

pair<bool, pii> get_xy(ll val) {
    assert(val);

    bool is_swapped = 0;
    if (val < 0) {
        is_swapped = 1;
        val *= -1;
    }

    int x = -1, y = -1;
    for (int i = 0; (1ll << i) <= val; i++) {
        if ((1ll << i) & val) {
            if (x != -1 && y + 1 != i) return {0, {-1, -1}};

            if (x == -1) x = i;
            y = i;
        }
    }
    y++;

    if (is_swapped) swap(x, y);
    return {1, {x, y}};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll acc = 0;
        for (auto &i : a) acc += i;

        if (acc % n) {
            cout << "No\n";
            continue;
        }

        const ll p = acc / n;

        bool yes = 1;

        int cnt_s = 0;
        map<int, int> prod, rec;
        for (int i = 0; i < n; i++) {
            if (p == a[i]) {
                cnt_s++;
                continue;
            }

            auto res = get_xy(p - a[i]);
            if (!res.fr) { yes = 0; break; }

            prod[res.sc.sc]++;
            rec[res.sc.fr]++;
        }

        for (int i = 0; i < 35; i++) {
            if (prod[i] != rec[i]) yes = 0;
        }

        cout << (yes ? "Yes" : "No") << '\n';
    }
}
