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
        ll n; cin >> n;

        string s = to_string(n);
        
        vector<int> ans;

        const int mod = sz(s);
        for (int x = 1; x < mod; x++) {
            string t = s.substr(sz(s) - x, x) + s.substr(0, sz(s) - x);

            const ll m = stoll(t);
            if (m > n && (m - n) % mod == x % mod) {
                ans.push_back(m - n);
            }
        }

        sort(all(ans));
        cout << sz(ans) << '\n';
        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    }
}