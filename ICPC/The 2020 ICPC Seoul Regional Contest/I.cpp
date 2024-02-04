#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

const int MAXN = 2020;  // limit for array size

struct Seg {  // 0-indexed
	int n;  // array size
	ll t[2 * MAXN];

	void build(int N) {
		n = N;
		for (int i = 0; i < 2 * MAXN; i++) t[i] = -INF;
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r) {  // sum on interval [l, r]
        r++;
		ll ret = -INF;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, t[l++]);
			if (r & 1) ret = max(ret, t[--r]);
		}
		return ret;
	}
};

struct Seg2D {  // 0-indexed
	int n;  // array size
	Seg t[2 * MAXN];

	void build(int N) {
		n = N;
		for (int i = 0; i < 2 * n; i++) t[i].build(n);
	}
	void modify(int x, int y, ll value) {  // set value at position p
		x += n;
        t[x].modify(y, value);
		for (; x > 1; x >>= 1) {
            t[x >> 1].modify(y, max(t[x].query(y, y), t[x ^ 1].query(y, y)));
        }
	}
	ll query(int l, int r, int l2, int r2) {  // sum on interval [l, r]
        r++;
		ll ret = -INF;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, t[l++].query(l2, r2));
			if (r & 1) ret = max(ret, t[--r].query(l2, r2));
		}
		return ret;
	}
}seg;

struct Query {
    int s, e, idx; ll ub;
    bool operator<(const Query& rhs) const {
        return ub < rhs.ub;
    }
};

struct Node {
    ll w;
    int s, e;
    bool operator<(const Node& rhs) const {
        return w < rhs.w;
    }
};

int n, m;
ll a[2020], psum[2020];
vector<Node> sum;

vector<Query> q;
vector<ll> ans;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    for (int i = 1; i <= n; i++) {
        psum[i] = a[i] + psum[i - 1];
        for (int j = 1; j <= i; j++) {
            sum.push_back({ psum[i] - psum[j - 1], j, i });
        }
    }

    q.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e >> q[i].ub;
        q[i].idx = i;
    }

    sort(sum.begin(), sum.end());
    sort(q.begin(), q.end());

    int idx = 0;

    seg.build(n + 1);

    for (auto& i : q) {
        while (idx < sz(sum) && sum[idx].w <= i.ub) {
            seg.modify(sum[idx].s, sum[idx].e, sum[idx].w);
            idx++;
        }

        ans[i.idx] = seg.query(i.s, i.e, i.s, i.e);
    }

    for (int i = 0; i < m; i++) {
        if (ans[i] == -INF) cout << "NONE\n";
        else cout << ans[i] << '\n'; 
    }

	return 0;
}