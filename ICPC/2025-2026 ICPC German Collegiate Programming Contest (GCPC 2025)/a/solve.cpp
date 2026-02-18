#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

ll naive(int l, int r) {
    deque<int> dq_l, dq_r;
    for (int i = 0; i < l; i++) dq_l.push_front(i);
    for (int i = l; i < l + r; i++) dq_r.push_back(i);

    int turn = 0;
    set<pii> st;
    set<tuple<deque<int>, deque<int>, int>> vis;
    while (!vis.count({dq_l, dq_r, turn})) {
        vis.insert({dq_l, dq_r, turn});
        st.insert({min(dq_l.back(), dq_r.front()), max(dq_l.back(), dq_r.front())});
        if (turn == 0) {
            int x = dq_l.back(); dq_l.pop_back();
            dq_r.push_back(x);
            turn = 1;
        } else {
            int x = dq_r.front(); dq_r.pop_front();
            dq_l.push_front(x);
            turn = 0;
        }
    }
    return sz(st);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

// TEST
// for (ll l = 2; l <= 30; l++)
// for (ll r = 1; r <= 30; r++) {
// cout << "l = " << l << ", " << "r = " << r << '\n';

// cout << "correct = " << naive(l, r) << '\n';
    ll l, r;
    cin >> l >> r;

    ll ans = 0;
    if (l - 1 == r) {
        ans += l + r;
    } else {
        if (l == r) {
            ans += l;
            ans += l + r;
        } else if (2 * (l - 1) == l + r) {
            ans += l - 1;
            ans += l + r;
        } else {
            ans += l + r;
            ans += l + r;
        }
    }

    cout << ans << '\n';
// cout.flush();
// assert(naive(l, r) == ans);
// }
}
