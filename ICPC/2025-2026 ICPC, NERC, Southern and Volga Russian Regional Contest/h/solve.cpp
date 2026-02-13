#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

ll sum(ll l, ll r) {
    return (l + r) * (r - l + 1) / 2;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        ll lm, rm, lb, rb;
        cin >> lm >> rm >> lb >> rb;
        rm += lm, lm += lm + 1;

        ll l = 0, r = min(rm - lm + 1, (rb - lb + 1) / 2);
        while (l < r) {
            const ll mid = (l + r + 1) >> 1;
            const ll summ = sum(rm - mid + 1, rm);
            const ll sumb = sum(lb, lb + 2 * mid - 1);
            if (summ >= sumb) l = mid;
            else r = mid - 1;
        }

        cout << l << '\n';
    }
}