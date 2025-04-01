#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int MAX = 101010;
const int D = 27;

string s, t;
ll dexp1[MAX], dexp2[MAX];
ll hs1[MAX], hs2[MAX];
ll ht1[MAX], ht2[MAX];

void rabin_karp() {
    dexp1[0] = dexp2[0] = 1;
    for (int i = 1; i <= sz(s); i++) {
        dexp1[i] = D * dexp1[i - 1] % MOD1;
        dexp2[i] = D * dexp2[i - 1] % MOD2;
    }

    for (int i = 0; i < sz(s); i++) {
        hs1[i + 1] = (D * hs1[i] + s[i] - 'A') % MOD1;
        hs2[i + 1] = (D * hs2[i] + s[i] - 'A') % MOD2;

        ht1[i + 1] = (D * ht1[i] + t[i] - 'A') % MOD1;
        ht2[i + 1] = (D * ht2[i] + t[i] - 'A') % MOD2;
    }
}

int get_start(int len) {
    unordered_set<ll> vis;
    for (int i = len; i <= sz(s); i++) {
        ll res1 = ((hs1[i] - hs1[i - len] * dexp1[len]) % MOD1 + MOD1) % MOD1;
        ll res2 = ((hs2[i] - hs2[i - len] * dexp2[len]) % MOD2 + MOD2) % MOD2;
        vis.insert(res1 + res2 * MOD1);
    }

    for (int i = len; i <= sz(t); i++) {
        ll res1 = ((ht1[i] - ht1[i - len] * dexp1[len]) % MOD1 + MOD1) % MOD1;
        ll res2 = ((ht2[i] - ht2[i - len] * dexp2[len]) % MOD2 + MOD2) % MOD2;
        if (vis.count(res1 + res2 * MOD1)) return i - len;
    }
    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;
    t = s;
    reverse(all(t));
    for (int i = 0; i < sz(t); i++) {
        if (t[i] == 'A') t[i] = 'T';
        else if (t[i] == 'G') t[i] = 'C';
        else if (t[i] == 'C') t[i] = 'G';
        else if (t[i] == 'T') t[i] = 'A';
        else assert(0);
    }

    rabin_karp();

    int l = 0, r = sz(s), ans = -1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;

        int res = get_start(mid);
        if (res == -1) r = mid - 1;
        else l = mid, ans = res;
    }

    cout << l << '\n';
    if (l) cout << s.substr(ans, l);
}
