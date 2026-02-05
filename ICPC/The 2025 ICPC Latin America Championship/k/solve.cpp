#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 1e9 + 7;

struct Card {
    char op;
    ll x, y;
};

bool valid(int n, ll p, ll h, const vector<Card> &a) {
    bool pp = 0, qq = 0;
    pp |= (p > 0);
    for (const auto &i : a) pp |= (i.op == '+');
    for (const auto &i : a) qq |= (i.op == '!');
    return pp && qq;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n;
    ll p, h;
    cin >> n >> p >> h;

    vector<Card> a(n, Card{});
    for (auto &i : a) {
        cin >> i.op;
        if (i.op == '*') cin >> i.x;
        else if (i.op == '+') cin >> i.y;
    }

    if (!valid(n, p, h, a)) {
        cout << "*";
        return 0;
    }

    vector<ll> add{}, mul{};
    ll cnt_attack{};
    for (const auto &i : a) {
        if (i.op == '+') add.push_back(i.y);
        else if (i.op == '*') mul.push_back(i.x);
        else cnt_attack++;
    }

    sort(add.rbegin(), add.rend());
    sort(mul.rbegin(), mul.rend());

    {
        bool static_power = 1;
        if (!add.empty()) static_power = 0;
        for (auto &i : mul) {
            if (i > 1) static_power = 0;
        }

        if (static_power) {
            const ll tot_attack = (h + p - 1) / p;
            
            ll ans = 0;
            ans += (tot_attack - 1) / cnt_attack * n;
            ans += tot_attack % cnt_attack == 0 ? cnt_attack : tot_attack % cnt_attack;
            cout << ans << '\n';
            return 0;
        }
    }

    ll ans = 0;
    ll p_now = p, h_now = h;
    while (1) {
        ll p_nxt = p_now;
        for (const ll i : add) p_nxt = min(INF, p_nxt + i);
        for (const ll i : mul) p_nxt = min(INF, p_nxt * i);

        if (h_now <= p_nxt * cnt_attack) {
            ll opt = INF;

            ll res0 = p_now;
            for (int i = 0; i < sz(add); i++) {
                ll res1 = res0;
                for (int j = 0; j < sz(mul); j++) {
                    if (h_now <= res1 * cnt_attack) {
                        opt = min(opt, i + j + (h_now + res1 - 1) / res1);
                    }
                    res1 = min(INF, res1 * mul[j]);
                }
                if (h_now <= res1 * cnt_attack) {
                    opt = min(opt, i + sz(mul) + (h_now + res1 - 1) / res1);
                }

                res0 = min(INF, res0 + add[i]);
            }
            ll res1 = res0;
            for (int j = 0; j < sz(mul); j++) {
                if (h_now <= res1 * cnt_attack) {
                    opt = min(opt, sz(add) + j + (h_now + res1 - 1) / res1);
                }
                res1 = min(INF, res1 * mul[j]);
            }
            if (h_now <= res1 * cnt_attack) {
                opt = min(opt, sz(add) + sz(mul) + (h_now + res1 - 1) / res1);
            }

            ans += opt;

            break;
        }

        p_now = p_nxt;
        h_now -= p_nxt * cnt_attack;
        ans += n;
    }

    cout << ans << '\n';
}
