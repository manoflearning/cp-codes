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

vector<int> p(404040, -1);

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

struct Q {
    int op, a, b;
};

int n, m, isIn[202020];
deque<int> arr[202020], a(1, 0);
vt<Q> q;
ll psum[202020];

void input() {
    cin >> n;
    FOR(i, 1, n + 1) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int x; cin >> x;
            isIn[x] = i;
            arr[i].push_back(x);
            merge(x, 202020 + i);
        }
    }

    cin >> m;
    q.resize(m + 1);
    FOR(i, 1, m + 1) {
        cin >> q[i].op >> q[i].a >> q[i].b;
    }
}

void offlineQuery() {
    EACH(i, q) {
        if (i.op != 1) continue;
        
        int u = isIn[i.a], v = isIn[i.b];
        if (u != v) {
            if (sz(arr[u]) >= sz(arr[v])) {
                EACH(x, arr[v]) {
                    isIn[x] = u;
                    arr[u].push_back(x);
                }
                arr[v].clear();
            }
            else {
                for (int i = sz(arr[u]) - 1; i >= 0; i--) {
                    int x = arr[u][i];
                    isIn[x] = v;
                    arr[v].push_front(x);
                }
                arr[u].clear();
            }
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

	input();

    offlineQuery();

    FOR(i, 1, n + 1) {
        EACH(j, arr[i]) {
            isIn[j] = sz(a);
            a.push_back(j);
        }
    }

    FOR(i, 1, sz(a))
        psum[i] = a[i] + psum[i - 1];

    FOR(i, 1, m + 1) {
        int op = q[i].op, x = q[i].a, y = q[i].b;

        if (op == 1) {
            if (find(x) == find(y)) {
                cout << "NO\n";
            }
            else {
                cout << "YES\n";
                merge(x, y);
            }
        }
        else {
            if (find(x) == find(y)) {
                int u = isIn[x], v = isIn[y];
                if (u > v) swap(u, v);
                cout << psum[v] - psum[u - 1] << '\n';
            }
            else cout << -1 << '\n';
        }
    }

	return 0;
}