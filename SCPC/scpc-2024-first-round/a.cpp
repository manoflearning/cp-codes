// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        int n; cin >> n;
        string s; cin >> s;

        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (s[i - 1] == 'A' && s[i] == 'A') ans += 2;
            if (s[i - 1] == 'A' && s[i] == 'B') continue;
            if (s[i - 1] == 'B' && s[i] == 'A') {
                if (0 <= i - 2 && s[i - 2] == 'A') ans += 1;
            }
            if (s[i - 1] == 'B' && s[i] == 'B') continue;
        }

        cout << ans << '\n';

        cout << flush;
    }
}