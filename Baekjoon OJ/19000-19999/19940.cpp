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

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int d[] = { 60, 10, -10, 1, -1 };

int n, dist[10101010];
int cnt[10101010][5];

void bfs() {
    memset(dist, -1, sizeof(dist));

    queue<int> q;
    q.push(0);
    dist[0] = 0;

    while (sz(q)) {
        int v = q.front();
        q.pop();

        for (int i = 4; i >= 0; i--) {
            int nxt = v + d[i];
            if (nxt < 0) nxt = 0;

            if (dist[nxt] != -1) continue;
            if (nxt >= 10101010) continue;

            dist[nxt] = dist[v] + 1;
            for (int j = 0; j < 5; j++) 
                cnt[nxt][j] = cnt[v][j];
            cnt[nxt][i]++;
            q.push(nxt);
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

    bfs();

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		cin >> n;

        for (int i = 0; i < 5; i++)
            cout << cnt[n][i] << ' ';
        cout << '\n';
	}

	return 0;
}