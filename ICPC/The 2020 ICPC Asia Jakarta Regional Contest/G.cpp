#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 998'244'353;
const int MAXN = 101010;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int n, p[MAXN];
int vi[MAXN];
vector<int> len;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];
}

void partitions() {
    for (int v = 1; v <= n; v++) {
        if (vi[v]) continue;

        vector<int> arr(1, v);
        for (int i = p[v]; i != v; i = p[i]) {
            arr.push_back(i);
        }
        
        len.push_back(sz(arr));

        for (auto& i : arr) {
            vi[i] = 1;
        }
    }
}

ll ans1 = 1, ans2 = 0;
map<int, int> fac;

void solve() {
    for (auto l : len) {
        ll x = 1 % l;
        vector<int> arr;
        map<int, int> mp;
        ll st = -1, t = -1;

        while (1) {
            if (mp.count(x)) {
                st = mp[x];
                t = sz(arr) - mp[x];
                break;
            }

            mp[x] = sz(arr);
            arr.push_back(x);
            x = x * 2 % l;
        }
        
        assert(t != -1);

        for (int p = 2; p * p <= t; p++) {
            if (t % p) continue;
            int cnt = 0;
            while (t % p == 0) { cnt++; t /= p; }
            fac[p] = max(fac[p], cnt);
        }
        if (t > 1) fac[t] = max(fac[t], 1);

        ans2 = max(ans2, st);
    }

    for (auto& i : fac) {
        ans1 = ans1 * power(i.first, i.second) % MOD;
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

    partitions();

    solve();

    cout << (ans1 + ans2) % MOD;
}