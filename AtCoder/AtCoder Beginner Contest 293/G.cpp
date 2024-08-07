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

int n, m, a[202020];
ll cnt[202020];

int sq = 734;

struct se {
	int s, e, idx;
	bool operator<(const se &rhs) const {
		if(s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
		else return (s / sq) & 1 ? e < rhs.e : e > rhs.e;
	}
};
vector<se> q;
vector<ll> ans;
ll res = 0;

void add(int idx) {
	// TODO: add value at idx from data structure
    int v = a[idx];
    res += cnt[v] * (cnt[v] - 1) / 2;
    cnt[v]++;
}
void del(int idx) {
	// TODO: remove value at idx from data structure
    int v = a[idx];
    cnt[v]--;
    res -= cnt[v] * (cnt[v] - 1) / 2;
}
ll query() {
	// TODO: extract the current answer of the data structure
    return res;
}

void f() {
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; i++) add(i);
	ans[q[0].idx] = query();
	for (int i = 1; i < q.size(); i++) {
		while (q[i].s < s) add(--s);
		while (e < q[i].e) add(++e);
		while (s < q[i].s) del(s++);
		while (q[i].e < e) del(e--);
		ans[q[i].idx] = query();
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
	for (int i = 1; i <= n; i++) cin >> a[i];
    q.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }

    sort(all(q));

    f();

    for (auto& i : ans)
        cout << i << '\n';

	return 0;
}