#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int m, n;
vector<pll> a, b;

void input() {
    cin >> m >> n;
    a.resize(m);
    for (auto& i : a) cin >> i.fr >> i.sc;
    b.resize(n);
    for (auto& i : b) cin >> i.fr >> i.sc;
}

void pickup() {
    vector<pll> stk;

    sort(all(a));
    sort(all(b));

    for (auto& i : a) {
        if (!stk.empty()) {
            if (stk.back().sc <= i.sc) continue;
            stk.push_back(i);
        } else stk.push_back(i);
    }

    a = stk;
    stk.clear();

    for (auto& i : b) {
        if (!stk.empty()) {
            while (!stk.empty() && stk.back().sc <= i.sc) {
                stk.pop_back();
            }
            stk.push_back(i);
        } else stk.push_back(i);
    }

    b = stk;
}

ll ans = 0;
void f(int l, int r, int nl, int nr) {
    if (l > r) return;
    ll res = -1e18;
    int mid = (l + r) >> 1, idx = -1;
    for (int i = nl; i <= nr; i++) {
        if (b[i].fr < a[mid].fr) continue;
        ll val = (b[i].fr - a[mid].fr) * (b[i].sc - a[mid].sc);
        if (res < val) {
            res = val, idx = i;
        }
    }
    ans = max(ans, res);
    if (l < r) {
        f(l, mid - 1, nl, idx);
        f(mid + 1, r, idx, nr);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    pickup();

    for (int i = 0; i + 1 < sz(a); i++)
        assert(a[i].fr < a[i + 1].fr && a[i].sc > a[i + 1].sc);
    for (int i = 0; i + 1 < sz(b); i++)
        assert(b[i].fr < b[i + 1].fr && b[i].sc > b[i + 1].sc);

    f(0, sz(a) - 1, 0, sz(b) - 1);

    cout << ans;
}
