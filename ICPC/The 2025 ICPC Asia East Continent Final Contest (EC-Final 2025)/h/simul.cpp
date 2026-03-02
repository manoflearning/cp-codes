#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int N_SIMUL = 1'000;
constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);
    
    int k, n;
    cin >> k >> n;

    vector<ll> a(k), b(n);
    ll sum_b{};
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i, sum_b += i;

    sort(all(a));

    mt19937 mt(time(NULL));

    ll sum = 0;
    for (int t = 0; t < N_SIMUL; t++) {
        shuffle(all(b), mt);

        ll res = -INF, rem_b = sum_b;
        for (int i = 0; i < k - 1; i++) {
            res = max(res, b[i]);
            rem_b -= b[i];
        }

        if (a[k - 1] <= res) {
            res = max(res, b[k - 1]);
        } else {
            const ld ev = (ld)rem_b / (n - k + 1);
            if (ev < a[k - 1]) res = max(res, a[k - 1]);
            else res = max(res, b[k - 1]);
        }

        sum += res;
    }

    cout << (ld)sum / N_SIMUL << '\n';
}
