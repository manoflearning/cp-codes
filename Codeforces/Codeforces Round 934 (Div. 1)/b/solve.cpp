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

// what: compute longest palindrome radius at every center (odd/even).
// time: O(n); memory: O(n)
// constraint: 0-indexed; d1[i]=odd radius, d2[i]=even radius.
// usage: auto [d1,d2]=manacher(s); // max len = max(2*d1[i]-1,2*d2[i])
pair<vector<int>, vector<int>> manacher(const string &s) {
    // result: d1/d2 radii for odd/even palindromes centered at i.
    int n = sz(s);
    vector<int> d1(n), d2(n);
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
        int n, q;
        cin >> n >> q;

        string s; cin >> s;
        s = "*" + s;

        vector<vector<int>> ps(26, vector<int>(n + 1));
        vector<vector<int>> ps_o(26, vector<int>(n + 1));
        vector<vector<int>> ps_e(26, vector<int>(n + 1));

        for (int i = 0; i < 26; i++) {
            for (int j = 1; j <= n; j++) {
                ps[i][j] += (s[j] - 'a' == i) + ps[i][j - 1];
                ps_o[i][j] += (s[j] - 'a' == i && (j & 1)) + ps_o[i][j - 1];
                ps_e[i][j] += (s[j] - 'a' == i && !(j & 1)) + ps_e[i][j - 1];
            }
        }

        auto [d1, d2] = manacher(s);

        auto sum_e = [&](int l, int r) -> ll {
            int lcnt = 0;
            for (int i = 0; i < 26; i++) {
                lcnt += (ps[i][r] - ps[i][l - 1]) > 0;
            }
            assert(lcnt > 0);

            const ll n = (r - l) / 2;
            return (lcnt == 1 ? n * n + n : 0);
        };
        auto sum_o = [&](int l, int r) -> ll {
            int lcnt_o = 0, lcnt_e = 0;
            for (int i = 0; i < 26; i++) {
                lcnt_o += (ps_o[i][r] - ps_o[i][l - 1]) > 0;
                lcnt_e += (ps_e[i][r] - ps_e[i][l - 1]) > 0;
            }

            assert(lcnt_o > 0 && lcnt_e > 0);
            const ll n = (r - l + 1) / 2;
            return (lcnt_o == 1 && lcnt_e == 1 ? n * n - 1 : 0);
        };

        while (q--) {
            int l, r;
            cin >> l >> r;

            const ll len = r - l + 1;

            ll ans = len * (len + 1) / 2 - 1;

            ans -= sum_e(l, r);
            ans -= sum_o(l, r);

            if (len & 1) {
                ans -= len * (2 * d1[l + len / 2] - 1 >= len);
            } else {
                ans -= len * (2 * d2[l + len / 2] >= len);
            }

            cout << ans << '\n';
        }
    }
}
