#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll A = 1e12;

vector<ll> naive_one_game(vector<ll> a) {
    const int n = sz(a);
    int n_stones = 1;
    for (int i = 0; i < n; i++) {
        a[i]++, n_stones--;
        if (n_stones == 0) {
            if (a[i] == 1) break;
            else n_stones = a[i], a[i] = 0;
        }
    }
    return a;
}

template<bool PRINT>
vector<ll> naive(ll t, vector<ll> a) {
    for (int turn = 0; turn < t; turn++) {
        a = naive_one_game(a);
        
        if (PRINT) {
            for (auto &i : a) cout << i << ' ';
            cout << '\n';
        }
    }
    return a;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    mt19937 mt(time(NULL));
    uniform_int_distribution<ll> rng(0, A);


    int n;
    ll t;
    cin >> n >> t;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    naive<true>(t, a);
}
