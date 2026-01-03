#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

ll n, m, k;
vector<ll> a, psum;
vector<ll> cc;

void init() {
    // TODO
}

void input() {
    cin >> n >> m >> k;
    a.resize(n);
    for (auto &i : a) cin >> i;
}

void coor_comp() {
    cc.push_back(-1);
    cc.push_back(0);
    for (auto &i : a) {
        cc.push_back(i - 1);
        cc.push_back(i);
        cc.push_back(i + 1);
    }
    cc.push_back(m);

    sort(all(cc), cc.end());
    cc.erase(unique(all(cc)), cc.end());

    for (auto &i : a) {
        i = lower_bound(all(cc), i) - cc.begin();
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        coor_comp();

        psum.assign(sz(cc), 0);
        for (auto &i : a) psum[i]++;
        
        for (int i = 1; i < sz(cc); i++) {
            psum[i] += psum[i - 1];
        }

        
    }
}
