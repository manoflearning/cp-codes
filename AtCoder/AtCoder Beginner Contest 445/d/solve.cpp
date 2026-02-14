#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Piece {
    ll h, w;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll h, w;
    int n;
    cin >> h >> w >> n;

    vector<Piece> a(n);
    for (auto &i : a) cin >> i.h >> i.w;

    vector<int> stk_h(n), stk_w(n);
    iota(all(stk_h), 0);
    iota(all(stk_w), 0);
    sort(all(stk_h), [&](int i, int j) {
        return a[i].h < a[j].h;
    });
    sort(all(stk_w), [&](int i, int j) {
        return a[i].w < a[j].w;
    });


    vector<pii> ans(n, {-1, -1});

    vector<bool> vis(n);
    ll now_h = h, now_w = w;
    while (1) {
        while (!stk_h.empty() && vis[stk_h.back()]) stk_h.pop_back();
        while (!stk_w.empty() && vis[stk_w.back()]) stk_w.pop_back();

        assert(stk_h.empty() == stk_w.empty());
        if (stk_h.empty()) break;

        if (a[stk_h.back()].h == now_h) {
            const int idx = stk_h.back();

            ans[idx].first = 0;
            ans[idx].second = now_w - a[idx].w;

            now_w = now_w - a[idx].w;
            vis[idx] = 1;
        } else {
            assert(a[stk_w.back()].w == now_w);

            const int idx = stk_w.back();
            ans[idx].first = now_h - a[idx].h;
            ans[idx].second = 0;

            now_h = now_h - a[idx].h;
            vis[idx] = 1;
        }
    }

    for (auto &i : ans) {
        cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }

    return 0;
}
