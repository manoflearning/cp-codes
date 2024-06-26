#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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
const int dx[] = { 1, -1, 0, 0, 0, 0 };
const int dy[] = { 0, 0, 1, -1, 0, 0 };
const int dz[] = { 0, 0, 0, 0, 1, -1 };

const int n = 5;
vector<vector<int>> a[4][6];
vector<vector<vector<int>>> b(6);
int ans = INF;

void bfs() {
    if (b[1][1][1] == 0) return;

    struct Node { int x, y, z; };
    queue<Node> q;
    vector<vector<vector<int>>> dist(6, vector<vector<int>>(6, vector<int>(6, -1)));
    
    dist[1][1][1] = 0;
    q.push({ 1, 1, 1 });

    while (sz(q)) {
        auto [x, y, z] = q.front();
        q.pop();

        for (int i = 0; i < 6; i++) {
            int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
            if (nx < 1 || n < nx) continue;
            if (ny < 1 || n < ny) continue;
            if (nz < 1 || n < nz) continue;
            if (!b[nx][ny][nz]) continue;
            if (dist[nx][ny][nz] != -1) continue;
            dist[nx][ny][nz] = dist[x][y][z] + 1;
            q.push({ nx, ny, nz });
        }
    }

    if (dist[5][5][5] == -1) return;
    ans = min(ans, dist[5][5][5]);
}

void turn(vector<vector<int>>& arr, vector<vector<int>>& tmp) {
    tmp = arr;
    for (int x = 1; x <= 5; x++) {
        for (int y = 1; y <= 5; y++) {
            int nx = 3 - (3 - y), ny = 3 + (3 - x);
            tmp[nx][ny] = arr[x][y];
        }
    }
}

vector<int> res(1, 0);
int vi[6];
vector<int> res2(1, 0);

void bt(int v) {
    if (v == 6) {
        for (int i = 1; i <= n; i++) {
            b[i] = a[res[i]][res2[i]];
        }
        bfs(); return;
    }

    res.push_back(0);
    bt(v + 1);
    res.pop_back();

    res.push_back(1);
    bt(v + 1);
    res.pop_back();
    
    res.push_back(2);
    bt(v + 1);
    res.pop_back();

    res.push_back(3);
    bt(v + 1);
    res.pop_back();
}

void bt2(int v) {
    if (v == 6) {
        bt(1); return;
    }

    for (int i = 1; i <= n; i++) {
        if (!vi[i]) {
            vi[i] = 1;
            res2.push_back(i);
            bt2(v + 1);
            vi[i] = 0;
            res2.pop_back();
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
	for (int i = 1; i <= n; i++) {
        a[0][i].resize(6, vector<int>(6));
        a[1][i].resize(6, vector<int>(6));
        a[2][i].resize(6, vector<int>(6));
        a[3][i].resize(6, vector<int>(6));
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                cin >> a[0][i][j][k];
            }
        }
        turn(a[0][i], a[1][i]);
        turn(a[1][i], a[2][i]);
        turn(a[2][i], a[3][i]);
    }

    bt2(1);

    cout << (ans == INF ? -1 : ans);

	return 0;
}