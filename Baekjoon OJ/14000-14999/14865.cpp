#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int flag;  // array size
struct mxSeg {  // 1-indexed
    vector<ll> t;

    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);

        //for (int i = flag; i < flag + n; i++) cin >> t[i];
        //for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void modify(int p, ll value) {  // set value at position p
        for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) / 2;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}mxseg;
struct mnSeg {  // 1-indexed
    vector<ll> t;

    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);

        //for (int i = flag; i < flag + n; i++) cin >> t[i];
        //for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void modify(int p, ll value) {  // set value at position p
        for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) / 2;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}mnseg;

struct point { int x, y; };

int n;
vector<point> p;
vector<pii> a;
vector<int> c;

void cc() {
    c.push_back(-INF);
    for (auto& i : a) {
        c.push_back(i.fr);
        c.push_back(i.sc);
    }

    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    for (auto& i : a) {
        i.fr = lower_bound(c.begin(), c.end(), i.fr) - c.begin();
        i.sc = lower_bound(c.begin(), c.end(), i.sc) - c.begin();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    p.resize(n);
    for (auto& i : p)
        cin >> i.x >> i.y;
    for (int i = 0; i < n; i++) 
        p.push_back(p[i]);

    int prv = -INF;
    for (int i = 0; i < 2 * n - 1; i++) {
        int b1 = (p[i].y < 0), b2 = (p[i + 1].y < 0);
        if (b1 != b2) {
            if (p[i].y < 0) prv = p[i].x;
            else {
                if (prv == -INF) prv = p[i].x;
                else a.push_back({ min(prv, p[i].x), max(prv, p[i].x) });
            }
        }
    }

    cc();

    mxseg.build(sz(c));
    mnseg.build(sz(c));

    int ans1 = 0, ans2 = 0;

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    for (auto& i : a) {
        if (mxseg.query(1, i.fr - 1) < i.fr) ans1++;
        mxseg.modify(i.fr, i.sc);
    }

    for (int i = sz(a) - 1; i >= 0; i--) {
        if (mnseg.query(a[i].fr + 1, a[i].sc - 1) > a[i].sc) ans2++;
        mnseg.modify(a[i].fr, a[i].sc);
    }

    cout << ans1 << ' ' << ans2;

    return 0;
}