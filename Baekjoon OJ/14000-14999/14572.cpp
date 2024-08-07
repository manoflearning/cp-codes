#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int flag;  // array size
struct orSeg {
    vector<ll> t;

    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
    }
    void modify(int p, ll value) {  // set value at position p
        for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] | t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) / 2;
        return query(l, r, n << 1, nl, mid) | query(l, r, n << 1 | 1, mid + 1, nr);
    }
}orseg;

struct andSeg {
    vector<ll> t;

    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
    }
    void modify(int p, ll value) {  // set value at position p
        for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] & t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
        if (r < nl || nr < l) return (1ll << 32) - 1;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) / 2;
        return query(l, r, n << 1, nl, mid) & query(l, r, n << 1 | 1, mid + 1, nr);
    }
}andseg;

struct Stu {
    int d, bit;
    bool operator<(const Stu& rhs) const {
        return d < rhs.d;
    }
};

int n, k, bo;
vector<Stu> a;

ll orquery(int l, int r) {
    int bit = orseg.query(l, r), ret = 0;
    for (int i = 0; i < 32; i++) {
        if ((1 << i) & bit) ret++;
    }
    return ret;
}

ll andquery(int l, int r) {
    int bit = andseg.query(l, r), ret = 0;
    for (int i = 0; i < 32; i++) {
        if ((1 << i) & bit) ret++;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k >> bo;
    a.push_back({ -INF, 0 });
    for (int i = 0; i < n; i++) {
        int m, d;
        cin >> m >> d;
        a.push_back({ d, 0 });
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            a.back().bit |= (1 << x);
        }
    }

    sort(a.begin(), a.end());

    orseg.build(n);
    andseg.build(n);
    for (int i = 1; i <= n; i++) {
        orseg.modify(i, a[i].bit);
        andseg.modify(i, a[i].bit);
    }

    int r = 1;
    ll ans = 0;
    for (int l = 1; l <= n; l++) {
        while (r <= n && a[r].d - a[l].d <= bo) r++;
        r--;
        
        ans = max(ans, (orquery(l, r) - andquery(l, r)) * (r - l + 1));
    }

    cout << ans;

    return 0;
}