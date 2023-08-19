// 아래 코드 중 Mo's Algorithm 관련부 출처
// https://github.com/manoflearning/cp-reference-codes/blob/master/reference-codes/8-misc/sqrt_decomposition_mos_algorithm.cpp

#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

const ll INF = 1e18;
const int MAXN = 101010;

// Seg 구조체 코드 출처
// : https://github.com/manoflearning/cp-reference-codes/blob/master/reference-codes/1-data-structure/segment-tree/segment_tree_iterative.cpp
struct Seg {  // 0-indexed
	int n;  // array size
	ll t[2 * MAXN];
	void build(int N) {
		n = N;
        for (int i = 0; i < 2 * n; i++) t[i] = INF;
	}
	void modify(int p, ll value) {  // set value at position p
        t[p + n] = min(t[p + n], value);
		for (p += n; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r) {  // sum on interval [l, r)
		ll ret = INF;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, t[l++]);
			if (r & 1) ret = min(ret, t[--r]);
		}
		return ret;
	}
}seg;

struct se {
	int s, e, idx;
	bool operator<(const se &rhs) const {
        return e < rhs.e;
		// if(s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
		// else return (s / sq) & 1 ? e < rhs.e : e > rhs.e;
	}
};
vector<se> q;
ll ans[MAXN];
int s, e;

int n, k;
ll x[MAXN], h[MAXN];

void init() {}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> x[i] >> h[i];
    cin >> k;
    q.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }
}

ll query() { return seg.query(s, e); }
inline ll cal(int l, int r) { return (x[r] - x[l]) * (h[r] + h[l]); }

int prve;
void f() {
    seg.build(n + 1);

	s = q[0].s, e = q[0].e;
    for (int i = 1; i <= e; i++) {
        for (int j = i + 1; j <= e; j++) {
            seg.modify(i, cal(i, j));
        }
        prve = e;
    }    
	ans[q[0].idx] = query();

	for (int i = 1; i < q.size(); i++) {
        s = q[i].s, e = q[i].e;
        if (prve < e) {
            for (int l = 1; l <= e; l++) {
                for (int r = max(l + 1, prve + 1); r <= e; r++) {
                    seg.modify(l, cal(l, r));
                }
            }
            prve = e;
        }
        
		ans[q[i].idx] = query();
	}
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        sort(q.begin(), q.end());
        f();

        for (int i = 0; i < k; i++) 
            cout << ans[i] << '\n';

        cout << flush;
    }
}