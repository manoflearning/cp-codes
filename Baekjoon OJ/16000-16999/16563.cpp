#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 5000000;

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

// factorization in O(log x)
void factorization(int x) {
    while (x > 1) {
		cout << sp[x] << ' ';
		x /= sp[x];
	}
	cout << '\n';
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	linearSieve();

	int n; cin >> n;
	while (n--) {
		int x; cin >> x;
		factorization(x);
	}

	return 0;
}

// 정해
/*#define _USE_MATH_DEFINES
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
#define pb push_back
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

int mnFac[MAX + 1];
int n, a[(int)1e6 + 5];

void getPrime() {
	FOR(i, 2, MAX + 1) {
		if (i & 1) mnFac[i] = i;
		else mnFac[i] = 2;
	}

	for (ll i = 3; i <= MAX; i += 2) {
		if (mnFac[i] == i) {
			for (ll j = i * i; j <= MAX; j += 2 * i) 
				if (mnFac[j] == j) mnFac[j] = i;
		}
	}
}

void input() {
	cin >> n;
	FOR(n) cin >> a[i];
}

void f(int x) {
	while (x > 1) {
		cout << mnFac[x] << ' ';
		x /= mnFac[x];
	}
}

void solve() {
	getPrime();

	input();

	FOR(n) {
		f(a[i]);
		cout << '\n';
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}*/

// 내 풀이
/*#define _USE_MATH_DEFINES
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
#define pb push_back
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

const int MAX = 1e5;

bool isPrime[MAX + 1];
vt<int> prime(1, 2), p[MAX + 1];

int n, a[(int)1e6 + 5];

// time complexity : O(nlogn)
void getPrime() {
	fill(isPrime, isPrime + MAX + 1, 1);

	FOR(i, 2, MAX + 1, 2) p[i].pb(2);
	FOR(i, 4, MAX + 1, 2) isPrime[i] = 0;

	for (ll i = 3; i <= MAX; i++) {
		if (isPrime[i]) {
			prime.pb(i);
			p[i].pb(i);
		}
		for (ll j = 2 * i; j <= MAX; j += i) {
			isPrime[j] = 0;
			p[j].pb(i);
		}
	}
}

void input() {
	cin >> n;
	FOR(n) cin >> a[i];
}

void f(int x) {
	vt<int> ans;

	EACH(i, prime) {
		if (x <= MAX) break;
		if (x < (ll)i * i) break;
		while (x % i == 0) {
			ans.pb(i);
			x /= i;
		}
	}

	if (x <= MAX) {
		EACH(i, p[x]) {
			while (x % i == 0) {
				ans.pb(i);
				x /= i;
			}
		}
	}
	else ans.pb(x);

	sort(all(ans));

	EACH(i, ans) cout << i << ' ';
}

void solve() {
	getPrime();

	input();

	FOR(n) {
		f(a[i]);
		cout << '\n';
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	solve();

	return 0;
}*/