#pragma GCC optimize("O3")
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

constexpr int BOUND = 16;

int k, n;
vector<ll> g, pg;
int a = -1, b = -1, c = -1, d = -1;

void init() {
    g.clear();
    pg.clear();
    a = b = c = d = -1;
}

void input() {
    cin >> k;
    n = (1 << (k + 1));
    g.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> g[i];
    }
}

void sol_naive() {
    unordered_map<ll, int> mp;
    for (int i = 1; i <= n; i++) {
        mp[pg[i - 1]] = i;

        for (int j = i + 1; j <= n; j++) {
            for (int k = j; k <= n; k++) {
                ll res = 0;
                res ^= pg[k];
                res ^= pg[j - 1];
                res ^= pg[i];

                auto it = mp.find(res);
                if (it != mp.end()) {
                    a = it->sc, b = i, c = j, d = k;
                    return;
                }
            }
        }
    }
}

void sol_random(uniform_int_distribution<int> &dis, mt19937_64 &eng) {
    unordered_map<ll, int> mpr;
    for (int i = 1; i <= n; i++) {
        if (mpr.count(pg[i]) && mpr[pg[i]] + 1 < i) {
            a = b = mpr[pg[i]] + 1;
            c = mpr[pg[i]] + 2, d = i;
            return;
        }
        mpr[pg[i]] = i;
    }

    while (1) {
        array<int, 4> arr{};
        arr[0] = dis(eng);
        arr[1] = dis(eng);
        arr[2] = dis(eng);

        if (arr[0] == arr[1] || arr[1] == arr[2] || arr[0] == arr[2]) continue;

        ll res = 0;
        res ^= pg[arr[2]];
        res ^= pg[arr[1]];
        res ^= pg[arr[0]];

        auto it = mpr.find(res);

        if (it != mpr.end() && it->sc != arr[0] && it->sc != arr[1] && it->sc != arr[2]) {
            arr[3] = it->sc;
            sort(all(arr));
            a = arr[0] + 1, b = arr[1], c = arr[2] + 1, d = arr[3];
            return;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    random_device rd;
    mt19937_64 eng(rd());
    
    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        pg.resize(n + 1);
        for (int i = 1; i <= n; i++)
            pg[i] = g[i] ^ pg[i - 1];

        if (n <= BOUND) {
            sol_naive();
        } else {
            uniform_int_distribution<int> dis(0, n);
            sol_random(dis, eng);
        }

        if (a == -1) {
            cout << -1 << '\n';
        } else {
            ll res = 0;
            res ^= pg[a - 1] ^ pg[b] ^ pg[c - 1] ^ pg[d];
            assert(res == 0);
            
            cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
        }
    }
}
