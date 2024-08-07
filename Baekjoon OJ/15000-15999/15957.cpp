#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const int INFT = 1e9 + 7;

int N, K;
ll J;
vector<int> t[MAXN];
vector<int> co(MAXN);

vector<pll> wei[MAXN];

void input() {
    cin >> N >> K >> J;
    for (int v = 2; v <= N; v++) {
        int x; cin >> x;
        t[x].push_back(v);
    }
    for (int i = 1; i <= N; i++) cin >> co[i];
    for (int i = 0; i < K; i++) {
        int T, v, w;
        cin >> T >> v >> w;
        wei[v].push_back({ T, w });
    }
}

vector<int> in(MAXN), out(MAXN);
int p;
vector<int> siz(MAXN), cnt(MAXN);

void dfs(int v) {
    in[v] = ++p;

    siz[v] = 1;
    cnt[co[v]]++;
    for (auto& i : t[v]) {
        dfs(i);
        siz[v] += siz[i];
    }

    for (auto& i : wei[v]) i.sc /= siz[v];

    out[v] = p;
}

vector<int> c;
void cc() {
    for (int i = 1; i <= N; i++) {
        for (auto& j : wei[i]) {
            c.push_back(j.fr);
        }
    }
    c.push_back(-1);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (int i = 1; i <= N; i++) {
        for (auto& j : wei[i]) {
            j.fr = lower_bound(all(c), j.fr) - c.begin();
        }
    }
}

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

vector<int> l(MAXN), r(MAXN), mid(MAXN);
vector<ll> sum(MAXN);

void dfsPbs(int v) {
    for (auto& i : wei[v]) seg.add(i.fr, i.sc);

    int id = co[v];
    sum[id] += seg.query(1, mid[id]);
    for (auto& i : t[v]) dfsPbs(i);

    for (auto& i : wei[v]) seg.add(i.fr, -i.sc);
}

void pbs() {
    seg.build(sz(c) + 1);

    for (int i = 1; i <= N; i++) l[i] = 1, r[i] = sz(c);

    for (int k = 0; k < 17; k++) {
        for (int i = 1; i <= N; i++) {
            mid[i] = -1, sum[i] = 0;
            if (l[i] >= r[i]) continue;
            mid[i] = (l[i] + r[i]) >> 1;
        }

        dfsPbs(1);

        for (int i = 1; i <= N; i++) {
            if (mid[i] == -1) continue;
            if (J * cnt[i] < sum[i]) r[i] = mid[i];
            else l[i] = mid[i] + 1;
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

    dfs(1);

    cc();

    pbs();

    for (int i = 1; i <= N; i++) {
        cout << (l[co[i]] == sz(c) ? -1 : c[l[co[i]]]) << '\n';
    }
}