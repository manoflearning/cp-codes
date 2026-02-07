#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n;
    ll d;
    cin >> n >> d;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    ll ans = 0;

    multiset<ll> st;
    int r = 0;
    for (int l = 0; l < n; l++) { // [l, r)
        while (r < n) {
            bool yes = 1;
            auto it = st.lower_bound(a[r]);
            if (it != st.end() && *it - a[r] < d) yes = 0;
            if (it != st.begin()) {
                it--;
                if (a[r] - *it < d) yes = 0;
            }
            if (yes) st.insert(a[r++]);
            else break;
        }

        ans += r - l;
        st.erase(st.find(a[l]));
    }

    cout << ans;

    return 0;
}
