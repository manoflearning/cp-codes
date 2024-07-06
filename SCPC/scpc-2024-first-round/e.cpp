// refers to the following public source code:
// https://github.com/manoflearning/cp-reference-codes/blob/master/reference-codes/8-misc/sqrt_decomposition_mos_algorithm.cpp

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int N = 50505;
const int R = 293;

int n;
int a[N];

struct Query {
    int s, e, idx;
    bool operator<(const Query& rhs) const {
        if (s / R != rhs.s / R) return s / R < rhs.s / R;
        else return (s / R) & 1 ? e < rhs.e : e > rhs.e;
    }
};
int q;
vector<Query> qu;
int ans[N], cnt[N];

int nos;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (n < a[i]) a[i] = 1;
    }

    cin >> q;
    qu.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> qu[i].s >> qu[i].e;
        qu[i].idx = i;
    }
}

// ll cal_cnt = 0;
void add(int x) {
    // cal_cnt++;
    if (x == 1) return;
    cnt[x]++;
    if (cnt[x] % x == 0) {
        nos++;
        if (x * x <= n) add(x * x);
    }
}
void del(int x) {
    // cal_cnt++;
    if (x == 1) return;
	cnt[x]--;
    if (cnt[x] % x == x - 1) {
        nos--;
        if (x * x <= n) del(x * x);
    }
}
void f() {
    // initialize
    nos = 0;
    for (int i = 2; i <= n; i++) cnt[i] = 0;

    // solve
	int s = qu[0].s, e = qu[0].e;
	for (int i = s; i <= e; i++) add(a[i]);
	ans[qu[0].idx] = nos;
	for (int i = 1; i < sz(qu); i++) {
		while (qu[i].s < s) add(a[--s]);
		while (e < qu[i].e) add(a[++e]);
		while (s < qu[i].s) del(a[s++]);
		while (qu[i].e < e) del(a[e--]);
		ans[qu[i].idx] = nos;
	}
}

int main() {
    // freopen("e-worst-case.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // auto st_t = clock();

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        input();

        sort(all(qu));

        f();

        for (int i = 0; i < q; i++)
            cout << ans[i] << '\n';

        cout << flush;
    }

    // auto en_t = clock();

    // cout << "total update count: " << cal_cnt << '\n';
    // cout << "total time: " << (en_t - st_t) / CLOCKS_PER_SEC << "s" << '\n';
}