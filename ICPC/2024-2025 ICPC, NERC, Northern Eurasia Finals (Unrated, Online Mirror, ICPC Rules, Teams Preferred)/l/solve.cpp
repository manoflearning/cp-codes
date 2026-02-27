#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Rect {
    int w, h, x, y, dx, dy;
};

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

ll lcm(ll x, ll y) { return x * y / gcd(x, y); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int w, h;
        cin >> w >> h;

        Rect a{}, b{};
        cin >> a.w >> a.h >> a.x >> a.y >> a.dx >> a.dy;
        cin >> b.w >> b.h >> b.x >> b.y >> b.dx >> b.dy;

        vector<pii> ax, bx, ay, by;

        auto simul = [](int W, int w, int x, int dx, vector<pii> &arr) {
            int now = x;
            for (int t = 0; t < 2 * (W - w); t++) {
                arr.push_back({now, now + w});
                if (now == 0 || now + w == W) dx *= -1;
                now += dx;
            }
        };

        simul(w, a.w, a.x, a.dx, ax);
        simul(w, b.w, b.x, b.dx, bx);
        simul(h, a.h, a.y, a.dy, ay);
        simul(h, b.h, b.y, b.dy, by);

        auto build_bit_vec = [](const vector<pii> &x, const vector<pii> &y) {
            const int lc = lcm(sz(x), sz(y));

            vector<bool> ret(lc);
            for (int t = 0; t < lc; t++) {
                const pii u = x[t % sz(x)], v = y[t % sz(y)];

                bool bit = false;
                bit |= (u.first <= v.first && v.first < u.second);
                bit |= (u.first < v.second && v.second <= u.second);
                bit |= (v.first <= u.first && u.first < v.second);
                bit |= (v.first < u.second && u.second <= v.second);

                ret[t] = bit;
            }
            return ret;
        };

        auto count_pairs = [&]() -> pair<ll, ll> {
            const auto vec1 = build_bit_vec(ax, bx);
            const auto vec2 = build_bit_vec(ay, by);

            const ll g = gcd(sz(vec1), sz(vec2));

            vector<ll> cnt1(g), cnt2(g);
            for (int i = 0; i < sz(vec1); i++) cnt1[i % g] += vec1[i];
            for (int i = 0; i < sz(vec2); i++) cnt2[i % g] += vec2[i];

            ll ret = 0;
            for (int i = 0; i < g; i++) ret += cnt1[i] * cnt2[i];
            
            return {ret, (ll)sz(vec1) * sz(vec2) / g};
        };

        auto [ans_n, ans_d] = count_pairs();
        const ll g = gcd(ans_n, ans_d);
        ans_n /= g, ans_d /= g;
        cout << ans_n << "/" << ans_d << '\n';
    }
}
