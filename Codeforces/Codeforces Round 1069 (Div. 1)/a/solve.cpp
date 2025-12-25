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
        string s, t;
        cin >> s >> t;

        vector<int> cnt(26);
        for (auto &c : t) cnt[c - 'a']++;

        bool is_pos = 1;
        for (auto &c : s) {
            if (!cnt[c - 'a']) {
                is_pos = 0;
                break;
            }
            cnt[c - 'a']--;
        }

        if (!is_pos) {
            cout << "Impossible\n";
            continue;
        }

        vector<int> smin(sz(s) + 1);
        smin[sz(s)] = 'z' - 'a';
        for (int i = sz(s) - 1; i >= 0; i--) {
            smin[i] = min(smin[i + 1], s[i] - 'a');
        }

        int idx = 0;
        for (int i = 0; i <= sz(s); i++) {
            while ((i < sz(s) && idx < s[i] - 'a') || idx <= smin[i]) {
                if (cnt[idx] > 0) {
                    cout << (char)(idx + 'a');
                    cnt[idx]--;
                } else {
                    idx++;
                }
            }
            if (i < sz(s)) cout << s[i];
        }
        cout << '\n';
    }
}