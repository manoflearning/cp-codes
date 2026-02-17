#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    int mx = 0;//, mn = INF;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;

        if (s == "/") {
            cout << (mx + 9) / 10 * 10 << '\n';
            // mn = INF;
        } else {
            const int l = stoi(s);
            // mn = min(mn, l);
            cout << l << '\n';
            mx = max(mx, l + 1);
        }
    }
}
