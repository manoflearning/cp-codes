#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = (1ll << 32);

const int MAX = 1e8;
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

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    getPrime();

    ll n; cin >> n;
    ll ans = 1;
    for (auto& i : prime) {
        if (n < i) break;
        ll x = i;
        while (x * i <= n) x *= i;
        ans = ans * x % MOD;
    }

    cout << ans;
}