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

    vector<string> s(n);
    for (auto &i : s) cin >> i;

    vector<vector<ll>> a(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            const char c = s[i][j];
            if (c == '?') a[i][j] = -1;
            else a[i][j] = c - '0';
        }
    }

    bool yes = 1;
    for (int l = 0; l < 2 * n - 1; l++) {
        set<int> st;
        for (int i = max(0, l - (n - 1)); i <= min(n - 1, l); i++) {
            const int j = l - i;
            if (a[i][j] != -1) st.insert(a[i][j]);
        }

        if (sz(st) >= 2) {
            yes = 0;
            break;
        }

        if (st.empty()) st.insert(0);

        const int co = *st.begin();
        for (int i = max(0, l - (n - 1)); i <= min(n - 1, l); i++) {
            const int j = l - i;
            a[i][j] = co;
        }
    }
    
    if (yes) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j];
            }
            cout << '\n';
        }
    } else {
        cout << -1 << '\n';
    }
    
    return 0;
}
