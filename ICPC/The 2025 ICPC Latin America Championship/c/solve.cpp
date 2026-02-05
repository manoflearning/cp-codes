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

    int c, n;
    cin >> c >> n;

    vector<int> t(n);
    for (auto &i : t) cin >> i;

    int l = -50, r = 50;
    while (l < r) {
        const int mid = (l + r + 1) >> 1;

        bool yes = 1;

        int acc = 0;
        for (const int i : t) {
            if (i < mid) acc++;
            else {
                acc = 0;
            }

            yes &= (acc <= c);
        }

        if (yes) l = mid;
        else r = mid - 1;
    }

    cout << l;
}
