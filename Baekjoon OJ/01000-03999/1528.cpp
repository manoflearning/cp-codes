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

int n, dist[1010101], prv[1010101];
vt<int> a;

void gms(int val) {
    if (val > n) return;

    if (val != 0) a.push_back(val);

    gms(10 * val + 4);
    gms(10 * val + 7);
}

int bfs() {
    memset(dist, -1, sizeof(dist));

    queue<int> q;

    q.push(0);
    dist[0] = 0;
    prv[0] = -1;

    while (sz(q)) {
        int v = q.front();
        q.pop();

        if (v == n) return dist[v];

        EACH(i, a) {
            if (v + i <= n && dist[v + i] == -1) {
                dist[v + i] = dist[v] + 1;
                prv[v + i] = v;
                q.push(v + i);
            }
        }
    }

    return -1;
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
	
	cin >> n;

    gms(0);

    sort(all(a));

    if (bfs() == -1) {
        cout << -1;
        return 0;
    }

    vt<int> ans;
    for (int i = n; i != 0; i = prv[i])
        ans.push_back(i - prv[i]);

    for (int i = sz(ans) - 1; i >= 0; i--) 
        cout << ans[i] << ' ';

	return 0;
}