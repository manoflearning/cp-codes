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

    int n; cin >> n;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    sort(all(a));

    ll ans = 0;
    for (int i = (n + 1) / 2; i < n; i++) ans += a[i];

    cout << ans << '\n';
}