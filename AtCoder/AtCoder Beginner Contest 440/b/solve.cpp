#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    vector<int> t(n);
    for (auto &i : t) cin >> i;

    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) {
        return t[i] < t[j];
    });

    cout << ord[0] + 1 << ' ' << ord[1] + 1 << ' ' << ord[2] + 1;
}