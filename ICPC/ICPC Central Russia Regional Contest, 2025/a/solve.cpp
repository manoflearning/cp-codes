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

    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    ll ans = 0;
    for (auto &i : a) {
        ans += (i + k - 1) / k;
    }
    cout << ans;
}
