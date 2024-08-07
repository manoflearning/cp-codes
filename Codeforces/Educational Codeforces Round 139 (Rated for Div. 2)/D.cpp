#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
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

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 1e7;
vector<int> sp(MAXN + 1);
vector<ll> prime;
// Determine prime numbers between 1 and MAXN in O(MAXN) 
void linearSieve() {
	for (int i = 2;i <= MAXN; i++) {
		if (!sp[i]) {
			prime.push_back(i);
			sp[i] = i;
		}
		for (auto j : prime) {
			if (i * j > MAXN) break;
			sp[i * j] = j;
			if (i % j == 0) break;
		}
	}
}

vector<int> arr;
// factorization in O(log x)
void factorization(int x) {
	while (x > 1) {
		arr.push_back(sp[x]);
		x /= sp[x];
	}
}

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

ll a, b;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    linearSieve();

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		cin >> a >> b;

        if (gcd(a, b) != 1) {
            cout << 0 << '\n';
            continue;
        }

        ll diff = abs(a - b);

        if (diff == 1) {
            cout << -1 << '\n';
            continue;
        }

        arr.clear();
        factorization(diff);

        ll ans = INF;
        for (auto& i : arr) {
            ans = min(ans, i - a % i);
        }

        cout << ans << '\n';
	}

	return 0;
}