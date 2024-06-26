#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

ll lb, ub, n;
vector<ll> p;
ll ans = 0;

void init() {
    p.clear();
    ans = 0;
}

void bt(int idx, ll x, int cnt) {
    if (idx == sz(p)) {
        if (cnt == 0) return;

        if (cnt & 1) ans += (ub / x) - ((lb - 1) / x);
        else ans -= (ub / x) - ((lb - 1) / x);
        return;
    }

    bt(idx + 1, x, cnt);
    bt(idx + 1, x * p[idx], cnt + 1);
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

        cin >> lb >> ub >> n;

        for (ll i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                p.push_back(i);
                while (n % i == 0) n /= i;
            }
        }
        if (n > 1) p.push_back(n);

        bt(0, 1, 0);
        
        cout << ub - lb + 1 - ans << '\n';
    }

	return 0;
}