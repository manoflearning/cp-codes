//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 1010101;

vector<int> uf(MAX, -1);

int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	uf[A] += uf[B];
	uf[B] = A;
}

int n, m, k;
int viy[505][505], vix[505][505];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;

        if (sx == ex) for (int y = min(sy, ey); y < max(sy, ey); y++) vix[sx][y] = 1;
        if (sy == ey) for (int x = min(sx, ex); x < max(sx, ex); x++) viy[x][sy] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = i - 1, y = j;
            if (0 <= x && !vix[i][j]) {
                merge(505 * i + j, 505 * x + y);
            }
            x = i, y = j - 1;
            if (0 <= y && !viy[i][j]) {
                merge(505 * i + j, 505 * x + y);
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans.push_back(-uf[find(505 * i + j)]);
        }
    }

    sort(ans.begin(), ans.end());

    cout << ans.back() << '\n' << ans.front() << '\n';

	return 0;
}