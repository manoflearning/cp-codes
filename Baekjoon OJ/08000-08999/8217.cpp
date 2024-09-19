#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

const int MAXN = 303030;
const int MAXM = 303030;
const int MAXQ = 303030;

struct Fenwick { // 1-indexed
    int flag;
    vector<__int128_t> t;
    void build(int N) {
        t.clear();
        flag = N;
        t.resize(flag + 1);
    }
    void add(int l, int r, ll val) { // add a val to all elements in interval [l, r]
        for (; l <= flag; l += l & -l) t[l] += val;
        for (r++; r<= flag; r += r & -r) t[r] -= val;
    }
    __int128_t query(int x) {
        __int128_t ret = 0;
        for (; x; x ^= x & -x) ret += t[x];
        return ret;
    }
}fw;

int n, m;
vector<int> o(MAXM);
vector<vector<int>> ro(MAXN);
vector<ll> p(MAXN);

int q;
struct Query { int l, r; ll w; };
vector<Query> qu(MAXQ);

void input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> o[i];
        ro[o[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> p[i];
    cin >> q;
    for (int i = 1; i <= q; i++)
        cin >> qu[i].l >> qu[i].r >> qu[i].w;
}

vector<int> l(MAXN), r(MAXN), mid(MAXN);

void pbs() {
    fill(all(l), 1);
    fill(all(r), q + 1);
    
    for (int cnt = 0; cnt < 30; cnt++) {
        fill(all(mid), INF);
        for (int i = 1; i <= n; i++) {
            if (l[i] == r[i]) continue;
            mid[i] = (l[i] + r[i]) >> 1;
        }

        int ord_idx = 0;
        vector<int> ord(n);
        iota(all(ord), 1);

        sort(all(ord), [&](int p1, int p2) {
            return mid[p1] < mid[p2];
        });

        fw.build(MAXM);

        for (int i = 1; i <= q; i++) {
            if (qu[i].l <= qu[i].r) {
                fw.add(qu[i].l, qu[i].r, qu[i].w);
            } else {
                if (1 <= qu[i].r && qu[i].r <= m) fw.add(1, qu[i].r, qu[i].w);
                if (1 <= qu[i].l && qu[i].l <= m) fw.add(qu[i].l, m, qu[i].w);
            }

            while (ord_idx < sz(ord) && mid[ord[ord_idx]] == i) {
                int v = ord[ord_idx++];
                __int128_t sum = 0;
                for (auto& i : ro[v]) sum += fw.query(i);
                if (sum < p[v]) l[v] = mid[v] + 1;
                else r[v] = mid[v];
            }
        }
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

    pbs();

    for (int i = 1; i <= n; i++) {
        if (l[i] == q + 1) cout << "NIE\n";
        else cout << l[i] << '\n';
    }
}
