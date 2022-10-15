#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;  // array size
struct Seg {  // 1-indexed
    vector<ll> t;

    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
	}
    void modify(int p, ll value) {  // set value at position p
        for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) / 2;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n, k;
int a[252525];
ll ans = 0;

ll f() {
    int l = 1, r = 65535 + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (seg.query(0, mid) >= (k + 1) / 2) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]++;
    }

    seg.build(65535 + 1);

    for (int i = 1; i <= k; i++) 
        seg.modify(a[i], 1);

    ans += f() - 1;
    for (int i = 2; i + k - 1 <= n; i++) {
        seg.modify(a[i - 1], -1);
        seg.modify(a[i + k - 1], 1);
        ans += f() - 1;
    }
    
    cout << ans;

    return 0;
}