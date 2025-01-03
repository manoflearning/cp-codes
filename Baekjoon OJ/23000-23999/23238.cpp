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

const int sq = 400;

struct se {
	int s, e, idx;
	bool operator<(const se& rhs) const {
		if (s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
		return e < rhs.e;
	}
};

int n, m, cnt[101010], bu[1010], ub;
vector<int> a, ans;
vector<se> q;

void input() {
    cin >> n >> m;
    a.resize(n + 1);
    FOR(n) cin >> a[i + 1];
    q.resize(m);
    ans.resize(m);
    FOR(m) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }
}

void buildBucket() {
    ub = (n + sq - 1) / sq;
    for (int i = 0; i <= ub; i++) {
        int mx = 0, res = -1;
        for (int j = i * sq + 1; j <= min(n, (i + 1) * sq); j++) {
            cnt[a[j]]++;
            if (cnt[a[j]] > mx) {
                mx = cnt[a[j]];
                res = a[j];
            }
        }

        bu[i] = res;

        for (int j = i * sq + 1; j <= min(n, (i + 1) * sq); j++) {
            cnt[a[j]] = 0;
        }
    }
}

void add(int idx) {
    cnt[a[idx]]++;
}

void del(int idx) {
	cnt[a[idx]]--;
}

int query(int s, int e) {
    int ret = 0, mx = 0;

    int l = s / sq * sq + 1, r = e / sq * sq;
    if (l < s) l += sq;

	for (int i = s; i < l; i++) {
        if (mx < cnt[a[i]]) {
            mx = cnt[a[i]];
            ret = a[i];
        }
    }
    for (int i = r + 1; i <= e; i++) {
        if (mx < bu[a[i]]) {
            mx = bu[a[i]];
            ret = a[i];
        }
    }

    for (int i = l / sq; i < r / sq; i++) {
        if 
    }
}

void f() {
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; i++) {
        cnt[a[i]]++;
    }
	ans[q[0].idx] = query(s, e);

	for (int i = 1; i < q.size(); i++) {
		while (q[i].s < s) add(--s);
		while (e < q[i].e) add(++e);
		while (s < q[i].s) del(s++);
		while (q[i].e < e) del(e--);
		ans[q[i].idx] = query(s, e);
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

    buildBucket();

	sort(q.begin(), q.end());

	f();

	for (auto& i : ans) 
		cout << i << '\n';

	return 0;
}