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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        string s; cin >> s;

        set<int> st;
        for (int i = 0; i < m; i++) {
            int idx; cin >> idx;
            st.insert(idx);
        }

        int now = 1;
        for (const auto &c : s) {
            if (c == 'A') {
                now++;
                st.insert(now);
            }
            if (c == 'B') {
                do {
                    now++;
                } while (st.count(now));
                st.insert(now);
                while (st.count(now)) now++;
            }
        }

        cout << sz(st) << '\n';
        for (auto &i : st) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
