#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <format>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 1'169'996'969;
constexpr int MAX = 18181;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

bool is_prime[MAX + 1];
vector<int> prime(1, 2);
vector<int> prime_acc;

void get_prime() {
    fill(is_prime + 2, is_prime + MAX + 1, 1);
    for (ll i = 4; i <= MAX; i += 2)
        is_prime[i] = 0;
    for (ll i = 3; i <= MAX; i += 2) {
        if (!is_prime[i]) continue;
        prime.push_back(i);
        for (ll j = i * i; j <= MAX; j += i * 2) {
            is_prime[j] = 0;
        }
    }

    prime_acc.resize(sz(prime));
    for (int i = 1; i <= 2000; i++) {
        prime_acc[i] = prime[i - 1] + prime_acc[i - 1];
    }
}

void bottomup(int n, vector<ll> &dp) {
    for (int i = prime_acc[n - 1]; i >= 0; i--) {
        dp[i + prime[n - 1]] = (dp[i + prime[n - 1]] + dp[i]) % MOD;
    }
}

string to_base36(unsigned long long n) {
    if (n == 0) return "0";
    string s = "";
    const char* chars = "0123456789abcdefghijklmnopqrstuvwxyz";
    while (n > 0) {
        s += chars[n % 36];
        n /= 36;
    }
    reverse(all(s));
    return s;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    get_prime();

    vector<ll> dp(prime_acc[2000] + 1);
    
    dp[0] = 1;

    for (int n = 1; n <= 2000; n++) {
        bottomup(n, dp);

        if (n >= 2) {
            map<int, ll> ans;

            for (int i = 0; i < 10; i++) {
                int p = prime[i];
                for (int j = i; j < 10; j++) {
                    int q = prime[j];

                    int g = gcd(p, q);

                    if (prime_acc[n] % (p/g + q/g)) {
                        ans[n * 30 * 30 + p/g * 30 + q/g] = 0;
                        continue;
                    }

                    ans[n * 30 * 30 + p/g * 30 + q/g] = dp[prime_acc[n] / (p/g + q/g) * p/g];
                }
            }

            for (auto &[k, v] : ans) {
                if (v) {
                    cout << to_base36((ll)k * MOD + v) << " ";
                }
            }
        }
    }
}
