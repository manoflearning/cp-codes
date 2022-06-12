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

const int MAX = 1010;

int n, vi[MAX], cnt[MAX][MAX], qcnt = 0;;
char ans[MAX];
vector<int> p(MAX, -1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}

int query(int l, int r) {
    if (l > r) swap(l, r);
    if (cnt[l][r]) return cnt[l][r];
    qcnt++;
    cout << '?' << ' ' << 2 << ' ' << l << ' ' << r << '\n';
    fflush(stdout);
    int x; cin >> x;
    return cnt[l][r] = x;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin >> n;

    FOR(len, 2, n + 1)
    FOR(i, 1, n + 1) {
        int j = i + len - 1;
        if (j > n) continue;

        if (qcnt == 6000) break;
        if (find(i) == find(j)) break;
        int res = query(i, j);
        if (res == j - i) {
            FOR(k, j - 1, i - 1, -1) {
                if (qcnt == 6000) break;
                if (find(k) == find(j)) break;
                int res2 = query(k, j);
                if (res2 == j - k) { merge(k, j); break; }
            }            
        }
    }

    FOR(i, 1, n + 1) {
        if (!ans[find(i)]) {
            cout << '?' << ' ' << 1 << ' ' << i << '\n';
            fflush(stdout);
            char x; cin >> x;
            ans[find(i)] = x;
        }
    }

    cout << '!' << ' ';
    FOR(i, 1, n + 1) {
        cout << ans[find(i)];
    }

	return 0;
}