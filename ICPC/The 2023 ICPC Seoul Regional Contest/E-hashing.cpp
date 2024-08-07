#pragma gcc optimize("O3")
#pragma gcc optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int MAXK = 10101;
const int MAXM = 1010;
const int MAXN = 1010101;
const int D = MAXK;
const int MOD = 1e9 + 9;

int K, M, N;
vector<int> a[MAXM];
vector<int> b;

unordered_map<int, int> mp;
ll expd[MAXN];

void preprocessing() {
    expd[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        expd[i] = D * expd[i - 1] % MOD;
    }
}

void input() {
    cin >> K >> M >> N;
    for (int i = 1; i <= M; i++) {
        a[i].resize(K);
        for (auto& j : a[i]) cin >> j;
    }
    b.resize(N);
    for (auto& i : b) cin >> i;
}

void valueCompression() {
    vector<int> c = b;
    c.push_back(-1);
    sort(all(c));
    for (auto& i : b) {
        i = lower_bound(all(c), i) - c.begin();
    }
}

void getHashedTickets() {
    for (int i = 1; i <= M; i++) {
        ll val = 0;
        for (int j = 0; j < K; j++) {
            val = (val + expd[K - j - 1] * a[i][j]) % MOD;
        }
        mp[val] = i;
    }
}

void isExist(ll val) {
    if (mp.count(val)) {
        for (auto& i : a[mp[val]])
            cout << i << ' ';
        exit(0);
    }
}

struct Fenwick {
	int flag, cnt;
	vector<int> arr, t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1, cnt++);
		arr.resize(flag);
		t.resize(flag);
	}
	void add(int p, int value) {
		arr[p] += value;
		while (p < flag) {
			t[p] += value;
			p |= p + 1;
		}
	}
	int query(int x) {
		int ret = 0;
		while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
		return ret;
	}
}fw;

int flag;
struct SegDigit {
    vector<ll> t;
    vector<pii> lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1, { 0, 0 });
    }
    void modify(int l, int r, pii val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] = val;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
    void propagate(int n) {
        if (lazy[n] == make_pair(0, 0)) return;
        // if (lazy[n].sc == 0 && t[n] == 0) return;
        if (n < flag) {
            if (lazy[n].sc == 0) {
                lazy[n << 1].fr += lazy[n].fr;
                lazy[n << 1 | 1].fr += lazy[n].fr;
            }
            else if (lazy[n].sc == 1) {
                lazy[n << 1].fr = lazy[n].fr;
                lazy[n << 1 | 1].fr = lazy[n].fr;
            }
            else if (lazy[n].sc == 2) {
                lazy[n << 1].fr = 0;
                lazy[n << 1 | 1].fr = 0;
            }
            lazy[n << 1].sc = lazy[n].sc;
            lazy[n << 1 | 1].sc = lazy[n].sc;
        }
        if (lazy[n].sc == 0) t[n] = t[n] % MOD * expd[lazy[n].fr] % MOD;
        else if (lazy[n].sc == 1) t[n] = expd[lazy[n].fr];
        else if (lazy[n].sc == 2) t[n] = 0;
        lazy[n] = { 0, 0 };
    }
}seg;

void solve() {
    fw.build(N + 1);
    seg.build(N);

    // [0, K - 1]
    for (int i = 0; i < K; i++) {
        fw.add(b[i], 1);
        seg.modify(b[i], b[i], { K - i - 1, 1 });
    }

    ll val = 0;
    for (int i = 0; i < K; i++) {
        int now = fw.query(b[i]);
        val = (val + expd[K - i - 1] * now) % MOD;
    }

    isExist(val);

    // [1, K], [2, K + 1], ..., [N - K, N - 1]
    for (int i = K; i < N; i++) {
        // modify b[i - K + 1], ..., b[i]
        val *= D;
        seg.modify(1, N, { 1, 0 });

        if (b[i - K] < b[i]) val -= seg.query(b[i - K] + 1, b[i] - 1);
        if (b[i - K] > b[i]) val += seg.query(b[i] + 1, b[i - K] - 1);

        // delete b[i - K]
        val -= expd[K] * fw.query(b[i - K]);
        fw.add(b[i - K], -1);
        seg.modify(b[i - K], b[i - K], { 0, 2 });

        // add b[i]
        fw.add(b[i], 1);
        seg.modify(b[i], b[i], { 0, 1 });
        val += fw.query(b[i]);

        // if there is winning ticket for [i - K + 1, i]
        val = (val % MOD + MOD) % MOD;
        isExist(val);
    }

    // if there is no winning ticket
    cout << 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    input();

    valueCompression();

    getHashedTickets();

    solve();
}