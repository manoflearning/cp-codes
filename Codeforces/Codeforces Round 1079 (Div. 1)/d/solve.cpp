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

        vector<int> rc, ro, sc, so;

        vector<int> stk_r{}, stk_s{};
        for (int i = 0; i < n; i++) {
            if (s[i] == '(' || s[i] == '[') {
                if (s[i] == '(') ro.push_back(i);
                else so.push_back(i);
            } else {
                if (s[i] == ')') {
                    if (!ro.empty()) ro.pop_back();
                    else rc.push_back(i);
                } else {
                    if (!so.empty()) so.pop_back();
                    else sc.push_back(i);
                }
            }
        }

        vector<int> c(sz(rc) + sz(sc));
        vector<int> o(sz(ro) + sz(so));

        merge(all(rc), all(sc), c.begin());
        merge(all(ro), all(so), o.begin());

        assert(~(sz(c) + sz(o)) & 1);

        int ans = 0;
        if (!c.empty() && !o.empty() && c.back() > o.front()) {
            ans += (sz(c) + sz(o)) / 2;
        } else {
            ans += (sz(c) + 1) / 2;
            ans += (sz(o) + 1) / 2;
        }

        cout << ans << '\n';
    }

    return 0;
}
