// if T[j] < A[i], we can ignore T[j].
// if B[i] <= T[j], T[j] always changes the state of i.
// if A[i] <= T[j] < B[i], 
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;
const int MAXK = 202020;
const int sq = 737;

struct Query {
    int s, e, idx;
    bool operator<(const Query& rhs) const {
        return e > rhs.e;
    }
};

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p) {
        for (t[p += flag - 1]++; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;
struct SegMax {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
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
}mx;

int N, K;
int A[MAXN], B[MAXN], T[MAXK];
vector<int> rT[606060];

vector<Query> qu;
int vi[MAXN];

vector<int> c(1, -1);

ll ans = 0;

void input() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> A[i] >> B[i];
    for (int i = 1; i <= K; i++) cin >> T[i];
}

void valueCompression() {
    for (int i = 1; i <= N; i++) {
        c.push_back(A[i]);
        c.push_back(B[i]);
    }
    for (int i = 1; i <= K; i++) c.push_back(T[i]);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (int i = 1; i <= N; i++) {
        A[i] = lower_bound(all(c), A[i]) - c.begin();
        B[i] = lower_bound(all(c), B[i]) - c.begin();
    }
    for (int i = 1; i <= K; i++) {
        T[i] = lower_bound(all(c), T[i]) - c.begin();
        rT[T[i]].push_back(i);
    }
}

void makeQueries() {
    for (int i = 1; i <= N; i++) {
        if (A[i] > B[i]) {
            swap(A[i], B[i]);
            vi[i] = 1;
        }
        qu.push_back({ A[i], B[i], i });
    }
    sort(all(qu));
}

void f() {
    mx.build(sz(c));
    seg.build(sz(c));
    
    for (int i = 1; i < sz(c); i++) {
        for (auto& j : rT[i]) {
            mx.modify(i, j);
        }
    }

    int prv = sz(c) - 1;
    for (auto& i : qu) {
        for (; prv >= i.e; prv--) {
            for (auto& j : rT[prv]) seg.modify(j);
        }
        int tmp = ans;
        int lb = mx.query(i.s, i.e - 1);
        if (vi[i.idx] || lb > 0) {
            int cnt = seg.query(lb + 1, K);
            if (cnt & 1) ans += c[i.s];
            else ans += c[i.e];
        }
        else {
            int cnt = seg.query(lb + 1, K);
            if (cnt & 1) ans += c[i.e];
            else ans += c[i.s];
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    valueCompression();

    makeQueries();

    f();
    
    cout << ans;
}