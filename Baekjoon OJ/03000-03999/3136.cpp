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
const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
    string s;
    vt<int> m;
    cin >> n >> s;
    EACH(i, s) m.push_back(i - '0');

    int y = 0, x = 0;
    vt<pii> vertex;
    vt<pair<pii, pii>> edge;
    vertex.push_back({ y, x });
    EACH(i, m) {
        int ny = y + dy[i], nx = x + dx[i];

        edge.push_back({ { y, x }, { ny, nx } });
        if (edge.back().fr > edge.back().sc) swap(edge.back().fr, edge.back().sc);
        vertex.push_back({ ny, nx });

        y = ny, x = nx;
        ny += dy[i], nx += dx[i];

        edge.push_back({ { y, x }, { ny, nx } });
        if (edge.back().fr > edge.back().sc) swap(edge.back().fr, edge.back().sc);
        vertex.push_back({ ny, nx });

        y = ny, x = nx;
    }

    sort(all(vertex));
    vertex.erase(unique(all(vertex)), vertex.end());
    sort(all(edge));
    edge.erase(unique(all(edge)), edge.end());

    cout << 1 - sz(vertex) + sz(edge);

	return 0;
}