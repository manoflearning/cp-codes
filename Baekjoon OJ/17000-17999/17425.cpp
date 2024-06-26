#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 1e6;
bool isPrime[MAX + 1];
vector<int> prime(1, 2);
void getPrime() {
    fill(isPrime + 2, isPrime + MAX + 1, 1);
    for (ll i = 4; i <= MAX; i += 2)
        isPrime[i] = 0;
    for (ll i = 3; i <= MAX; i += 2) {
        if (!isPrime[i]) continue;
        prime.push_back(i);
        for (ll j = i * i; j <= MAX; j += i * 2)
            isPrime[j] = 0;
    }
}

ll dp[MAX + 1], psum[MAX + 1];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // initialize
    getPrime();

    dp[1] = psum[1] = 1;
    for (int i = 2; i <= MAX; i++) {
        int x = i;
        dp[i] = 1;
        for (auto& p : prime) {
            if (sqrt(x) < p) break;
            ll sum = 1, powp = 1;
            while (x % p == 0) {
                x /= p;
                powp *= p;
                sum += powp;
            }
            if (sum > 1) dp[i] *= sum;
        }
        if (x > 1) dp[i] *= (1 + x);

        psum[i] = dp[i] + psum[i - 1];
    }

    // solve
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        cout << psum[n] << '\n';
    }
}