#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

ll cnt[26];

string s;
ll n;

ll powxy(ll x, ll y) {
    if (!y) return 1;
    if (y == 1) return x;
    ll res = powxy(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main(){
    cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> s >> n;
    
    ll res1 = 0;
    for (auto& c : s) {
        int x = c - 'a';
        for (int i = x + 1; i < 26; i++) {
            res1 += cnt[i];
        }
        cnt[x]++;
    }

    ll res2 = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            res2 = (res2 + cnt[j] * cnt[i]) % MOD;
        }
    }

    ll ans = 0;
    ans = (ans + res1 * (n % MOD)) % MOD;
    ans = (ans + res2 * (n % MOD) % MOD * ((n % MOD) + MOD - 1) % MOD * powxy(2, MOD - 2) % MOD) % MOD;

    cout << ans;
}
