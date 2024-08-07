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

const int MAX = 1010101;

vector<int> p(MAX, -1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	//p[A] += p[B];
	p[B] = A;
}

int n, m, deg[55], cnt;
vt<string> a;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    a.resize(n);
    EACH(i, a) cin >> i;

    set<pii> s2;

    FOR(i, n) FOR(j, i + 1, n) {
        if (a[i][j] == 'Y') {
            if (find(i) != find(j)) {
                cnt++;
                merge(i, j);
                deg[i]++, deg[j]++;
                s2.insert({ i, j });
            }
        }
    }

    FOR(i, n) FOR(j, i + 1, n) {
        if (cnt == m) break;
        if (a[i][j] == 'Y') {
            if (s2.find({ i, j }) != s2.end()) continue;
            
            cnt++;
            merge(i, j);
            deg[i]++, deg[j]++;
        }
    }

    set<int> s;
    FOR(i, n) {
        s.insert(find(i));
    }

    if (sz(s) != 1 || cnt != m) {
        cout << -1;
    }
    else {
        FOR(i, n) cout << deg[i] << ' ';
    }

	return 0;
}