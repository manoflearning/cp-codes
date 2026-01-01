#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    set<pii> a;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x > y) swap(x, y);
        a.insert({x, y});
    }

    if (n == 1) {
        cout << "NO\n";
        exit(0);
    }

    int x = -1, y = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!a.count({i, j})) {
                x = i, y = j;

                i = j = n + 1;
                break;
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
        exit(0);
    }

    int p = 3;
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i == x || i == y) continue;
        ans[i] = p++;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        if (i == x) cout << 1 << ' ';
        else if (i == y) cout << 2 << ' ';
        else cout << ans[i] << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++) {
        if (i == x) cout << 1 << ' ';
        else if (i == y) cout << 1 << ' ';
        else cout << ans[i] << ' ';
    }
    cout << '\n';
}