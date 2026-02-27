#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Wave {
    ll p, l, a;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; ll w;
    cin >> n >> w;

    vector<Wave> waves;
    while (n--) {
        char op; cin >> op;

        if (op == '!') {
            ll p, l, a;
            cin >> p >> l >> a;
            waves.push_back({p, l, a});
        } else {
            ll p; cin >> p;

            ll ans = 0;
            for (auto &i : waves) {
                if (p < i.p || i.p + i.l <= p) continue;
                if ((p - i.p) & 1) continue;

                if ((p - i.p) & 3) ans -= i.a;
                else ans += i.a;
            }

            cout << ans << '\n';
        }
    }
}
