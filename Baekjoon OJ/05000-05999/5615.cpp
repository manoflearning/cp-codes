#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const int MAX = 65536;
bool isPrime[MAX + 1];
vector<int> prime;
void getPrime() {
	fill(isPrime + 2, isPrime + MAX + 1, 1);
	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAX; i++) {
		if (isPrime[i]) prime.push_back(i);
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

    int n; cin >> n;
    unordered_map<ll, int> mp;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        mp[x << 1 | 1]++;
    }

	for (auto& i : prime) {
        vector<ll> res;
        for (auto& j : mp) {
            if (j.fr % i == 0) {
                res.push_back(j.fr);
            }
        }

        for (auto& j : res) mp[j] = 0;
    }

    int ans = 0;
    for (auto& i : mp)
        ans += i.sc;

    cout << ans;

	return 0;
}