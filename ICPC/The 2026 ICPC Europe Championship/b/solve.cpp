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

    int n;
    string s, t;
    cin >> n >> s >> t;

    int acc = 1;
    unordered_set<ll> st_s, st_t;
    for (auto &i : s) {
        if (i == '0') acc++;
        else {
            if (st_s.count(acc)) st_s.erase(acc);
            else st_s.insert(acc);
            acc = 1;
        }
    }
    if (st_s.count(acc)) st_s.erase(acc);
    else st_s.insert(acc);
    acc = 1;

    for (auto &i : t) {
        if (i == '0') acc++;
        else {
            if (st_t.count(acc)) st_t.erase(acc);
            else st_t.insert(acc);
            acc = 1;
        }
    }
    if (st_t.count(acc)) st_t.erase(acc);
    else st_t.insert(acc);
    acc = 1;

    // DEBUG
    // for (auto &i : st_t) cout << i << '\n';

    ll ans = 0;
    for (const auto &i : st_s) for (const auto &j : st_t) ans ^= (i * j);

    cout << ans << '\n';
}
