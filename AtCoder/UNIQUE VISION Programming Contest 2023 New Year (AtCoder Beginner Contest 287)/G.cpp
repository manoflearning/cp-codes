//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

vector<ll> c;

int flag;  // array size
struct Seg {
	struct Node {
		ll cnt, sum;
	};
    vector<Node> t;

    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll cnt) {
		t[p + flag - 1].cnt += cnt;
		t[p + flag - 1].sum += cnt * c[p];
		p += flag - 1;
        for (; p > 1; p >>= 1) {
			t[p >> 1].cnt = t[p].cnt + t[p ^ 1].cnt;
			t[p >> 1].sum = t[p].sum + t[p ^ 1].sum;
		}
		//cout << t[1].cnt << '\n';
    }
    ll kth(ll k, int n = 1) {
		if (t[n].cnt < k) return -1;
		
		if (k == t[n].cnt) return t[n].sum;
        if (flag <= n) return k * c[n - flag + 1];
		
        if (k <= t[n << 1 | 1].cnt) return kth(k, n << 1 | 1);
        else return t[n << 1 | 1].sum + kth(k - t[n << 1 | 1].cnt, n << 1);
    }
}seg;

int n;
ll score[202020], quota[202020];

struct Query {
	int op; ll x, y;
};
int m;
vector<Query> q;

int idx(ll x) {
	return lower_bound(all(c), x) - c.begin();
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	// input
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> score[i] >> quota[i];
	}
	cin >> m;
	q.resize(m);
	for (auto& i : q) {
		cin >> i.op >> i.x;
		if (i.op == 1 || i.op == 2) cin >> i.y;
	}

	// value compression
	c.push_back(-INF);
	for (int i = 1; i <= n; i++) {
		c.push_back(score[i]);
	}
	for (auto& i : q) {
		if (i.op == 1) c.push_back(i.y);
	}
	sort(all(c));
	c.erase(unique(all(c)), c.end());

	// solve
	seg.build(sz(c));
	for (int i = 1; i <= n; i++) {
		seg.add(idx(score[i]), quota[i]);
	}
	
	for (auto& i : q) {
		if (i.op == 1) {
			seg.add(idx(score[i.x]), -quota[i.x]);
			score[i.x] = i.y;
			seg.add(idx(score[i.x]), quota[i.x]);
		}
		if (i.op == 2) {
			seg.add(idx(score[i.x]), -quota[i.x]);
			quota[i.x] = i.y;
			seg.add(idx(score[i.x]), quota[i.x]);
		}
		if (i.op == 3) {
			cout << seg.kth(i.x) << '\n';
		}
	}

	return 0;
}