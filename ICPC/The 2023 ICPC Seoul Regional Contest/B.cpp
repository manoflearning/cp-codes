#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 202020;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++)
            t[i] = 1;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int p) {
        for (t[p += flag - 1]--; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    int kth(int x, int n = 1, int nl = 1, int nr = flag) {
        if (nl == nr) return nl;

        int mid = (nl + nr) >> 1;
        if (x <= t[n << 1]) {
            return kth(x, n << 1, nl, mid);
        } else {
            return kth(x - t[n << 1], n << 1 | 1, mid + 1, nr);
        }
    }
}seg;

int n, z[MAXN];
int a[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> z[i];

    // after while loop
    int coconut = z[n - 1] % (n - 1);
    swap(z[0], z[coconut]);

    // while loop
    seg.build(n);

    int mango = 0;
    for (int i = 0; i + 1 < n; i++) {
        int idx = seg.kth(mango + 1);
        a[idx - 1] = z[i];

        seg.add(idx);
        mango = (z[i] + mango - 1) % (n - i - 1);
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) { a[i] = z[n - 1]; break; }
    }

    for (int i = 0; i < n; i++)
        cout << a[i] << '\n';
}
