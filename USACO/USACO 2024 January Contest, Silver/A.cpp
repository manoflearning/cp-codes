#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int INF = 1e9 + 7;

int flag;
struct Seg {
    vector<int> t;
    void build(int n, vector<int>& a) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = 1; i <= n; i++)
            t[i + flag - 1] = a[i];
        for (int i = flag - 1; i >= 1; i--)
            t[i] = max(t[i << 1], t[i << 1 | 1]);
    }
    void modify(int p, int val) {
        t[p + flag - 1] = max(t[p + flag - 1], val);
        for (p += flag - 1; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int N, Q, C;
        cin >> N >> Q >> C;
        
        vector<int> c(N + 1);
        for (int i = 1; i <= N; i++) cin >> c[i];

        seg.build(N, c);

        vector<pii> a(Q);
        vector<int> ub(N + 1, C);
        vector<int> ah(N + 1);
        vector<int> ha(N + 1);
        for (auto& i : a) {
            cin >> i.fr >> i.sc;
            ah[i.fr] = i.sc;
            ha[i.sc] = max(ha[i.sc], i.fr);
            if (c[i.sc] != 0) {
                ub[i.fr] = min(ub[i.fr], c[i.sc] - 1);
            }
        }

        int lb = 0;
        for (int i = N; i >= 1; i--) {
            if (ah[i] != 0) {
                lb = max(lb, seg.query(i + 1, ah[i] - 1));
                if (lb <= seg.query(1, i - 1)) lb = 0;
            }
            if (lb > 0 && c[i] == 0) {
                c[i] = lb, lb = 0;
                seg.modify(i, c[i]);
            }
        }

        // c[i] <= ub[i] for all i
        for (int i = N - 1; i >= 1; i--) {
            ub[i] = min(ub[i], ub[i + 1]);
        }

        bool isValid = 1;
        for (int i = 1; i <= N; i++) {
            int val = max(1, seg.query(1, ha[i]) + 1);

            if (c[i] == 0) { c[i] = val; seg.modify(i, c[i]); }
            else if (c[i] < val) isValid = 0;

            if (c[i] > ub[i]) isValid = 0;
        }

        if (isValid) {
            for (int i = 1; i <= N; i++) 
                cout << c[i] << ' ';
            cout << '\n';
        }
        else cout << -1 << '\n';
    }
}