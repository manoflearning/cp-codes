#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

struct point {
	int x, y;
	point() : point(x, y) {}
	point(int sx, int sy) : x(sx), y(sy) {}
	bool operator <(point& O) {
		if (x != O.x) return x < O.x;
		return y > O.y;
	}
};

vector<point> p;
int flag;
vector<ll> sgtr, lazy;

void init();
bool cmp(point& a, point& b);
ll sum(int L, int R, int n, int nL, int nR);
void update(int L, int R, int n, int nL, int nR, int v);
void propagate(int n, int nL, int nR);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		init();

		int N; cin >> N;

		for (int i = 0; i < N; i++) {
			int x, y;
			cin >> x >> y;
			p.push_back(point(x, y));
		}

		sort(p.begin(), p.end(), cmp);

		int h = 1;
		for (int i = 0; i < p.size(); i++) {
			if (i + 1 != p.size() && p[i].y == p[i + 1].y) p[i].y = h;
			else p[i].y = h++;
		}
		
		for (flag = 1; flag < h; flag *= 2);
		sgtr.resize(2 * flag);
		lazy.resize(2 * flag);

		sort(p.begin(), p.end());

		ll ans = 0;
		for (int i = 0; i < p.size(); i++) {
			ans += sum(p[i].y, h, 1, 1, flag);
			update(p[i].y, p[i].y, 1, 1, flag, 1);
		}

		cout << ans << '\n';
	}

	return 0;
}

void init() {
	p.clear();
	sgtr.clear();
	lazy.clear();
}

bool cmp(point& a, point& b) {
	return a.y < b.y;
}

ll sum(int L, int R, int n, int nL, int nR) {
	propagate(n, nL, nR);

	if (R < nL || nR < L) return 0;
	if (L <= nL && nR <= R) return sgtr[n];

	int mid = (nL + nR) / 2;
	return sum(L, R, 2 * n, nL, mid) + sum(L, R, 2 * n + 1, mid + 1, nR);
}

void update(int L, int R, int n, int nL, int nR, int v) {
	propagate(n, nL, nR);

	if (R < nL || nR < L) return;
	if (L <= nL && nR <= R) {
		lazy[n] = v;
		propagate(n, nL, nR);
		return;
	}

	int mid = (nL + nR) / 2;
	update(L, R, 2 * n, nL, mid, v);
	update(L, R, 2 * n + 1, mid + 1, nR, v);

	sgtr[n] = sgtr[2 * n] + sgtr[2 * n + 1];
}

void propagate(int n, int nL, int nR) {
	if (lazy[n] != 0) {
		if (n < flag) {
			lazy[2 * n] += lazy[n];
			lazy[2 * n + 1] += lazy[n];
		}
		sgtr[n] += lazy[n] * (nR - nL + 1);
		lazy[n] = 0;
	}
}