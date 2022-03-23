// stack
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

struct hidx {
	ll h, idx;
};

int n;
vt<ll> h;

void init() {
	h.clear();
}

void input() {
	h.resize(n);
	FOR(n) cin >> h[i];
}

ll f() {
	ll ret = 0;
	stack<hidx> stk;

	stk.push({ -1, -1 });
	FOR(i, 0, n) {
		while (stk.top().h > h[i]) {
			ll mnh = stk.top().h;
			stk.pop();

			ret = max(ret, mnh * (i - stk.top().idx - 1));
		}
		
		stk.push({ h[i], i });
	}

	while (stk.top().h > -1) {
		ll mnh = stk.top().h;
		stk.pop();

		ret = max(ret, mnh * (n - stk.top().idx - 1));
	}
	
	return ret;
}

/*ll f2() {
	ll ret = 0;
	stack<hidx> stk;

	FOR(i, n - 1, -1, -1) {
		while (sz(stk) && stk.top().h >= h[i]) stk.pop();

		if (sz(stk)) ret = max(ret, h[i] * (stk.top().idx - i));
		else ret = max(ret, h[i] * (n - i));

		stk.push({ h[i], i });
	}

	return ret;
}*/

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (1) {
		init();

		cin >> n;
		if (!n) break;

		input();

		cout << f() << '\n';
		//cout << max(f(), f2()) << '\n';		
	}

	return 0;
}

// divide and conquer
/*#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int histo[MAX];

long long find_max(int left, int right);

int main() {
	while (true) {
		int n;
		scanf("%d", &n);

		if (n == 0) break;

		for (int i = 0; i < n; i++)
			scanf("%lld", &histo[i]);

		printf("%lld\n", find_max(0, n - 1));
	}

	return 0;
}

long long find_max(int left, int right) {
	//base case
	if (left == right) return histo[left];
	
	int flag = (left + right) / 2;

	int r_left = flag, r_right = flag + 1;
	long long height = min(histo[r_left], histo[r_right]);
	
	long long ret = height * (r_right - r_left + 1);
	
	while (left < r_left || r_right < right) {
		if (r_right < right && (r_left == left || histo[r_left - 1] <= histo[r_right + 1])) {
			r_right++;
			height = min(height, (long long)histo[r_right]);
		}
		else {
			r_left--;
			height = min(height, (long long)histo[r_left]);
		}
		
		ret = max(ret, height * (r_right - r_left + 1));
	}
	
	ret = max(ret, find_max(left, flag));
	ret = max(ret, find_max(flag + 1, right));

	return ret;
}*/