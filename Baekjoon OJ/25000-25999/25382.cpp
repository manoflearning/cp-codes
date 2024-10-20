#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 252525;
const int INF = 1e9 + 7;

int flag;
struct mxSeg {
    vector<int> t;
    void build(int n) {
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
}mx;
struct mnSeg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);

        for (int i = flag; i < flag + n; i++)
            t[i] = i - flag + 1;
        for (int i = flag + n; i < 2 * flag; i++)
            t[i] = INF;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = min(t[i << 1], t[i << 1 | 1]);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}mn, xy;

struct Node {
    int x, y, l, r, idx;
//    bool operator==(const Node& rhs) const { return idx == rhs.idx; }
//    bool operator!=(const Node& rhs) const { return idx != rhs.idx; }
//    bool operator<(const Node& rhs) const { return r ^ rhs.r ? r > rhs.r : idx < rhs.idx; }
};

int n, vi[MAXN];
vector<Node> a;
int ans[MAXN];

void NO() { 
    cout << "NO"; exit(0); 
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].l >> a[i].r;
        a[i].idx = i;
    }

    // sorting
    sort(a.begin(), a.end(), [&](const Node& p1, const Node& p2) {
        return p1.x < p2.x;
    });

    // solve
    mx.build(n);
    mn.build(n);
    for (auto& i : a) {
        int lb = 1 + mx.query(1, i.y - 1);
        int t = mn.query(max(lb, i.l), i.r);
        
        if (t == INF) NO();

        mx.modify(i.y, t);
        mn.modify(t, INF);

        ans[i.idx] = t;
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
}