#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll val) {
        t[p + flag - 1] = (t[p + flag - 1] + val) % MOD;
        for (p += flag - 1; p > 1; p >>= 1)
            t[p >> 1] = (t[p] + t[p ^ 1]) % MOD;
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return (query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr)) % MOD;
    }
}seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        int n, m;
        ll X, Y, Z;
        cin >> n >> m >> X >> Y >> Z;

        vector<ll> A(m), B;
        for (auto& i : A) cin >> i;
        for (int i = 0; i < n; i++) {
            B.push_back(A[i % m]);
            A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
        }

        {
            vector<ll> cc;
            cc.push_back(-INF);
            for (auto& i : B) cc.push_back(i);
            
            sort(all(cc));
            cc.erase(unique(all(cc)), cc.end());

            for (auto& i : B)
                i = lower_bound(all(cc), i) - cc.begin();
        }

        // for (auto& i : B) 
        //     cout << i << ' ';
        // cout << '\n';

        {
            seg.build(n + 1);
            for (auto& i : B) {
                ll prv = seg.query(1, i - 1);
                seg.add(i, (prv + 1) % MOD);
            }
        }

        cout << "Case #" << tt << ": ";
        cout << seg.query(1, n + 1) << '\n';
    }
}
