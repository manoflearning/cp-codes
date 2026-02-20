#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int N = 1'000'000;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

void solve(ll a, ll b) {
    for (ll n = b; n <= N; n += b) {
        const ll tgt = n / b * a;
        if (tgt < n - 1) break;

        ll sum = n - 1;
        vector<ll> y(1, n - 1);

        while (sum < tgt && y.back() > 1) {
            const int mx = min(y.back() - 1, tgt - sum);
            sum += mx;
            y.push_back(mx);
        }

        if (sum != tgt) continue;

        for (auto &i : y) i++;

        cout << n << ' ' << n - 1 << '\n';
        for (int i = 0; i < sz(y); i++) {
            for (int j = y[i]; j >= (i + 1 == sz(y) ? 2 : y[i + 1] + 1); j--) {
                cout << (i == 0 ? 1 : y[i - 1]) << ' ' << j << '\n';
            }
        }

        return;
    }

    cout << "impossible\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll a{}, b{};
    string s, acc; cin >> s;
    for (char c : s) {
        if (c == '/') a = stoi(acc), acc.clear();
        else acc += c;
    }
    b = stoi(acc);

    solve(a, b);

    // TEST
    // for (ll a = 1; a <= 1000; a++) {
    //     for (ll b = 1; b <= 1000; b++) {
    //         const ll g = gcd(a, b);
    //         a /= g, b /= g;
    //         solve<false>(a, b);
    //     }
    // }
}
