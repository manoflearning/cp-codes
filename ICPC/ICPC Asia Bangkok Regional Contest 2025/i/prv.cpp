#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        string s; cin >> s;

        set<int> st_i, st_c, st_p;
        for (int i = 0; i < sz(s); i++) {
            if (s[i] == 'I') st_i.insert(i + 1);
            else if (s[i] == 'C') st_c.insert(i + 1);
            else if (s[i] == 'P') st_p.insert(i + 1);
        }

        vector<array<int, 4>> ans;

        while (!st_c.empty()) {
            auto it_c1 = st_c.end(); it_c1--;

            auto it_p = st_p.lower_bound(*it_c1);
            if (it_p == st_p.begin()) break;
            it_p--;

            auto it_c2 = st_c.lower_bound(*it_p);
            if (it_c2 == st_c.begin()) break;
            it_c2--;

            auto it_i = st_i.lower_bound(*it_c2);
            if (it_i == st_i.begin()) break;
            it_i--;

            it_c2 = st_c.lower_bound(*it_i);

            ans.push_back({*it_i, *it_c2, *it_p, *it_c1});

            st_i.erase(ans.back()[0]);
            st_c.erase(ans.back()[1]);
            st_p.erase(ans.back()[2]);
            st_c.erase(ans.back()[3]);
        }

        cout << sz(ans) << '\n';
        for (auto &i : ans) {
            cout << i[0] << ' ' << i[1] << ' ' << i[2] << ' ' << i[3] << '\n';
        }
    }
}