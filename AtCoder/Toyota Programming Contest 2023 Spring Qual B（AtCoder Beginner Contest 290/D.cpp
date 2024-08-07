#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		ll n, d, k;
		cin >> n >> d >> k;

		if (d >= n) d %= n;
		if (d == 0) {
			cout << k - 1 << '\n';
			continue;
		}

		ll cnt = lcm(n, d) / d;
		
		cout << (k - 1) % cnt * d % n + (k - 1) / cnt << '\n';
	}

	return 0;
}