#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int a, b, n;

long long power(long long base, int exp) {
    if (exp == 0) return 1;
    if (exp == 1) return base;

    long long res = power(base, exp / 2);
    return res * res % MOD * (exp & 1 ? base : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> a >> b >> n;

    long long p2 = power(2, n - 1);
    long long ans = power(p2, 31);

    cout << ans;
}