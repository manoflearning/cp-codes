// BOJ 13537 AC Code
// https://www.acmicpc.net/problem/13537
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int MAX = 1 << 17;

struct MergeSortTree {
    vector<int> tree[MAX << 1];

    void build(const vector<int>& arr) {
        for (int i = 0; i < sz(arr); i++) 
            tree[i + 1 + MAX].push_back(arr[i]);

        for (int i = MAX - 1; i >= 1; i--) {
            tree[i].resize(sz(tree[i << 1]) + sz(tree[i << 1 | 1]));
            merge(all(tree[i << 1]), all(tree[i << 1 | 1]), tree[i].begin());
        }
    }

    int query(int l, int r, int k, int n = 1, int nl = 0, int nr = MAX - 1) { // 0-indexed, query on interval [l, r]
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r)
            return tree[n].end() - upper_bound(all(tree[n]), k);

        int mid = (nl + nr) >> 1;
        return query(l, r, k, n << 1, nl, mid) + query(l, r, k, n << 1 | 1, mid + 1, nr);
    }
}mstree;

int n;
vector<int> arr;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    arr.resize(n);
    for (auto& i : arr) cin >> i;

    mstree.build(arr);

    int q; cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;

        int ans = mstree.query(a, b, c);
        cout << ans << '\n';
    }
    
    return 0;
}

/*#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int MAX = 1 << 17;

struct MergeSortTree {
    vector<int> tree[1 << 18];

    void add(int idx, int val) {
        tree[idx + MAX].push_back(val);
    }

    void build(const vector<int>& arr) {
        for (int i = 0; i < sz(arr); i++) add(i + 1, arr[i]);

        for (int i = MAX - 1; i >= 1; i--) {
            tree[i].resize(sz(tree[i << 1]) + sz(tree[i << 1 | 1]));
            merge(all(tree[i << 1]), all(tree[i << 1 | 1]), tree[i].begin());
        }
    }

    int query(int l, int r, int k) {
        l += MAX, r += MAX;
        int ret = 0;
        while (l <= r) {
            if (l & 1) ret += tree[l].end() - upper_bound(all(tree[l]), k), l++;
            if (~r & 1) ret += tree[r].end() - upper_bound(all(tree[r]), k), r--;
            l >>= 1, r >>= 1;
        }
        return ret;
    }
}mstree;

int n;
vector<int> arr;

int main() {
    #ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    arr.resize(n);
    for (auto& i : arr) cin >> i;

    mstree.build(arr);

    int q; cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;

        int ans = mstree.query(a, b, c);
        cout << ans << '\n';
    }
    
    return 0;
}*/

/*#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define pii pair<int, int>

const int MAX = 1e5;

struct Seg {
	int N, t[2 * MAX];

	void modify(int p) {
		for (t[p += N] = 1; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	int query(int l, int r) {
		int ret = 0;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;

struct ijk {
	int i, j, k, idx;
};

priority_queue<pii> pq;
int M;
ijk Q[MAX + 5];
int ans[MAX + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> seg.N;
	for (int i = 0; i < seg.N; i++) {
		int A; cin >> A;
		pq.push({ A, i });
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> Q[i].i >> Q[i].j >> Q[i].k;
		Q[i].idx = i;
	}

	sort(Q, Q + M, [](ijk& a, ijk& b) {
		return a.k > b.k;
		});

	for (int i = 0; i < M; i++) {
		while (!pq.empty() && pq.top().first > Q[i].k) {
			seg.modify(pq.top().second);
			pq.pop();
		}
		ans[Q[i].idx] = seg.query(Q[i].i - 1, Q[i].j);
	}
	
	for (int i = 0; i < M; i++) cout << ans[i] << '\n';

	return 0;
}*/