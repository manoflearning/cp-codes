#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    string s;
    int k;
    cin >> s >> k;

    if (k == sz(s)) {
        cout << 0;
    }
    else if (2 * k <= sz(s)) {
        int ans = 0;
        for (int i = 0, j = sz(s) - k; i < k && j < sz(s); i++, j++) {
            if (s[i] != s[j]) ans++;
        }
        cout << ans;
    }
    else {
        int ans = 0;

        int d = sz(s) - k;
        for (int i = 0; i < d; i++) {
            vector<int> cnt(26);
            int sum = 0;
            for (int j = i; j < sz(s); j += d) {
                cnt[s[j] - 'a']++;
                sum++;
            }

            int res = 1e9;
            for (auto& i : cnt) {
                res = min(res, sum - i);
            }
            ans += res;
        }

        cout << ans;
    }
}