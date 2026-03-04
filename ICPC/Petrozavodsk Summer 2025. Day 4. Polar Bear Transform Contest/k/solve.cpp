#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    int g = 0;
    for (auto &i : a) g = gcd(i, g);

    sort(all(a));

    const int cnt = a.back() / g - n;
    if (cnt % 3 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}