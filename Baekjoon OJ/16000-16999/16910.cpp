#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int flag;
struct Seg {
    vector<int> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void modify(int l, int r, int op, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] = op;
            propagate(n, nl, nr);
            return;
        }

        int mid = (nl + nr) >> 1;
        modify(l, r, op, n << 1, nl, mid);
        modify(l, r, op, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    int mex(int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nl == nr) {
            assert(t[n] == 0);
            return nl;
        }
        
        int mid = (nl + nr) >> 1;
        propagate(n << 1, nl, mid);
        if (t[n << 1] < (mid - nl + 1)) return mex(n << 1, nl, mid);
        else return mex(n << 1 | 1, mid + 1, nr);
    }
    void propagate(int n, int nl, int nr) {
        if (!lazy[n]) return;

        if (n < flag) {
            if (lazy[n] == 1 || lazy[n] == 2) {
                lazy[n << 1] = lazy[n];
                lazy[n << 1 | 1] = lazy[n];
            }
            if (lazy[n] == 3) {
                lazy[n << 1] = (3 - lazy[n << 1]);
                lazy[n << 1 | 1] = (3 - lazy[n << 1 | 1]);

                // if (lazy[n << 1] == 0) lazy[n << 1] = 3;
                // else if (lazy[n << 1] == 1) lazy[n << 1] = 2;
                // else if (lazy[n << 1] == 2) lazy[n << 1] = 1;
                // else if (lazy[n << 1] == 3) lazy[n << 1] = 0;

                // if (lazy[n << 1 | 1] == 0) lazy[n << 1 | 1] = 3;
                // else if (lazy[n << 1 | 1] == 1) lazy[n << 1 | 1] = 2;
                // else if (lazy[n << 1 | 1] == 2) lazy[n << 1 | 1] = 1;
                // else if (lazy[n << 1 | 1] == 3) lazy[n << 1 | 1] = 0;
            }
        }

        if (lazy[n] == 1) t[n] = (nr - nl + 1);
        if (lazy[n] == 2) t[n] = 0;
        if (lazy[n] == 3) t[n] = (nr - nl + 1) - t[n];
        lazy[n] = 0;
    }
}seg;

int n;
struct Query { int op; ll l, r; };
Query qu[101010];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> qu[i].op >> qu[i].l >> qu[i].r;
}

vector<ll> cc;
void value_comp() {
    cc.push_back(-1);
    cc.push_back(1);
    for (int i = 1; i <= n; i++) {
        cc.push_back(qu[i].l);
        cc.push_back(qu[i].r);
        cc.push_back(qu[i].r + 1);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 1; i <= n; i++) {
        qu[i].l = lower_bound(all(cc), qu[i].l) - cc.begin();
        qu[i].r = lower_bound(all(cc), qu[i].r) - cc.begin();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    value_comp();

    seg.build(sz(cc));

    for (int i = 1; i <= n; i++) {
        seg.modify(qu[i].l, qu[i].r, qu[i].op);

        int ans = seg.mex();
        cout << cc[ans] << '\n';
    }
}
