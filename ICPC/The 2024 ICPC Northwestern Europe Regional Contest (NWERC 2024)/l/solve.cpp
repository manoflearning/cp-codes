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

    int n, m;
    ll x, y;
    cin >> n >> m >> x >> y;

    vector<ll> a(n), b(m);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;

    sort(all(a));
    sort(all(b));

    int lo = -1, hi = n;
    while (lo < hi) {
        const int mid = (lo + hi + 1) >> 1;

        int j = 0;
        for (int i = 0; i < n; i++) {
            int rem = (i < mid ? y : x);
            while (rem > 0 && j < m && b[j] <= a[i]) {
                rem--, j++;
            }
        }

        if (j == m) lo = mid;
        else hi = mid - 1;
    }

    if (lo == -1) {
        cout << "impossible\n";
    } else {
        cout << lo << '\n';
    }
}
