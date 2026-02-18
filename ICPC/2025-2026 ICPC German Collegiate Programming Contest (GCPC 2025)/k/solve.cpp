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

    int n, a, b;
    cin >> n >> a >> b;

    if (a + b < 3 || n + 1 < a + b) {
        cout << "no\n";
        exit(0);
    }

    a--, b--;

    vector<int> l, r;
    int st = n - 1;
    while (a--) l.push_back(st--);
    while (b--) r.push_back(st--);
    reverse(all(l));

    if (!l.empty()) {
        while (st > 0) l.push_back(st--);
    } else {
        reverse(all(r));
        while (st > 0) r.push_back(st--);
        reverse(all(r));
    }

    cout << "yes\n";
    for (auto &i : l) cout << i << ' ';
    cout << n << ' ';
    for (auto &i : r) cout << i << ' ';
    cout << '\n';
}
