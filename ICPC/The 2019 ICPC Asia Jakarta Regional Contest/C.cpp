#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, q; 
    cin >> n >> q;

    vector<int> r(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= n; i++) cin >> c[i];

    vector<int> psumr(n + 1), psumc(n + 1);
    for (int i = 1; i <= n; i++) {
        psumr[i] = (r[i] & 1) + psumr[i - 1];
        psumc[i] = (c[i] & 1) + psumc[i - 1];
    }

    while (q--) {
        int ra, ca, rb, cb;
        cin >> ra >> ca >> rb >> cb;
        if (ra > rb) swap(ra, rb);
        if (ca > cb) swap(ca, cb);

        bool isValid = true;

        int cntr = psumr[rb] - psumr[ra - 1];
        int cntc = psumc[cb] - psumc[ca - 1];
        if (cntr != (rb - ra + 1) && cntr != 0) isValid = false;
        if (cntc != (cb - ca + 1) && cntc != 0) isValid = false;

        if (isValid) cout << "YES\n";
        else cout << "NO\n";
    }
}