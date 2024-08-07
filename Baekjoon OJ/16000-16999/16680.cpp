// solution 1
#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll p10[19];

void pre() {
    p10[0] = 1;
    for (int i = 1; i < 19; i++) {
        p10[i] = 10 * p10[i - 1];
    }
}

int isAnSooBinNumber(ll n) {
    int sum = 0;
    for (int i = 0; i < 19; i++) {
        if (n < p10[i]) break;
        sum += n / p10[i] % 10;
    }
    return sum & 1;
}

ll sol1(ll n) {
    return ((ll)1e9 - 1) * n;
}
ll sol2(ll n) {
    srand(time(NULL));
    while (1) {
        ll x = rand() % (ll)1e9;
        if (isAnSooBinNumber(x * n)) return x * n;
    }
}
ll sol3(ll n) {
    while (!isAnSooBinNumber(n) && n <= 2 * p10[17]) n *= 2;
    return n;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    pre();

    int tc; cin >> tc;
    while (tc--) {
        ll n; cin >> n;
        cout << sol2(n) << '\n';
    }
}