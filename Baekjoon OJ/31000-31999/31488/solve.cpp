#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

struct Dish {
    ll t, p;
    int idx;
};

struct Person {
    ll T, P;
    int idx;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<Dish> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].t >> a[i].p;
        a[i].idx = i;
    }

    vector<Person> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i].T >> b[i].P;
        b[i].idx = i;
    }

    sort(all(a), [](const Dish &i, const Dish &j) {
        if ((i.t - i.p) ^ (j.t - j.p)) return i.t - i.p < j.t - j.p;
        else return i.p < j.p;
    });

    auto cx = [](const Dish &i, const Dish &j) -> ld {
        return (ld)(i.p - j.p) / (j.t - j.p - i.t + i.p);
    };

    vector<Dish> stk;
    for (const Dish &i : a) {
        while (sz(stk) >= 2) {
            const Dish j = stk.back();
            stk.pop_back();
            if (cx(stk.back(), j) <= cx(j, i)) {
                stk.push_back(j);
                break;
            }
        }
        stk.push_back(i);
    }

    // DEBUG
    // for (const Dish &i : stk)
    //     cout << i.idx + 1 << '\n';

    sort(all(b), [](const Person &i, const Person &j) {
        return i.T * (j.T + j.P) < j.T * (i.T + i.P);
    });

    vector<int> ans(m);

    int j = 0, prv = -1;
    Person prv_i{-1, 1};
    for (const Person &i : b) {
        if (prv_i.T * (i.T + i.P) == i.T * (prv_i.T + prv_i.P)) {
            ans[i.idx] = prv;
        } else {
            while (j + 1 < sz(stk) && stk[j].t * i.T + stk[j].p * i.P < stk[j + 1].t * i.T + stk[j + 1].p * i.P) {
                j++;
            }

            int now = stk[j].idx;
            while (j + 1 < sz(stk) && stk[j].t * i.T + stk[j].p * i.P == stk[j + 1].t * i.T + stk[j + 1].p * i.P) {
                j++;
                now = min(now, stk[j].idx);
            }

            ans[i.idx] = now;

            prv = now;
            prv_i = i;
        }
    }
    
    for (auto &i : ans) cout << i + 1 << '\n';

    return 0;
}
