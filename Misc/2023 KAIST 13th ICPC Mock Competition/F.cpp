#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 101010;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

int n;
vector<int> p(MAXN);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> p[i];

        seg.build(n);
        for (int i = 1; i <= n; i++) seg.modify(i, p[i]);

        vector<int> ans;

        int idx = 1;
        while (idx < n) {
            int pmax = seg.query(1, idx);
            if (idx == pmax) {
                swap(p[idx], p[idx + 1]);
                ans.push_back(idx);
                seg.modify(idx, p[idx]);
                seg.modify(idx + 1, p[idx + 1]);
            } else idx = pmax;
        }

        cout << sz(ans) << '\n';
        for (auto& i : ans) cout << i << ' ';
        cout << '\n';
    }
}
