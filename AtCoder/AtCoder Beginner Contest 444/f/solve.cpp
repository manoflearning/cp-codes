#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

inline void insert_d(const ll l, const ll w, ll &cnt_d, ll &lazy_op_d) {
    cnt_d += w;
    lazy_op_d += (l - 1) * w;
}

inline void insert_u(const ll l, const ll w, vector<pll> &vec_u, ll &cnt_u) {
    vec_u.push_back({l, w});
    cnt_u += w;
}

bool f(const ll t, const ll m, const vector<ll> &a) {
    vector<pll> vec_u{};
    ll cnt_u{};
    ll cnt_d{}, lazy_op_d{};
    ll cnt_op{};

    for (const ll l : a) {
        if (l / 2 >= t) {
            int d = 0;
            while ((l >> d) >= 2 * t) d++;

            const ll p = 1ll << d;
            const ll q = l / p;
            const ll r = l % p;

            if (q <= 2 * t - 2) {
                const ll both = min(m - cnt_op, p - 1);
                cnt_op += both;
                if (both == p - 1) {
                    insert_u(q, p - r, vec_u, cnt_u);
                    insert_u(q + 1, r, vec_u, cnt_u);
                } else {
                    insert_u(t, both + 1, vec_u, cnt_u);
                }
            } else {
                const ll both = min(m - cnt_op, p - 1 + r);
                cnt_op += both;
                if (both == p - 1 + r) {
                    insert_u(2 * t - 1, p - r, vec_u, cnt_u);
                    insert_u(t, 2 * r, vec_u, cnt_u);
                } else {
                    insert_u(t, both + 1, vec_u, cnt_u);
                }
            }
        } else if (l < t) {
            insert_d(l, 1, cnt_d, lazy_op_d);
        } else if (l >= t) {
            insert_u(l, 1, vec_u, cnt_u);
        }
    }

    vec_u.push_back({t, 0});
    sort(vec_u.begin(), vec_u.end());

    auto it = vec_u.end();
    if (it != vec_u.begin()) it--;
    while (cnt_op < m && cnt_d < cnt_u) {
        const ll both = min(m - cnt_op, lazy_op_d);
        if (both > 0) {
            cnt_op += both;
            cnt_d += both, lazy_op_d -= both;
        } else {
            const ll l0 = it->first / 2, l1 = l0 + (it->first & 1);
            const ll add_once = 1 + (l0 - 1) + (l1 - 1) * (l1 < t);
            const ll w = min(it->second, ((m - cnt_op) + add_once - 1) / add_once);

            cnt_op += w;

            it->second -= w;
            cnt_u -= w;
            if (it->second == 0) {
                if (it != vec_u.begin()) it--;
            }

            insert_d(l0, w, cnt_d, lazy_op_d);
            if (l1 < t) insert_d(l1, w, cnt_d, lazy_op_d);
            else {
                vec_u.front().second += w;
                cnt_u += w;
            }
        }
    }

    return cnt_d < cnt_u;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        ll m;
        cin >> n >> m;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll l = 1, r = *max_element(all(a));
        while (l < r) {
            const ll mid = (l + r + 1) >> 1;

            if (f(mid, m, a)) l = mid;
            else r = mid - 1;
        }

        cout << l << '\n';
    }

    return 0;
}

// median이 mid 이상이 되도록 연산을 수행할 수 있는가? (결정 문제)
// (1) floor(l / 2) >= mid인 stick들을 다 쪼개기
// (2) l < mid인 stick들을 다 쪼개기
// (3) mid <= l인 stick들을 다 쪼개기