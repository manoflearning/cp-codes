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

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        int n;
        string s;
        cin >> n >> s;

        int dir = 1;
        int now = 0, mn = 0, mx = 0;

        for (int i = 0; i < n; i++) {
            now += dir;

            mn = min(mn, now);
            mx = max(mx, now);
            if (i + 1 < n && s[i] == s[i + 1]) {
                dir *= -1;
            }
        }

        cout << mx - mn << '\n';
    }
}
