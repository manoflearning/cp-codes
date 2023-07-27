#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> x[111];

void init() { }

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        x[i].resize(m);
        for (auto& j : x[i]) cin >> j;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";
        
        init();

        input();

        int ans = 0;
        for (auto& i : x[0]) ans += i;
        for (auto& i : x[n - 1]) ans += i;
        
        
        for (int i = 1; i < n; i++) {
            vector<int> prv = x[i - 1];

            for (int j = 0; j < m; j++) {
                prv[j] = min(prv[j], x[i][j]);
                //prv[j] += min(x[i][j] - prv[j], x[i - 1][j] - prv[j]);
                ans += x[i][j] + x[i - 1][j] - 2 * prv[j];
            }
            cout << ans << '\n';
            for (auto& j : prv)
                cout << j << ' ';
            cout << '\n';
        }

        cout << ans << '\n';
    }
}