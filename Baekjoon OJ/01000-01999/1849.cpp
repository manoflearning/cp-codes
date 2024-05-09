#include <bits/stdc++.h>
using namespace std;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);

        for (int i = flag; i < flag + n; i++) t[i] = 1;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int kth(int k, int n = 1, int nl = 1, int nr = flag) {
        if (nl == nr) return nl;

        int mid = (nl + nr) >> 1;
        if (k <= t[n << 1]) return kth(k, n << 1, nl, mid);
        else return kth(k - t[n << 1], n << 1 | 1, mid + 1, nr);
    }
}seg;

int n, a[101010];
int ans[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    seg.build(n);

    for (int i = 1; i <= n; i++) {
        int pos = seg.kth(a[i] + 1);
        
        ans[pos] = i;
        seg.modify(pos, 0);
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}