#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
#define fr first
#define sc second
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        
        vector<vector<int>> t(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            t[u].push_back(v);
            t[v].push_back(u);
        }

        string s; cin >> s;

        int cntq_nl = 0;
        int cnt0 = 0, cnt1 = 0, cntq = 0;
        for (int v = 2; v <= n; v++) {
            if (sz(t[v]) >= 2) {
                cntq_nl += s[v - 1] == '?';
            } else {
                cnt0 += s[v - 1] == '0';
                cnt1 += s[v - 1] == '1';
                cntq += s[v - 1] == '?';
            }
        }

        int ans = 0;
        if (s[0] == '?') {
            if (cnt0 > cnt1 || cnt0 < cnt1) {
                if (cnt0 > cnt1) s[0] = '1';
                else s[0] = '0';

                ans += cnt0 * (s[0] != '0');
                ans += cnt1 * (s[0] != '1');
                ans += cntq / 2;
            } else {
                ans += cnt0;
                ans += (cntq + (cntq_nl & 1)) / 2;
            }
        } else {
            ans += cnt0 * (s[0] != '0');
            ans += cnt1 * (s[0] != '1');
            ans += (cntq + 1) / 2;
        }

        cout << ans << '\n';
    }
}
