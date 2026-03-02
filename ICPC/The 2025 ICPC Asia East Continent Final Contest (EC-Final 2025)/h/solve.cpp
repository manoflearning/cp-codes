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
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;

    sort(all(a));
    sort(all(b));

    
}
