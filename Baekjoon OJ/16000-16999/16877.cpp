#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    vector<int> fib;
    fib.push_back(1);
    fib.push_back(2);
    while (fib.back() < 3030303) {
        fib.push_back(fib[sz(fib) - 2] + fib[sz(fib) - 1]);
    }

    vector<int> gn(3030303);
    gn[0] = 0;
    for (int i = 1; i < 3030303; i++) {
        vector<bool> vis(35);
        for (auto& j : fib) {
            if (j > i) break;
            vis[gn[i - j]] = 1;
        }
        for (int j = 0; j <= sz(fib); j++) {
            if (!vis[j]) { gn[i] = j; break; }
        }
    }

    int n; cin >> n;

    int gn_acc = 0;
    for (int i = 1; i <= n; i++) {
        int p; cin >> p;
        gn_acc ^= gn[p];
    }

    cout << (gn_acc != 0 ? "koosaga" : "cubelover");
}
