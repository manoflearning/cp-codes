#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 252525;
const int MAXD = 49;

int n;
vector<ll> a;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

int ans = 0;
unordered_map<ll, pair<int, int>> dep[MAXD + 1];

void add(ll v, int w) {
    for (int d = 0; d <= MAXD; d++) {
        if ((1ll << d) <= v && v < (1ll << (d + 1))) {
            auto& it = dep[d][v];
            if (it.sc) it.fr += w - 1;
            else it.fr += w;
            it.sc++;
            break;
        }
    }
}
void add(ll v, int w, int d) {
    auto& it = dep[d][v];
    if (it.sc) it.fr += w - 1;
    else it.fr += w;
    it.sc++;
}

void solve() {
    for (auto& v : a) add(v, 1);
    
    for (int d = MAXD; d >= 0; d--) {
        for (auto [v, it] : dep[d]) {
            if (it.sc > 1) {
                ans += it.fr;
                if (v > 1) add(v >> 1, 1, d - 1);
            }
            else if (v > 1) add(v >> 1, it.fr + 1, d - 1);
        }
        dep[d].clear();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}