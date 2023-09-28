#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXN = 505050;
const int MAXL = 500001;
const int MAXT = 500001;
const ll INF = 1e18;

int flag;
struct Seg {
    vector<ll> t;
    void build() {
        for (flag = 1; flag < MAXL; flag <<= 1);
        t.resize(flag << 1, -INF);
    }
    void modify(int p, ll val) {
        t[p + flag - 1] = max(val, t[p + flag - 1]);
        for (p += flag - 1; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return -INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}segR, segL; 

struct Market {
    int x; ll M;
    bool operator<(const Market& rhs) const {
        return x < rhs.x;
    }
};

int N, S;
ll U, D;
vector<Market> a[MAXN];
ll dp[MAXN];

void input() {
    cin >> N >> U >> D >> S;
    for (int i = 0; i < N; i++) {
        int T, x, M;
        cin >> T >> x >> M;
        a[T].push_back({ x, M });
    }
    a[0].push_back({ S, 0 });
    a[MAXT].push_back({ S, 0 });
}

void sorting() {
    for (int i = 1; i <= MAXT; i++) {
        sort(all(a[i]));
    }
}

void modifyR(int p, ll val) { segR.modify(p, val - D * (MAXL - p)); }
void modifyL(int p, ll val) { segL.modify(p, val - U * (p - 1)); }
ll queryR(int p) { return segR.query(1, p - 1) + D * (MAXL - p); }
ll queryL(int p) { return segL.query(p + 1, MAXL) + U * (p - 1); }

void f() {
    for (int i = 1; i <= MAXL; i++) dp[i] = -INF;
    segR.build();
    segL.build();
    
    dp[S] = 0;
    modifyR(S, dp[S]);
    modifyL(S, dp[S]);

    for (int i = 1; i <= MAXT; i++) {
        for (int j = 0; j < sz(a[i]); j++) {
            int x = a[i][j].x; ll M = a[i][j].M;
            ll res = M + queryR(x);
            dp[x] = max(dp[x], res);
            modifyR(x, res);
        }
        for (int j = sz(a[i]) - 1; j >= 0; j--) {
            int x = a[i][j].x; ll M = a[i][j].M;
            ll res = M + queryL(x);
            dp[x] = max(dp[x], res);
            modifyL(x, res);
        }

        for (auto& j : a[i]) {
            modifyR(j.x, dp[j.x]);
            modifyL(j.x, dp[j.x]);
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

    sorting();

    f();

    cout << dp[S];
}