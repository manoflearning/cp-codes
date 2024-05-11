#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int N, M;
ll C, T[202020], P[202020];

int flag;  // array size
struct LR {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, -INF);
		// for (int i = flag; i < flag + n; i++) t[i] = -(N - (i - flag + 1)) * C;
		// for (int i = flag - 1; i >= 1; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
	}
	void modify(int p, ll value) {  // set value at position p
        t[p + flag - 1] = max(t[p + flag - 1], value - (N - p) * C);
		for (p += flag - 1; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return -INF;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}lr;
struct RL {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, -INF);
		// for (int i = flag; i < flag + n; i++) t[i] = -(i - flag) * C;
		// for (int i = flag - 1; i >= 1; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
	}
	void modify(int p, ll value) {  // set value at position p
        t[p + flag - 1] = max(t[p + flag - 1], value - (p - 1) * C);
		for (p += flag - 1; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return -INF;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}rl;

void input() {
    cin >> N >> C >> M;
    for (int i = 1; i <= M; i++) cin >> T[i] >> P[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    lr.build(N);
    rl.build(N);

    lr.modify(1, 0);
    rl.modify(1, 0);
    for (int i = 1; i <= M; i++) {
        ll res = -INF;
        res = max(res, lr.query(1, T[i]) + C * (N - T[i]) + P[i]);
        res = max(res, rl.query(T[i], N) + C * (T[i] - 1) + P[i]);
        lr.modify(T[i], res);
        rl.modify(T[i], res);
    }

    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ans = max(ans, lr.query(i, i) + C * (N - i));
        ans = max(ans, rl.query(i, i) + C * (i - 1));
    }
    cout << ans;
}