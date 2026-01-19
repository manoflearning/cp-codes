#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;

    vector<int> lm(n + 1, -1), rm(n + 1, -1);
    for (int i = 0; i < n; i++) {
        if (lm[a[i]] == -1) lm[a[i]] = i;
        rm[a[i]] = i;
    }

    vector<pii> b;
    for (int x = 1; x <= n; x++) {
        if (lm[x] + 1 < rm[x]) {
            b.push_back({lm[x], rm[x]});
        }
    }

    sort(all(b));

    int ub = -1;
    vector<pii> nb;
    for (const auto &[l, r] : b) {
        if (ub < r) {
            pii prv = {-1, -1};
            while (!nb.empty() && l < nb.back().second) {
                prv = nb.back();
                nb.pop_back();
            }
            if (prv.first != -1) nb.push_back(prv);

            nb.push_back({l, r});
        }
        ub = max(ub, r);
    }
    b = nb;

    if (b.empty()) {
        cout << 0 << '\n';
        exit(0);
    }

    int ans = 0;

    int pr = -1;
    for (const auto &[l, r] : b) {
        if (pr < l) {
            ans += r - l - 1;
        } else {
            ans += r - pr;
            ans--;
        }
        pr = r;
    }

    cout << ans << '\n';
}
