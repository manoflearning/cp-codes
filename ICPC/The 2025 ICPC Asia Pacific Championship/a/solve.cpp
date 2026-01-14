#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int r, c;
    cin >> r >> c;
    vector<string> a(r);
    for (auto &i : a) cin >> i;

    ll ans = 0;

    vector<ll> cntR(r), cntC(c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] == '.') cntR[i]++, cntC[j]++;
        }
    }

    for (int i = 0; i < r; i++) {
        ll acc = 0, sum = 0;
        for (int j = 0; j < c; j++) {
            if (a[i][j] == '#') continue;

            ll res = 0;
            res += (acc * (cntR[i] - 2) + sum) * (cntR[i] + cntC[j] - 3);
            res -= acc * (cntR[i] - 2);

            ans += res * 2;

            acc++;
            sum += cntC[j] - 1;
        }
    }

    for (int j = 0; j < c; j++) {
        ll acc = 0, sum = 0;
        for (int i = 0; i < r; i++) {
            if (a[i][j] == '#') continue;

            ll res = 0;
            res += (acc * (cntC[j] - 2) + sum) * (cntC[j] + cntR[i] - 3);
            res -= acc * (cntC[j] - 2);

            ans += res * 2;

            acc++;
            sum += cntR[i] - 1;
        }
    }

    cout << ans << '\n';
}
