#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag, INF);
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] = value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != INF) {
			if (n < flag) {
				lazy[n << 1] = lazy[n];
				lazy[n << 1 | 1] = lazy[n];
			}
			t[n] = lazy[n] * (nr - nl + 1);
			lazy[n] = INF;
		}
	}
}seg;

int n, m, k;
struct Query {
    int l, r, w;
};
vector<Query> arr[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int y, x, r;
        cin >> y >> x >> r;
        for (ll j = x - r; j <= x + r; j++) {
            int d = sqrt(r * r - (j - x) * (j - x));
            arr[j].push_back({ y - d, y + d, k - i });
        }
    }

    ll ans = 0;

    seg.build(n);
    for (int x = 1; x <= m; x++) {
        seg.modify(1, n, k);

        sort(all(arr[x]), [&](const Query& p1, const Query& p2) {
            return p1.w > p2.w;
        });

        for (auto& i : arr[x]) {
            seg.modify(i.l, i.r, i.w);
        }

        ans += seg.query(1, n);
    }

    cout << ans;
}
