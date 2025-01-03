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
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 202020;
// Union find
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
// Kruskal's algorithm
struct wv {
	ll w; int v;
};
struct wuv {
	ll w; int u, v;
	bool operator<(const wuv& rhs) const {
		return w < rhs.w;
	}
};
ll n, m;
ll t, ans;
vector<wuv> a;
vector<wv> adj[MAX];
void input() {
	cin >> n >> m >> t;
	a.resize(m);
	for (auto& i : a) 
		cin >> i.u >> i.v >> i.w;
}
void makingMST() {
	sort(a.begin(), a.end());
	for (auto& i : a) {
		if (find(i.u) == find(i.v)) continue;
        ans += i.w;
		merge(i.u, i.v);
		adj[i.u].push_back({ i.w, i.v });
		adj[i.v].push_back({ i.w, i.u });
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

    makingMST();

    cout << ans + (n - 1) * (n - 2) / 2 * t;

	return 0;
}