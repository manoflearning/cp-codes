#define _USE_MATH_DEFINES
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

ll n, m, k;
pii arr[1010];
vt<int> dir, adj[1010];
int dist[1010];
vt<int> path;

void input() {
    cin >> n >> m >> k;
    FOR(i, 1, n + 1) cin >> arr[i].fr >> arr[i].sc;
    FOR(m) {
        char c; cin >> c;
        if (c == 'L') dir.push_back(0);
        else dir.push_back(1);
    }
}

int cal(int st) {
    int now = st;
    FOR(m) {
        now = (dir[i] ? arr[now].sc : arr[now].fr);
    }
    return now;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    FOR(i, 1, n + 1) {
        adj[i].push_back(cal(i));
    }
    
    memset(dist, -1, sizeof(dist));

    int now = 1;
    dist[now] = 0;
    path.push_back(now);

    int l = -1, r = -1;
    while (1) {
        int next = adj[now][0];
        if (dist[next] != -1) {
            l = dist[next], r = dist[now];
            break;
        }

        dist[next] = dist[now] + 1;
        path.push_back(next);

        now = next;
    }

    if (k <= r) cout << path[k];
    else {
        k -= l;
        k %= (r - l + 1);
        k += l;
        cout << path[k];
    }

	return 0;
}