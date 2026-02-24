#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;

    ll ans = 0;
    ans += a * b * e * f * g;
    ans += c * d * e * f * g;
    cout << ans << '\n';
}