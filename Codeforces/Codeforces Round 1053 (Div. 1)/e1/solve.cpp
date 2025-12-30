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

bool query(int x, int l, int r) {
    cout << "? " << x << ' ';
    cout << r - l + 1 << ' ';
    for (int i = l; i <= r; i++) {
        cout << i << ' ';
    }
    cout << '\n';
    cout.flush();

    bool ret; cin >> ret;
    return ret;
}

int solve(int l, int r, vector<int> vals, vector<int> waste) {
    if (l == r) return vals[0];

    int mid = (l + r) >> 1;

    vector<int> vals_l, vals_r, waste_l, waste_r;
    for (int x : vals) {
        bool res_l = query(x, l, mid);
        if (!res_l) {
            vals_r.push_back(x);
        } else {
            bool res_r = query(x, mid + 1, r);
            if (res_r) {
                waste_l.push_back(x);
                waste_r.push_back(x);
            } else {
                vals_l.push_back(x);
            }
        }
    }

    for (int x : waste) {
        bool res_l = query(x, l, mid);
        if (res_l) waste_l.push_back(x);
        else waste_r.push_back(x);
    }

    int len_l = mid - l + 1;
    if (len_l != 2 * sz(vals_l) + sz(waste_l)) {
        return solve(l, mid, vals_l, waste_l);
    } else {
        return solve(mid + 1, r, vals_r, waste_r);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        if (n == -1) break;

        vector<int> vals(n);
        iota(all(vals), 1);

        int ans = solve(1, 2 * n - 1, vals, vector<int>{});
        cout << "! " << ans << '\n';
        cout.flush();
    }
}
