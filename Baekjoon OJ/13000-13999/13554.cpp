#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;
const int MAXM = 101010;
const int MAXK = 101010;
const int SQ = 373;

struct Fenwick { // 0-indexed
	int flag, cnt; // array size
	vector<ll> arr, t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1, cnt++);
		arr.resize(flag);
		t.resize(flag);
	}
	void add(int p, ll value) { // add value at position p
		arr[p] += value;
		while (p < flag) {
			t[p] += value;
			p |= p + 1;
		}
	}
	ll query(int x) {
		ll ret = 0;
		while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
		return ret;
	}
    ll query(int l, int r) {
        if (l > r) return 0;
		return query(r) - (l ? query(l - 1) : 0);
	}
}fwa, fwb;

int n, a[MAXN], b[MAXN];

int m;
struct Query {
    int s, e, k, idx;
    bool operator<(const Query& rhs) const {
        if (s / SQ != rhs.s / SQ) return s / SQ < rhs.s / SQ;
        else return (s / SQ) & 1 ? e < rhs.e : e > rhs.e;
    }
};
Query q[MAXM];
ll ans[MAXM];

ll cnta[MAXK], cntb[MAXK];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].s >> q[i].e >> q[i].k;
        q[i].idx = i;
    }
}

void add(int idx) {
    ll x = a[idx], y = b[idx];
    cnta[x]++, cntb[y]++;
    fwa.add(x, 1); fwb.add(y, 1);
}
void del(int idx) {
    ll x = a[idx], y = b[idx];
    cnta[x]--, cntb[y]--;
    fwa.add(x, -1); fwb.add(y, -1);
}

ll query(int k) {
    ll ret = 0;

    for (ll i = 1; i * i <= k; i++) {
        if (!cnta[i]) continue;
        ret += cnta[i] * fwb.query(i + 1, k / i);
    }
    for (ll i = 1; i * i <= k; i++) {
        if (!cntb[i]) continue;
        ret += cntb[i] * fwa.query(i, k / i);
    }

    return ret;
}

void mo() {
    fwa.build(MAXK);
    fwb.build(MAXK);

    int s = q[1].s, e = q[1].e;
    for (int i = s; i <= e; i++) add(i);
    ans[q[1].idx] += query(q[1].k);

    for (int i = 2; i <= m; i++) {
		while (q[i].s < s) add(--s);
		while (e < q[i].e) add(++e);
		while (s < q[i].s) del(s++);
		while (q[i].e < e) del(e--);
        ans[q[i].idx] += query(q[i].k);
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

    sort(q + 1, q + m + 1);

    mo();

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
}
