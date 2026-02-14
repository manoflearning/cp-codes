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

    int n; cin >> n;

    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
        i--;
    }

    vector<int> ans = a;
    for (int i = n - 1; i >= 0; i--) {
        if (i < ans[i]) ans[i] = max(ans[i], ans[ans[i]]);
    }

    for (auto &i : ans) cout << i + 1 << ' ';

    return 0;
}
