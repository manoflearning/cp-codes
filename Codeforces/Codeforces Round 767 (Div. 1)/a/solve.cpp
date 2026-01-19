#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        unordered_map<int, queue<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[a[i]].push(i);
        }

        vector<int> ans;

        int st = 0;
        while (st < n) {
            int mex = 0;
            unordered_set<int> vis;
            while (st < n) {
                while (!mp[mex].empty() && mp[mex].front() < st) mp[mex].pop();

                if (!mp[mex].empty()) {
                    for (int i = st; i <= mp[mex].front(); i++) {
                        vis.insert(a[i]);
                    }
                    st = mp[mex].front() + 1;

                    while (vis.count(mex)) mex++;
                } else break;
            }

            if (!vis.empty()) ans.push_back(mex);
            else {
                if (st < n) {
                    assert(mex == 0);
                    while (st++ < n) ans.push_back(0);
                }
            }
        }

        cout << sz(ans) << '\n';
        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    }
}
