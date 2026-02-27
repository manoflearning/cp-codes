#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int UB = 28;

void bt(int idx, 
    const int ub, 
    const vector<int> &x, 
    const vector<int> &y,
    const vector<ll> &pow3,
    int sum_x,
    int sum_y,
    ll code,
    unordered_map<ll, ll> &mp
) {
    if (idx == ub) {
        if (code != 0) mp[sum_x * (1ll << 20) + sum_y] = code;
        return;
    }

    bt(idx + 1, ub, x, y, pow3, sum_x + x[idx], sum_y + y[idx], code + 1 * pow3[idx], mp);

    bt(idx + 1, ub, x, y, pow3, sum_x, sum_y, code, mp);

    bt(idx + 1, ub, x, y, pow3, sum_x - x[idx], sum_y - y[idx], code + 2 * pow3[idx], mp);
}

void yes() { cout << "yes\n"; }
void no(const ll code, const vector<ll> &pow3) {
    vector<int> x, y;
    for (int i = 0; i < UB; i++) {
        const int now = code / pow3[i] % 3;
        if (now == 1) x.push_back(i);
        if (now == 2) y.push_back(i);
    }

    cout << "no\n";
    cout << sz(x) << ' ';
    for (auto &i : x) cout << i + 1 << ' ';
    cout << '\n';
    cout << sz(y) << ' ';
    for (auto &i : y) cout << i + 1 << ' ';
    cout << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    n = min(n, UB);

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    const int mid = n >> 1;

    vector<pii> vec;
    unordered_map<ll, ll> mp_l, mp_r;
    vector<ll> pow3(UB);
    pow3[0] = 1;
    for (int i = 0; i + 1 < UB; i++)
        pow3[i + 1] = 3 * pow3[i];
    
    bt(0, mid, x, y, pow3, 0, 0, 0, mp_l);
    bt(mid, n, x, y, pow3, 0, 0, 0, mp_r);

    if (mp_l.count(0) || mp_r.count(0)) {
        if (mp_l.count(0)) { no(mp_l[0], pow3); exit(0); }
        if (mp_r.count(0)) { no(mp_r[0], pow3); exit(0); }
    } else {
        for (const auto &[k, vl] : mp_l) {
            if (mp_r.count(-k)) {
                no(vl + mp_r[-k], pow3);

                exit(0);
            }
        }
    }

    yes();
}
