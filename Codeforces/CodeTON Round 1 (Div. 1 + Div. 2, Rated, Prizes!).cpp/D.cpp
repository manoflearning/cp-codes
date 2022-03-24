#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 5e6;

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
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    getPrime();

    int tc; cin >> tc;

    FOR(tc) {
        ll n; cin >> n;

        if (n & 1) {
            cout << 2 << '\n';
            continue;
        }

        // n is even

        if (n == 6) {
            cout << 3 << '\n';
            continue;
        }

        if (n < 10) {
            cout << -1 << '\n';
            continue;
        }

        // n is even && n >= 10

        if (n % 4 == 2) {
            cout << 4 << '\n';
            continue;
        }

        // n is multiple of 4 && n >= 10 

        ll ans = -1;

        for (ll i = 8; i * (i + 1) / 2 <= n; i <<= 1) {
            if ((n - i * (i + 1) / 2) % i == 0) {
                ans = i;
                break;
            }
        }

        if (ans != -1) {
            cout << ans << '\n';
            continue;
        }

        // answer must be prime number

        while (n % 2 == 0) n /= 2;

        EACH(p, prime) {
            if (n % p == 0) {
                ans = p;
                break;
            }
        }

        cout << ans << '\n';
    }

	return 0;
}