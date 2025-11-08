#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const string s = "QWERTYUIOPASDFGHJKLZXCVBNM";

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    vector<bool> vis(26);
    int vis_cnt = 0;

    string t;
    for (int i = 0; i < 3; i++) {
        string in; cin >> in;
        t += in;
    }

    for (int i = 0; i < sz(s); i++) {
        if (t[i] == '*' && !vis[s[i] - 'A']) {
            vis[s[i] - 'A'] = 1;
            vis_cnt++;
        }
    }

    int q; cin >> q;
    while (q--) {
        string in; cin >> in;

        set<char> st;
        bool is_pos = 1;
        for (auto &c : in) {
            if (!vis[c - 'A']) { is_pos = 0; break; }
            st.insert(c);
        }

        cout << (is_pos && sz(st) == vis_cnt ? "POSSIBLE" : "IMPOSSIBLE") << '\n';
    }
}