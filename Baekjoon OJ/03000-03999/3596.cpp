#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2020;

int gn[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    gn[0] = 0;
    gn[1] = 1;
    gn[2] = 1;
    for (int i = 3; i < MAXN; i++) {
        vector<bool> vis(75);
        if (i >= 3) vis[gn[i - 3]] = 1;
        if (i >= 4) vis[gn[i - 4]] = 1;
        if (i >= 5) {
            for (int j = 0; j <= i - 5; j++) {
                int k = (i - 5) - j;
                vis[gn[j] ^ gn[k]] = 1;
            }
        }

        for (int j = 0; j < 75; j++)
            if (!vis[j]) { gn[i] = j; break; }

        // cout << i << ' ' << gn[i] << '\n';
    }

    int n; cin >> n;
    cout << (gn[n] > 0 ? 1 : 2);
}
