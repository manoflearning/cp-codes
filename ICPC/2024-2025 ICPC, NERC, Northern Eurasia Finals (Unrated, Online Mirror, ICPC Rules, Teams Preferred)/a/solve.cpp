#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void solve(const int n, vector<int> &a, const vector<int> &c, vector<pii> &ans) {
    for (int i = 0; i < n; i++) {
        int j{};
        for (j = i; j < n; j++) {
            if (c[i] == a[j]) break;
        }

        for (int k = j; k - 1 >= i; k--) {
            ans.push_back({a[k], a[k - 1]});
            swap(a[k], a[k - 1]);
        }

        assert(c[i] == a[i]);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<int> c(n);
    for (auto &i : c) cin >> i, i--;

    vector<int> a(n);
    iota(all(a), 0);

    vector<int> b = a;
    reverse(all(b));

    vector<pii> ans;
    solve(n, a, b, ans);
    solve(n, a, c, ans);

    cout << sz(ans) << '\n';
    for (auto &i : ans) {
        cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }
}
