#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

bool valid(const ll l, const vector<ll> &a) {
    ll sum = 0;
    map<ll, ll> mp;
    for (auto &i : a) mp[i]++, sum += i;

    if (sum % l) return 0;

    for (auto &[k, v] : mp) {
        if (k == l) continue;
        else if (l < k) return 0;
        else if (l > k) {
            if (!mp.count(l - k) || mp[l - k] != v) return 0;
        }
    }
    return 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    sort(all(a));

    const ll l0 = a.back();
    const ll l1 = a.front() + a.back();

    if (valid(l0, a)) cout << l0 << ' ';
    if (valid(l1, a)) cout << l1 << ' ';

    return 0;
}
