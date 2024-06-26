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

int sq;

struct se {
	int s, e, idx;
	bool operator<(const se& a) const {
		if (s / sq != a.s / sq) return s / sq < a.s / sq;
		return e < a.e;
	}
};

int n, t;
ll cnt[1010101];
vt<ll> a;
vector<se> q;
vector<ll> ans;

void input() {
	// TODO: 1. receive input 2. resize q, ans 3. calculate sq 
    cin >> n >> t;
    a.resize(n + 1);
    FOR(n) cin >> a[i + 1];

    q.resize(t);
    ans.resize(t);
    sq = sqrt(1000000);

    FOR(t) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }
}

void add(int idx, ll& res) {
	res -= cnt[a[idx]] * cnt[a[idx]] * a[idx];
    cnt[a[idx]]++;
    res += cnt[a[idx]] * cnt[a[idx]] * a[idx];
}

void del(int idx, ll& res) {
	res -= cnt[a[idx]] * cnt[a[idx]] * a[idx];
    cnt[a[idx]]--;
    res += cnt[a[idx]] * cnt[a[idx]] * a[idx];
}

void f() {
	int s = q[0].s, e = q[0].e;
	// TODO: initialize data structure
    FOR(i, s, e + 1) cnt[a[i]]++;
    ll res = 0;
    FOR(i, 1, 1000001) {
        res += cnt[i] * cnt[i] * i;
    }
    ans[q[0].idx] = res;

	for (int i = 1; i < q.size(); i++) {
		while (q[i].s < s) add(--s, res);
		while (e < q[i].e) add(++e, res);
		while (s < q[i].s) del(s++, res);
		while (q[i].e < e) del(e--, res);
        ans[q[i].idx] = res;
	}
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
    
    sort(q.begin(), q.end());

    f();

    for (auto& i : ans)
		cout << i << '\n';

	return 0;
}