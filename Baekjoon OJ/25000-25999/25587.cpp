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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };


const int MAX = 1010101;

int n;
vector<int> uf(MAX, -1), AA(MAX), BB(MAX);

int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	uf[A] += uf[B];
    AA[A] += AA[B];
    BB[A] += BB[B];
	uf[B] = A;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    
    for (int i = 1; i <= n; i++) {
        AA[i] = a[i];
        BB[i] = b[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] < b[i]) ans++;

    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, v;
            cin >> u >> v;

            if (find(u) == find(v)) continue;

            int U = find(u), V = find(v);

            ans -= AA[U] < BB[U] ? -uf[U] : 0;
            ans -= AA[V] < BB[V] ? -uf[V] : 0;

            merge(u, v);

            int R = find(u);
            ans += AA[R] < BB[R] ? -uf[R] : 0;
        }
        else cout << ans << '\n';
    }

	return 0;
}