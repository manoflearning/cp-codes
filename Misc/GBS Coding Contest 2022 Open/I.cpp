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

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m, k;
int d[1010][1010], w[1010][1010], vi[1010][1010], ind[1010][1010];
int cnt, bit;

vector<int> a, b;

void dfs(int y, int x) {
    cnt++;
    vi[y][x] = 1;

    int ny = y + w[y][x] * dy[d[y][x]], nx = x + w[y][x] * dx[d[y][x]];
    if (ny < 1 || n < ny || nx < 1 || m < nx) {
        bit = 1;
        return;
    }

    if (!vi[ny][nx]) dfs(ny, nx);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            if (c == 'R') d[i][j] = 0;
            if (c == 'L') d[i][j] = 1;
            if (c == 'D') d[i][j] = 2;
            if (c == 'U') d[i][j] = 3;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> w[i][j];

            int ny = i + w[i][j] * dy[d[i][j]];
            int nx = i + w[i][j] * dx[d[i][j]];
            
            if (1 <= ny && ny <= n && 1 <= nx && nx <= m) ind[ny][nx]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ind[i][j] || vi[i][j]) continue;

            cnt = bit = 0;
            dfs(i, j);
            
            if (!bit) a.push_back(cnt);
            else b.push_back(cnt);
        }
    }

    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    int aa = 0, bb = 0;
    int asum = 0, bsum = 0;
    for (int i = 0; i < sz(a); i++) {
        cout << a[i] << '\n';
        asum += a[i];
        if (i < k) aa += a[i];
    }
    for (int i = 0; i < sz(b); i++) {
        cout << b[i] << '\n';
        bsum += b[i];
        if (i < k) bb += b[i];
    }

    cout << bsum - bb << ' ' << bsum + aa;

	return 0;
}