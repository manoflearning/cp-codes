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

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;

    bool yes = 0;

    int i = 0;
    for (int j = 0; j < m; j++) {
        while (i < n && a[i] != b[j]) {
            if (j > 0 && a[i] == b[j - 1]) yes = 1;
            i++;
        }
        i++;
    }
    for (int j = i; j < n; j++) {
        yes |= a[j] == b.back();
    }

    yes &= (i <= n);

    cout << (yes ? "Yes" : "No");

    return 0;
}
