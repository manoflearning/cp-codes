#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, int val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

ll psum[303030];

int n, m;
vector<int> a;
vector<int> l[101010];

void input() {
    cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;
    for (int i = 0; i < m; i++) {
        int cnt; cin >> cnt;
        l[i].resize(cnt);
        for (auto& j : l[i]) cin >> j;
    }
}

void cc() {
    vector<ll> c(1, -1);
    for (auto& i : a) c.push_back(i);
    for (int i = 0; i < m; i++) {
        for (auto& j : l[i]) c.push_back(j);
    }

    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    for (auto& i : a) i = lower_bound(c.begin(), c.end(), i) - c.begin();
    for (int i = 0; i < m; i++) {
        for (auto& j : l[i]) j = lower_bound(c.begin(), c.end(), j) - c.begin();
    }
}

ll f(const vector<int>& arr) {
    // for (auto& i : a) seg.add(i, 1);
    
    ll ret = 1e18;

    ll cnt = 0;
    for (auto& i : arr) cnt += psum[303029] - psum[i];
    ret = min(ret, cnt);
    
    for (auto& i : arr) {
        cnt -= psum[303029] - psum[i];
        cnt += psum[i - 1];
        ret = min(ret, cnt);
    }

    return ret;
}

ll inv(const vector<int>& arr) {
    ll ret = 0;

    for (auto& i : arr) {
        ret += seg.query(i + 1, 303030);
        seg.add(i, 1);
    }

    for (auto& i : arr) seg.add(i, -1);

    return ret;
}

void solve() {
    seg.build(303030);

    for (auto& i : a) psum[i]++;
    for (int i = 1; i < 303030; i++) {
        psum[i] += psum[i - 1];
    }

    ll inva = inv(a);
    for (int i = 0; i < m; i++) {
        cout << f(l[i]) + inva + inv(l[i]) << '\n';
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

    cc();

    solve();
}