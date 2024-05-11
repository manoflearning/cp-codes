#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int MOD = 1e8;

const int MAXN = 1e8 + 1e6;  // limit for array size
struct Seg {  // 0-indexed
	int n;  // array size
	ll t[2 * MAXN];
	void build(int N) {
		n = N;
		// for (int i = 0; i < n; i++) cin >> t[n + i];
		// for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void add(int p) {  // set value at position p
		for (t[p += n]++; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {  // sum on interval [l, r)
		ll ret = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;

int n;
ll a[303030];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    ll ans = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
        ans += sum + a[i] * (i - 1);
        sum += a[i];
    }

    vector<int> ord(n);
    iota(all(ord), 1);

    sort(all(ord), [](int p1, int p2) {
        return a[p1] < a[p2];
    });

    seg.build(n + 1);

    int j = n - 1;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && a[ord[i]] + a[ord[j]] >= MOD) seg.add(ord[j--]);

        ans -= MOD * seg.query(1, ord[i]);
    }

    cout << ans;
}