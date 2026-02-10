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

    string s; cin >> s;

    int cnt_blocks{};
    for (int i = 0; i < sz(s); i++) {
        if ((i == 0 || (i > 0 && s[i - 1] == ':')) && s[i] != ':') {
            cnt_blocks++;
        }
    }

    vector<string> ans;
    for (int i = 0; i < sz(s); i++) {
        if ((i == 0 || (i > 0 && s[i - 1] == ':')) && s[i] != ':') {
            ans.push_back(string{});
        }
        if (i + 1 < sz(s) && s[i] == ':' && s[i + 1] == ':') {
            int cnt = 8 - cnt_blocks;
            while (cnt--) ans.push_back(string{"0000"});
        }
        if (s[i] != ':') {
            ans.back().push_back(s[i]);
        }
    }

    assert(sz(ans) == 8);
    for (int i = 0; i < sz(ans); i++) {
        ans[i] = string(4 - sz(ans[i]), '0') + ans[i];
        for (auto &c : ans[i]) {
            if ('A' <= c && c <= 'Z') c = c - 'A' + 'a';
        }
        cout << ans[i];
        if (i + 1 < sz(ans)) cout << ":";
    }
}
