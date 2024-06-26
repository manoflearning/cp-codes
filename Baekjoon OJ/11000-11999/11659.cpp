#include <iostream>
using namespace std;

const int MAX = 100000;

int arr[MAX], psum[MAX + 1];

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];

		psum[i + 1] = psum[i] + arr[i];
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;

		cout << psum[b + 1] - psum[a] << '\n';
	}

	return 0;
}

//sqrt decomposition, mo's algorithm
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vs vector<string>
#define vvs vector<vector<string>>
#define fr first
#define sc second

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 1e5 + 5;

int r;

struct se {
	int s, e, idx;
	bool operator<(se b) {
		if (s / r != b.s / r) return s / r < b.s / r;
		return e < b.e;
	}
};

int n, m, a[MAX], ans[MAX];
se b[MAX];

void input() {
	cin >> n >> m;
	r = (int)sqrt(n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) {
		cin >> b[i].s >> b[i].e;
		b[i].idx = i;
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	sort(b + 1, b + m + 1);

	int sum = 0;
	for (int i = b[1].s; i <= b[1].e; i++) sum += a[i];
	ans[b[1].idx] = sum;

	for (int i = 2; i <= m; i++) {
		for (int j = b[i].s; j < b[i - 1].s; j++) sum += a[j];
		for (int j = b[i - 1].s; j < b[i].s; j++) sum -= a[j];
		for (int j = b[i - 1].e + 1; j <= b[i].e; j++) sum += a[j];
		for (int j = b[i].e + 1; j <= b[i - 1].e; j++) sum -= a[j];

		ans[b[i].idx] = sum;
	}

	for (int i = 1; i <= m; i++) cout << ans[i] << '\n';

	return 0;
}
