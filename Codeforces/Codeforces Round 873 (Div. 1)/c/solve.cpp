#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

// what: compute longest palindrome radius at every center (odd/even).
// time: O(n); memory: O(n)
// constraint: 0-indexed; d1[i]=odd radius, d2[i]=even radius.
// usage: auto [d1,d2]=manacher(s); // max len = max(2*d1[i]-1,2*d2[i])
pair<vi, vi> manacher(const string &s) {
    // result: d1/d2 radii for odd/even palindromes centered at i.
    int n = sz(s);
    vi d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) l = i - k - 1, r = i + k;
    }
    return {d1, d2};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        string s;
        cin >> n >> s;

        s = "*" + s;
        vi d2 = manacher(s).sc;

        vi next(n + 1, -1);
        set<int> st;
        for (int i = n; i >= 1; i--) {
            while (!st.empty()) {
                int j = *st.begin();
                if (i < j - d2[j]) st.erase(j);
                else break;
            }
            if (!st.empty()) {
                int j = *st.begin();
                next[i] = 2 * j - i;
            }

            if (d2[i]) st.insert(i);
        }

        ll ans = 0;
        vector<ll> dp(n + 2);
        for (int i = n; i >= 1; i--) {
            if (next[i] != -1)
                dp[i] = 1 + dp[next[i]];
            // cout << i << ' ' << dp[i] << '\n';
            ans += dp[i];
        }

        cout << ans << '\n';
    }
}