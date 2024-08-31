#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

ll A, B, C, K, L;
vector<int> cyc[7];

ll power(ll x, ll y, int mod) {
    if (y == 1) return x % mod;
    ll res = power(x, y / 2, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    for (int i = 1; i <= 6; i++) {
        cyc[i].push_back(i);
        while (1) {
            int x = cyc[i].back();
            int y = x * i % 7;
            if (y == i) break;
            cyc[i].push_back(y);
        }
    }

    cin >> A >> B >> C >> K >> L;

    L = (L - K + 7) % 7;

    ll cnt = power(B, C, sz(cyc[A]));
    ll ans_1 = cyc[A][(cnt + sz(cyc[A]) - 1) % sz(cyc[A])];
    ll ans_2 = power(B, C, 7) * power(A, 5, 7) % 7;

    ll ans = 0;
    ans += (ans_1 == L ? 1 : 0);
    ans += (ans_2 == L ? 2 : 0);
    cout << ans;
}