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
        int n;
        string s;
        cin >> n >> s;

        int ans = 0;
        for (char c : s) ans += (c == '1');

        bool x2{}, x3{};
        for (int i = 0; i < sz(s); i++) {
            if (i + 1 < sz(s) && s[i] == '1' && s[i + 1] == '1') x2 = 1;
            if (i + 2 < sz(s) && s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '1') x3 = 1;
        }

        if (x3) ans -= 2;
        else if (x2) ans -= 1;

        cout << ans << '\n';
    }
}