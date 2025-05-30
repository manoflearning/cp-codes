#include <bits/stdc++.h>
using namespace std;

const int MAXD = 20;

int n;
struct Node { int L, R; };
vector<Node> a;
int par[2020202][MAXD + 1];
int mnL[2020202];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < 2020202; i++) mnL[i] = i;

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.L >> i.R;
        i.L += 1'000'000;
        i.R += 1'000'000;
        mnL[i.R] = min(mnL[i.R], i.L);
    }

    int mn = 1e9 + 7;
    for (int i = 2020202 - 1; i >= 0; i--) {
        mn = min(mn, mnL[i]);
        par[i][0] = mn;
    }

    for (int d = 1; d <= MAXD; d++) {
        for (int i = 0; i < 2020202; i++) {
            par[i][d] = par[par[i][d - 1]][d - 1];
        }
    }

    int q; cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int L1 = a[u].L, R1 = a[u].R, L2 = a[v].L, R2 = a[v].R;

        if (L1 < L2) { swap(L1, L2); swap(R1, R2); }

        if (L1 <= R2) {
            cout << 1 << '\n';
            continue;
        }

        int ans = 0;
        for (int d = MAXD; d >= 0; d--) {
            if (R2 < par[L1][d]) {
                L1 = par[L1][d];
                ans += (1 << d);
            }
        }

        L1 = par[L1][0], ans += 2;

        if (L1 <= R2) cout << ans << '\n';
        else cout << -1 << '\n';
    }
}