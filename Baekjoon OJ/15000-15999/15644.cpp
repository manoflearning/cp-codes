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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };
const char dr[] = { 'R', 'L', 'D', 'U' };

int n, m;
vector<string> a;
string res, ans;

void bt(int cnt, int prv, vector<string> arr) {
    if (cnt >= 10) return;

    for (int d = 0; d < 4; d++) {
        if (d == prv) continue;

        vector<string> nxt = arr;
        int ry = -1, rx = -1, by = -1, bx = -1;
        for (int y = 1; y <= n; y++) {
            for (int x = 1; x <= m; x++) {
                if (arr[y][x] == 'R') ry = y, rx = x;
                if (arr[y][x] == 'B') by = y, bx = x;
            }
        }

        int ro = 0, bo = 0;
        for (int i = 0; i < 20; i++) {
            int nry = ry + dy[d], nrx = rx + dx[d];
            int nby = by + dy[d], nbx = bx + dx[d];

            if (1 <= nry && nry <= n && 1 <= nrx && nrx <= m && nxt[nry][nrx] == '.') {
                swap(nxt[nry][nrx], nxt[ry][rx]);
                ry = nry, rx = nrx;
            }
            else if (1 <= nry && nry <= n && 1 <= nrx && nrx <= m && nxt[nry][nrx] == 'O') {
                nxt[ry][rx] = '.';
                ro = 1;
                ry = INF, rx = INF;
            }
            else if (1 <= nby && nby <= n && 1 <= nbx && nbx <= m && nxt[nby][nbx] == '.') {
                swap(nxt[nby][nbx], nxt[by][bx]);
                by = nby, bx = nbx;
            }
            else if (1 <= nby && nby <= n && 1 <= nbx && nbx <= m && nxt[nby][nbx] == 'O') {
                nxt[by][bx] = '.';
                bo = 1;
                by = INF, bx = INF;
            }
        }

        if (ro && bo) continue;
        else if (ro) {
            res.push_back(dr[d]);
            if (ans.empty() || sz(ans) > sz(res)) ans = res;
            res.pop_back();
            continue;
        }
        else if (bo) continue;
        else {
            res.push_back(dr[d]);
            bt(cnt + 1, d, nxt);
            res.pop_back();
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

	cin >> n >> m;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].resize(1);
        string s; cin >> s;
        for (auto& c : s)
            a[i].push_back(c);
    }

    bt(0, 4, a);
    
    if (ans.empty()) cout << -1;
    else {
        cout << sz(ans) << '\n';
        cout << ans;
    }

	return 0;
}