#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        string s; cin >> s;

        int cnt0 = 0, cnt1 = 0;
        for (auto &i : s) {
            if (i == '0') cnt0++;
            if (i == '1') cnt1++;
        }

        if (cnt0 == 0) {
            cout << 0 << '\n';
        } else if (cnt1 == 0) {
            cout << 1 << '\n';
        } else {
            s.push_back('1');
            int cnt_distinctive_0s = 0;
            for (int i = 0; i + 1 < sz(s); i++) {
                if (s[i] != s[i + 1] && s[i] == '0') {
                    cnt_distinctive_0s++;
                }
            }
            if (cnt_distinctive_0s == 1) cout << 1 << '\n';
            else cout << 2 << '\n';
        }
    }
}