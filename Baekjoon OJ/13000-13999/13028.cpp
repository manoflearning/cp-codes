#include <bits/stdc++.h>
using namespace std;

const int SQ = 373;
struct Query {
	int s, e, idx;
	bool operator<(const Query& rhs) const {
		if (s / SQ != rhs.s / SQ) return s / SQ < rhs.s / SQ;
		return e < rhs.e;
	}
};

int n, m;
int a[101010], cnt[101010], res;
vector<Query> q;
vector<int> ans;

void add(int idx) {
	cnt[a[idx]]++;
    if (cnt[a[idx]] == 3) res++;
}
void del(int idx) {
	if (cnt[a[idx]] == 3) res--;
    cnt[a[idx]]--;
}
int query() { return res; }
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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

    sort(q.begin(), q.end());

	f();
	for (auto& i : ans) 
		cout << i << '\n';
}
