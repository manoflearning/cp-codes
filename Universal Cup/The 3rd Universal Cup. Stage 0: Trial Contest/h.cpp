#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int Q = 202020;
const double sq2 = sqrt(2);

int q, w;
int x[Q], y[Q], val[Q];
int st[Q], en[Q], len[Q];

int flag;
struct Seg {
    vector<int> mn, cnt;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        mn.resize(flag << 1);
        cnt.resize(flag << 1);
        for (int i = flag; i < flag + n; i++)
            cnt[i] = len[i - flag + 1];
        for (int i = flag - 1; i >= 1; i--) {
            update_cnt(i);
        }
    }
    void update_cnt(int n) {
        if (flag <= n) return;
        if (mn[n << 1] == 0 && mn[n << 1 | 1] == 0) {
            cnt[n] = cnt[n << 1] + cnt[n << 1 | 1];
        }
        else if (mn[n << 1] == 0) cnt[n] = cnt[n << 1];
        else if (mn[n << 1 | 1] == 0) cnt[n] = cnt[n << 1 | 1];
        else cnt[n] = 0;
    }
    void modify(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        update_cnt(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            mn[n] += val;
            update_cnt(n);
            return;
        }

        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        update_cnt(n);
    }
    int query() { return w - cnt[1]; }
}seg;

void input() {
    cin >> q >> w;
    set<pair<int, int>> s;
    for (int i = 1; i <= q; i++) {
        cin >> x[i] >> y[i];

        st[i] = x[i] - y[i];
        en[i] = x[i] + y[i];
        st[i] = max(st[i], 0);
        en[i] = min(en[i], w);

        if (s.count({ x[i], y[i] })) {
            val[i] = -1;
            s.erase({ x[i], y[i] });
        }
        else {
            val[i] = 1;
            s.insert({ x[i], y[i] });
        }
    }
}

void coor_comp() {
    vector<int> c;
    c.push_back(-1);
    c.push_back(0);
    for (int i = 1; i <= q; i++) {
        c.push_back(st[i]);
        c.push_back(en[i]);
    }
    c.push_back(w);

    sort(all(c));
    c.erase(unique(all(c)), c.end());
    
    for (int i = 1; i <= q; i++) {
        st[i] = lower_bound(all(c), st[i]) - c.begin();
        en[i] = lower_bound(all(c), en[i]) - c.begin();
    }

    for (int i = 1; i + 1 < sz(c); i++) {
        len[i] = c[i + 1] - c[i];
    }

    seg.build(sz(c));
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    coor_comp();

    cout << fixed << setprecision(9);

    // cout << seg.query() << '\n';
    for (int i = 1; i <= q; i++) {
        // cout << st[i] << ' ' << en[i] - 1 << '\n';
        seg.modify(st[i], en[i] - 1, val[i]);
        cout << sq2 * seg.query() << '\n';
    }
}