#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

ll ans = 0;
set<pll> s;

ll cal(ll l, ll r) {
    return (r - l + 1) * (r - l + 2) / 2;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        ll op, x;
        cin >> op >> x;

        if (op == 1) {
            ll l = x, r = x;

            auto it = s.lower_bound({ x + 1, -1 });
            if (it != s.end() && it->fr == x + 1) {
                r = it->sc;
                ans -= cal(it->fr, it->sc);
                s.erase(it);
            }

            it = s.lower_bound({ x, -1 });
            if (it != s.begin()) {
                it--;
                if (it->sc == x - 1) {
                    l = it->fr;
                    ans -= cal(it->fr, it->sc);
                    s.erase(it);
                }
            }

            ans += cal(l, r);
            s.insert({ l, r });
        }
        else {
            ll l = x, r = x;

            auto it = s.lower_bound({ x + 1, -1 });
            if (it != s.begin()) {
                it--;
                l = it->fr, r = it->sc;
                ans -= cal(it->fr, it->sc);
                s.erase(it);
            }

            if (l < x) {
                ans += cal(l, x - 1);
                s.insert({ l, x - 1 });
            }
            if (x < r) {
                ans += cal(x + 1, r);
                s.insert({ x + 1, r });
            }
        }
        
        cout << ans << '\n';
    }

    return 0;
}