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

bool query(int l, int r, int x) {
    cout << "? " << x << ' ' << r - l + 1 << ' ';
    for (int i = l; i <= r; i++) cout << i << ' ';
    cout << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}
void solve(int l, int r, set<int> st1, set<int> st2) {
    if (l == r) {
        cout << "! " << *st2.begin() << '\n';
        cout.flush();
        return;
    }

    set<int> st1_l, st1_r;

    int mid = (l + r) >> 1;
    for (auto &i : st1) {
        if (query(l, mid, i)) st1_l.insert(i);
        else st1_r.insert(i);
    }

    set<int> st2_l, st2_r;
    for (auto &i : st2) {
        bool res_l = query(l, mid, i);
        bool res_r = query(mid + 1, r, i);

        if (res_l && res_r) {
            st1_l.insert(i);
            st1_r.insert(i);
        } else if (res_l) {
            st2_l.insert(i);
        } else if (res_r) {
            st2_r.insert(i);
        }
    }

    if (sz(st1_l) + 2 * sz(st2_l) != mid - l + 1) {
        solve(l, mid, st1_l, st2_l);
    } else {
        solve(mid + 1, r, st1_r, st2_r);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        set<int> st;
        for (int i = 1; i <= n; i++) st.insert(i);

        solve(1, 2 * n - 1, set<int>{}, st);
    }
}
