// 01111
// 10111
// 11011
// 11101
// 11110
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int MAXB = 29;

int n;
vector<ll> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    vector<int> cnt(30);
    for (auto& i : a) {
        for (int b = 0; b <= MAXB; b++) {
            if (i & (1 << b)) cnt[b]++;
        }
    }

    ll ans = 1;
    for (int i = 0; i < n; i++) {
        ll res = 0;
        for (int b = 0; b <= MAXB; b++) {
            if (cnt[b]) cnt[b]--, res |= (1 << b);
        }
        ans = ans * res % MOD;
    }

    cout << ans;
}