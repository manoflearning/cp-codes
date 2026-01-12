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

        vector<int> a(m);
        for (auto &i : a) cin >> i;

        set<int> st;
        for (auto &i : a) st.insert(i);

        int now = 1;
        for (const char c : s) {
            if (c == 'A') {
                now += 1;
                st.insert(now);
            } else {
                now++;
                while (st.count(now)) now++;
                st.insert(now);
                while (st.count(now)) now++;
            }
        }

        cout << sz(st) << '\n';
        for (auto &i : st) cout << i << ' ';
        cout << '\n';
    }
}