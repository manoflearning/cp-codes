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

    int n, k;
    cin >> n >> k;

    set<int> st;
    for (int i = 0; i < n; i++) st.insert(i);

    while (k--) {
        int h; cin >> h;

        auto it_r = st.lower_bound(h);
        auto it_l = it_r;
        if (it_l != st.begin()) it_l--;

        const int dl = abs(h - *it_l);
        const int dr = (it_r == st.end() ? 1e9 : abs(h - *it_r));

        if (dl <= dr) {
            cout << *it_l << '\n';
            st.erase(it_l);
        } else {
            cout << *it_r << '\n';
            st.erase(it_r);
        }
    }
}
