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

    int q; cin >> q;

    int vol = 0;
    bool play = 0;
    while (q--) {
        int x; cin >> x;

        if (x == 1) vol++;
        if (x == 2) vol = max(0, vol - 1);
        if (x == 3) play = !play;

        cout << (vol >= 3 && play ? "Yes" : "No") << '\n';
    }

    return 0;
}
