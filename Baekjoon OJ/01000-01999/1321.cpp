#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) cin >> t[i];
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int p, ll value) {
        for (t[p += flag - 1] += value; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int kth(ll k, int n = 1) {
        assert(k <= t[n]);
        if (flag <= n) return n - flag + 1;
        if (k <= t[n << 1]) return kth(k, n << 1);
        else return kth(k - t[n << 1], n << 1 | 1);
    }
}seg;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    int n; cin >> n;
    seg.build(n);
    int m; cin >> m;
    while (m--) {
        int op, x, y;
        cin >> op >> x;
        if (op == 1) {
            cin >> y;
            seg.add(x, y);
        }
        if (op == 2) {
            cout << seg.kth(x) << '\n';
        }
    }
}