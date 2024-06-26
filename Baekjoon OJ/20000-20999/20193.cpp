#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

int flag;
struct Seg {
    vector<int> t, lazy;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void init() {
        t.clear();
        lazy.clear();
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void propagate(int n) {
        if (!lazy[n]) return;

        if (n < flag) {
            lazy[n << 1] += lazy[n];
            lazy[n << 1 | 1] += lazy[n];
        }
        t[n] += lazy[n];
        lazy[n] = 0;
    }
    void modify(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            propagate(n);
            return;
        }

        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = max(t[n << 1], t[n << 1 | 1]);
    }
    int query() {
        propagate(1);
        return t[1];
    }
}seg;

struct Point {
    ll y; int c;
};

int n, k;
vector<Point> p[252525];
multiset<int> s[252525];

void add(int y, int c, int len) {
    int l = y, r = y + len;

    auto it = s[c].lower_bound(y);
    if (it != s[c].end()) r = min(r, *it - 1);
    if (it != s[c].begin()) {
        it--;
        l = max(l, *it + len + 1);
    }

    seg.modify(l, r, 1);
    s[c].insert(y);
}
void del(int y, int c, int len) {
    int l = y, r = y + len;

    s[c].erase(s[c].find(y));

    auto it = s[c].lower_bound(y);
    if (it != s[c].end()) r = min(r, *it - 1);
    if (it != s[c].begin()) {
        it--;
        l = max(l, *it + len + 1);
    }

    seg.modify(l, r, -1);
}

bool possible(int len) {
    // initialize
    seg.init();
    for (int i = 0; i < 252525; i++) s[i].clear();

    // solve
    for (int x = 0; x <= len; x++) {
        for (auto& i : p[x]) 
            add(i.y, i.c, len);
    }

    if (seg.query() == k) return 1;

    for (int x = len + 1; x <= 250000; x++) {
        for (auto& i : p[x])
            add(i.y, i.c, len);
        for (auto& i : p[x - len - 1])
            del(i.y, i.c, len);

        if (seg.query() == k) return 1;
    }

    return 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        p[x].push_back({ y, c });
    }

    seg.build(2 * 250000);

    int l = 0, r = 250000;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (possible(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
}