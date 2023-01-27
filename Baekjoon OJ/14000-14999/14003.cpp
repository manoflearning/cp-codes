#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int MAXN = 1010101;  // limit for array size

struct Seg {  // 0-indexed
	int n;  // array size
	pair<int, int> t[2 * MAXN];
	void build(int N) {
		n = N;
		//for (int i = 0; i < n; i++) cin >> t[n + i];
		//for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, pair<int, int> value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) 
            t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	pair<int, int> query(int l, int r) {  // sum on interval [l, r)
		pair<int, int> ret = { 0, INF };
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, t[l++]);
			if (r & 1) ret = max(ret, t[--r]);
		}
		return ret;
	}
}seg;

int n;
pair<int, int> dp[1010101];
vector<int> a, c;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    // input
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    // value compression
    for (auto& i : a)
        c.push_back(i);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    for (auto& i : a)
        i = lower_bound(c.begin(), c.end(), i) - c.begin(); 

    // solve
    seg.build(c.size() + 10);
    for (int i = 0; i < n; i++) {
        dp[i] = seg.query(0, a[i]);
        dp[i].first++;
        seg.modify(a[i], { dp[i].first, i });
    }

    int mxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (dp[mxIdx] < dp[i]) mxIdx = i;
    }

    cout << dp[mxIdx].first << '\n';
    stack<int> stk;
    while (mxIdx != INF) {
        stk.push(mxIdx);
        mxIdx = dp[mxIdx].second;
    }
    while (!stk.empty()) {
        cout << c[a[stk.top()]] << ' ';
        stk.pop();
    }
}