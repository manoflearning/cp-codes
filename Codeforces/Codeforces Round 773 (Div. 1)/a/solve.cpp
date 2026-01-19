#pragma GCC optimize ("O3")
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

    int tc; cin >> tc;
    while (tc--) {
        int n; ll x;
        cin >> n >> x;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        sort(all(a));

        multiset<ll> st;
        for (auto &i : a) {
            if (i % x == 0) {
                auto it = st.find(i / x);
                if (it != st.end()) st.erase(it);
                else st.insert(i);
            } else st.insert(i);
        }

        cout << sz(st) << '\n';
    }
}
