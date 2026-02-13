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
        string s; cin >> s;

        // set<char> st;
        // for (char c : s) st.insert(c);
        // if (sz(st) == 1) {
        //     cout << sz(s) + 1 << '\n';
        //     continue;
        // }

        ll ans = 1;

        vector<ll> cnt(26);
        for (char c : s) cnt[c - 'a']++;

        for (int i = 0; i < 26; i++) {
            ans += cnt[i] * (cnt[i] + 1) / 2;
        }

        char prv = '*';
        ll len = 0;
        for (char c : s) {
            if (prv == c) {
                len++;
            } else {
                ans -= len * (len + 1) / 2;
                ans += len;
                len = 1;
                prv = c;
            }
        }
        ans -= len * (len + 1) / 2;
        ans += len;
        len = 1;

        cout << ans << '\n';
    }
}