#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAX = 10101010;

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

ll dp[MAX];

int main() {
    freopen("prime_subtractorization_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    getPrime();

    dp[1] = 0;
    dp[2] = 0;
    dp[3] = 0;
    dp[5] = 2;

    for (int i = 2; i < sz(prime); i++) {
        int p = prime[i];
        if (isPrime[p + 2] && p + 2 < MAX) dp[p + 2]++;
    }

    for (int i = 1; i < MAX; i++) {
        dp[i] += dp[i - 1];
    }

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";
        int n; cin >> n;
        cout << dp[n] << '\n'; 
    }
}
