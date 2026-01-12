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

pair<bool, int> get_x(ll val) {
    assert(val);

    if (val < 0) val *= -1;

    int x = 0;
    while ((1ll << x) < val) x++;
    if ((1ll << x) == val) return {1, x};
    else return {0, 0};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll sum = 0;
        for (auto &i : a) sum += i;

        if (sum % n) {
            cout << "No\n";
            continue;
        }

        const ll p = sum / n;

        bool yes = 1;

        vector<int> acc(35);
        for (int i = 0; i < n; i++) {
            if (p == a[i]) continue;

            if (get_x(p - a[i]).fr) continue;

            auto res = get_xy(p - a[i]);
            if (!res.fr) { yes = 0; break; }

            acc[res.sc.fr]++;
            acc[res.sc.sc]--;

            // cout << i << ' ' << res.sc.fr << ' ' << res.sc.sc << '\n';
        }

        vector<int> pos(35), neg(35);
        for (int i = 0; i < n; i++) {
            if (p == a[i]) continue;

            auto res = get_x(p - a[i]);
            if (!res.fr) continue;

            const int x = res.sc;
            if (p > a[i]) neg[x]++;
            else pos[x]++;
        }

        for (int i = 33; i >= 0; i--) {
            // goal: for all i, acc[i] == 0

            // (acc[x] += w)
            // or (acc[x + 1] += w, acc[x] -= w)

            if (acc[i + 1]) {
                if (acc[i + 1] < 0) {
                    if (abs(acc[i + 1]) > pos[i]) { yes = 0; break; }

                    int t = abs(acc[i + 1]);
                    acc[i + 1] += t, acc[i] -= t;
                    acc[i] += (pos[i] - t);
                    acc[i] -= neg[i];
                } else {
                    if (abs(acc[i + 1]) > neg[i]) { yes = 0; break; }

                    int t = abs(acc[i + 1]);
                    acc[i + 1] -= t, acc[i] += t;
                    acc[i] -= (neg[i] - t);
                    acc[i] += pos[i];
                }
            } else {
                acc[i] += pos[i];
                acc[i] -= neg[i];
            }
        }
        yes &= (acc[0] == 0);

        cout << (yes ? "Yes" : "No") << '\n';
    }
}
