#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<pii> a(n);
        for (auto &i : a) {
            cin >> i.first >> i.second;
        }
        sort(all(a));

        vector<int> suf(n + 1, -1);
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = max(a[i].second, suf[i + 1]);
        }
        
        int ans = INF;

        set<int> st;
        for (int i = 0; i < n; i++) {
            const int m1 = a[i].first;

            const int m2 = suf[i + 1];
            if (m2 != -1) ans = min(ans, abs(m2 - m1));
            if (m2 <= m1) {
                auto it = st.lower_bound(m1);
                if (it != st.end()) {
                    ans = min(ans, abs(*it - m1));
                }
                if (it != st.begin()) {
                    it--;
                    ans = min(ans, abs(max(*it, m2) - m1));
                }
            }

            st.insert(a[i].second);
        }

        cout << ans << '\n';
    }
}
