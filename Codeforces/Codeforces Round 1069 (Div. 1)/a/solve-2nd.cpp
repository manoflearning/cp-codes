#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        string s, t;
        cin >> s >> t;

        vector<int> cnt(26);
        for (auto &c : t) cnt[c - 'a']++;

        bool is_valid = 1;
        for (auto &c : s) {
            cnt[c - 'a']--;
            if (cnt[c - 'a'] < 0) is_valid = 0;
        }

        if (!is_valid) {
            cout << "Impossible\n";
            continue;
        }

        string ans;

        int idx = 0;
        for (auto &c : s) {
            while (idx < c - 'a') {
                while (cnt[idx]--) {
                    ans.push_back(idx + 'a');
                }
                idx++;
            }
            ans.push_back(c);
        }
        while (idx < 26) {
            while (cnt[idx]--) {
                ans.push_back(idx + 'a');
            }
            idx++;
        }

        cout << ans << '\n';
    }
}