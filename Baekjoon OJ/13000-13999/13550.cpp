#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010, MAXM = 101010;
const int MAXK = 1010101;
const int SQ = 333;

int n, k;
ll a[MAXN], pa[MAXN];
struct Query {
    int s, e, idx;
    bool operator<(const Query& rhs) const {
		if(s / SQ != rhs.s / SQ) return s / SQ < rhs.s / SQ;
		else return (s / SQ) & 1 ? e < rhs.e : e > rhs.e;
	}
};
int m;
Query q[MAXM];
int ans[MAXM];
int cnt[MAXN], bucket[MAXN / SQ];

deque<int> dq[MAXN];

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pa[i] = (a[i] + pa[i - 1]) % k;
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].s--;
        q[i].idx = i;
    }
}

void value_comp() {
    vector<int> cc(1, -1e9);
    for (int i = 0; i <= n; i++)
        cc.push_back(pa[i]);
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 0; i <= n; i++)
        pa[i] = lower_bound(all(cc), pa[i]) - cc.begin();
}

void add(int idx) {
	int x = pa[idx];
    
    if (!dq[x].empty()) {
        cnt[dq[x].back() - dq[x].front()]--;
        bucket[(dq[x].back() - dq[x].front()) / SQ]--;
    }

    if (dq[x].empty() || dq[x].back() < idx) dq[x].push_back(idx);
    else dq[x].push_front(idx);

    cnt[dq[x].back() - dq[x].front()]++;
    bucket[(dq[x].back() - dq[x].front()) / SQ]++;
}
void del(int idx) {
    int x = pa[idx];
    
    cnt[dq[x].back() - dq[x].front()]--;
    bucket[(dq[x].back() - dq[x].front()) / SQ]--;

    if (dq[x].empty() || dq[x].back() == idx) dq[x].pop_back();
    else dq[x].pop_front();

    if (!dq[x].empty()) {
        cnt[dq[x].back() - dq[x].front()]++;
        bucket[(dq[x].back() - dq[x].front()) / SQ]++;
    }
}
int query() {
    for (int i = MAXN / SQ; i >= 0; i--) {
        if (!bucket[i]) continue;
        for (int j = SQ - 1; j >= 0; j--) {
            if (cnt[i * SQ + j]) return i * SQ + j;
        }
    }
    return 0;
}
void f() {
	int s = q[1].s, e = q[1].e;
	for (int i = s; i <= e; i++) add(i);
	ans[q[1].idx] = query();

	for (int i = 2; i <= m; i++) {
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

    input();

    value_comp();

    sort(q + 1, q + m + 1);

    f();

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
}
