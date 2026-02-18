#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int fuck = 0;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, b;
    ll r, w;
    cin >> n >> b >> r >> w;

    vector<ll> d(b);
    vector<int> t(n);
    for (auto &i : d) cin >> i;
    for (auto &i : t) cin >> i, i--;

    vector<ll> pd(b);
    for (int i = 0; i < b; i++)
        pd[i] = d[i] + (i > 0 ? pd[i - 1] : 0);

    ll lo = 0, hi = 1e12;
    while (lo < hi) {
        const ll mid = (lo + hi) >> 1;

        bool yes = 1;

        Tree<ll> st1, st2;

        ll acc = pd[0], cnt_bus = 0;
        int mx_t = 0, rb = 0;

        for (int i = 0; i < n; i++) {
            acc += 2 * w;
            if (mx_t < t[i]) {
                acc += pd[t[i]] - pd[mx_t];
                mx_t = t[i];
            }

            acc += st1.order_of_key(t[i]) * 2 * w;
            if (st1.find(t[i]) == st1.end()) {
                acc += (sz(st2) - st2.order_of_key((t[i] + 1) * (ll)1e9)) * 2 * w;
            }

            st1.insert(t[i]);
            st2.insert(t[i] * (ll)1e9 + fuck++);

            if (mid < acc) {
                if (!rb) {
                    st1.clear(), st2.clear();

                    acc = pd[0] + ++cnt_bus * r;
                    mx_t = 0, rb = 1;
                    
                    i--;
                } else { yes = 0; break; }
            } else { rb = 0; }
        }

        if (yes) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';
}
