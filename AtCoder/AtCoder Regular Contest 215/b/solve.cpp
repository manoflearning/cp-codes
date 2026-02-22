#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

vector<int> solve(int n, const vector<int> &a) {
    vector<int> ans;

    int turn = 0;
    vector<unordered_set<int>> vis(2);
    for (int i = 0; i < 2 * n; i++) {
        if (vis[turn].count(a[i])) {
            turn = !turn;
            ans.push_back(i - 1);
        }

        vis[turn].insert(a[i]);
    }

    assert(sz(ans) <= n);

    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(2 * n);
        for (auto &i : a) cin >> i;

        vector<int> ans = solve(n, a);

        cout << sz(ans) << '\n';
        for (auto &i : ans) cout << i + 1 << ' ';
        cout << '\n';
    }

    return 0;
}
