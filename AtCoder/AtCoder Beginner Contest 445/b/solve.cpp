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

    int m = 0;
    vector<string> a(n);
    for (auto &i : a) {
        cin >> i;
        m = max(m, sz(i));
    }

    for (string &i : a) {
        int k = (m - sz(i)) / 2;
        cout << string(k, '.') << i << string(k, '.') << '\n';
    }

    return 0;
}
