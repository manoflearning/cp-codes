#pragma GCC optimize("O3")
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
        int n;
        string s;
        cin >> n >> s;

        int cnt0 = 0;
        for (char c : s) cnt0 += (c == '0');

        if (cnt0 * 2 != n) {
            cout << -1 << '\n';
            continue;
        }

        s = "*" + s;

        vector<int> ans;

        int l = 1, r = n;
        while (l < r) {
            if (s[l] == s[r]) {
                if (s[l] == '1') {
                    ans.push_back(l - 1);
                    s = "*" + s.substr(1, l - 1) + "01" + s.substr(l, sz(s) - l);
                    r = r + 2;
                } else {
                    ans.push_back(r);
                    s = "*" + s.substr(1, r) + "01" + s.substr(r + 1, sz(s) - r - 1);
                    r = r + 2;
                }
            } else {
                l++, r--;
            }
        }

        cout << sz(ans) << '\n';
        for (auto &i : ans)
            cout << i << ' ';
        cout << '\n';
        // cout << s << '\n';
    }
}