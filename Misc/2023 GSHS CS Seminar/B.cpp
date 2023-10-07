#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr frist
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 505050;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int n;
ll a[MAXN];

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) t[i] = a[i + flag - 1];
        for (int i = flag - 1; i >= 1; i--)
            t[i] = gcd(t[i << 1], t[i << 1 | 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return gcd(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seggcd;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    seggcd.build(n);
}

ll psum[MAXN], ssum[MAXN];

void input() {
    
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    
}