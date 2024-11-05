#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 505050;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, int val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} sega, segb;

int n;
int a[MAXN], b[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    sega.build(n);
    segb.build(n);

    vector<int> ord(n);
    iota(all(ord), 1);
    sort(all(ord), [&](int p1, int p2) {
        return a[p1] < a[p2];
    });

    ll xa = 0, xb = 0;
    for (int i = 0; i < n; i++) {
        int idx = ord[i];
        xb += segb.query(b[idx] + 1, n);
        segb.add(b[idx], 1);
    }
    
    if (xb & 1) {
        cout << "No";
        exit(0);
    }

    cout << "Yes\n";

    if (xb == 0) {
        for (int i = 0; i < n; i++) {
            cout << a[ord[i]] << ' ';
        }
        cout << '\n';
        for (int i = 0; i < n; i++) {
            cout << b[ord[i]] << ' ';
        }
        cout << '\n';
        exit(0);
    }
    
    vector<int> lmost;
    vector<bool> used(n + 1);

    for (int i = n - 1; i >= 0; i--) {
        int idx = ord[i];

        ll acnt = i;
        ll bcnt = segb.query(1, b[idx] - 1) - segb.query(b[idx] + 1, n);

        segb.add(b[idx], -1);

        if ((xa + acnt) < (xb + bcnt)) {
            xa += acnt;
            xb += bcnt;
            lmost.push_back(idx);
            used[idx] = 1;
        } else {
            acnt = 0, bcnt = 0;
            for (int j = i - 1; j >= 0; j--) {
                int idx2 = ord[j];

                acnt++;
                if (b[idx2] < b[idx]) bcnt++;
                else bcnt--;

                if (xa + acnt == xb + bcnt) {
                    for (auto &x : lmost) cout << a[x] << ' ';
                    for (int k = 0; k < j; k++) {
                        if (!used[ord[k]]) cout << a[ord[k]] << ' ';
                    }
                    cout << a[ord[i]] << ' ';
                    for (int k = j; k < i; k++) {
                        if (!used[ord[k]]) cout << a[ord[k]] << ' ';
                    }
                    cout << '\n';
                    for (auto &x : lmost) cout << b[x] << ' ';
                    for (int k = 0; k < j; k++) {
                        if (!used[ord[k]]) cout << b[ord[k]] << ' ';
                    }
                    cout << b[ord[i]] << ' ';
                    for (int k = j; k < i; k++) {
                        if (!used[ord[k]]) cout << b[ord[k]] << ' ';
                    }

                    exit(0);
                }
            }
        }
    }

    assert(0);
}
