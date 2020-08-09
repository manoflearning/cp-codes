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

struct point {
	ll y, x;
};

int N;
vector<point> p;
int bit;
double res;

void cal() {
	ll ay = 0, ax = 0, by = 0, bx = 0;
	for (int i = 0; i < N; i++) {
		if (bit & (1 << i)) ay += p[i].y, ax += p[i].x;
		else by += p[i].y, bx += p[i].x;
	}
	ll cy = fabs(ay - by), cx = fabs(ax - bx);
	res = min(res, sqrt(cy * cy + cx * cx));
}

void f(int idx, int cnt) {
	if (cnt == N / 2) {
		cal();
		return;
	}

	for (int i = idx; i < N; i++) {
		bit |= (1 << i);
		f(i + 1, cnt + 1);
		bit ^= (1 << i);
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed; cout.precision(6);

	int tc; cin >> tc;
	while (tc--) {
		res = INF;

		cin >> N;
		p.resize(N);
		for (auto& i : p) cin >> i.y >> i.x;

		f(0, 0);

		cout << res << '\n';
	}

	return 0;
}