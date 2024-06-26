#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int d = 1, m;

ll GCD(ll a, ll b) {
	if (b == 0) return a;
	else return GCD(b, a % b);
}

ll LCM(ll a, ll b) {
	return a * b / GCD(a, b);
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int a, b;
	cin >> a >> b;
	
	for (int i = 0; i < a; i++) {
		int x; cin >> x;
		if (i == 0) d = x;
		else d = LCM(d, x);
	}
	for(int i = 0; i < b; i++) {
		int x; cin >> x;
		if (i == 0) m = x;
		else m = GCD(m, x);
	}

	if (m % d) {
		cout << 0;
		return 0;
	}
	
	int c = m / d, ans = 0;

	//약수 구하기
	for (int i = 1; i * i <= c; i++) {
		if (c % i == 0) {
			if (i * i < c) ans += 2;
			else ans++;
		}
	}

	cout << ans;

	return 0;
}
