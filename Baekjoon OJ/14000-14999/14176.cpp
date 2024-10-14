#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

typedef vector<ll> poly;
typedef complex<double> cpx;
void fft(vector<cpx> &a, bool inv){
    int n = a.size(), j = 0;
    vector<cpx> roots(n/2);
    for(int i=1; i<n; i++){
        int bit = (n >> 1);
        while(j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }
    double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
    for(int i=0; i<n/2; i++) roots[i] = cpx(cos(ang * i), sin(ang * i));
    for(int i=2; i<=n; i<<=1){
        int step = n / i;
        for(int j=0; j<n; j+=i) for(int k=0; k<i/2; k++){
            cpx u = a[j+k], v = a[j+k+i/2] * roots[step * k];
            a[j+k] = u+v; a[j+k+i/2] = u-v;
        }
    }
    if(inv) for(int i=0; i<n; i++) a[i] /= n;
}
vector<ll> multiply(vector<ll> &v, vector<ll> &w){
    vector<cpx> fv(v.begin(), v.end()), fw(w.begin(), w.end());
    int n = 2; while(n < v.size() + w.size()) n <<= 1;
    fv.resize(n); fw.resize(n);
    fft(fv, 0); fft(fw, 0);
    for(int i=0; i<n; i++) fv[i] *= fw[i];
    fft(fv, 1);
    vector<ll> ret(n);
    for(int i=0; i<n; i++) ret[i] = (ll)round(fv[i].real());
    return ret;
}
 
const int MAXN = 101010;
const int MAXD = 17;

bool isPrime[MAXN + 1];
vector<int> prime(1, 2);
void getPrime() {
	fill(isPrime + 2, isPrime + MAXN + 1, 1);
	for (ll i = 4; i <= MAXN; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAXN; i += 2) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
		for (ll j = i * i; j <= MAXN; j += i * 2)
			isPrime[j] = 0;
	}
}

int n;
vector<int> adj[MAXN];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int par[MAXN][MAXD], dep[MAXN];

void dfs(int v, int prv) {
    par[v][0] = prv;
    dep[v] = 1 + dep[prv];
    for (auto& i : adj[v]) {
        if (i != prv) dfs(i, v);
    }
}
void build_sparse_table() {
    for (int d = 0; d + 1 < MAXD; d++) {
        for (int v = 1; v <= n; v++) {
            par[v][d + 1] = par[par[v][d]][d];
        }
    }
}
int dist(int u, int v) {
    int ret = 0;

    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int i = 0; i < MAXD; i++)
        if (diff & (1 << i)) v = par[v][i];
    ret += diff;

    if (u == v) return ret;
    
    for (int i = MAXD - 1; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            u = par[u][i];
            v = par[v][i];
            ret += (1 << (i + 1));
        }
    }

    return ret + 2;
}

int siz[MAXN];
vector<int> cdchd[MAXN];
int cdpar[MAXN];
bool used[MAXN];

int get_size(int v, int prv) {
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (!used[i] && i != prv) 
            siz[v] += get_size(i, v);
    }
    return siz[v];
}
int get_cent(int v, int prv, int tot) {
    for (auto& i : adj[v]) {
        if (used[i] || i == prv) continue;
        if (siz[i] > tot / 2) return get_cent(i, v, tot);
    }
    return v;
}

void cd(int v, int prv) {
    int tot = get_size(v, prv);
    int cent = get_cent(v, prv, tot);
    
    cdchd[prv].push_back(cent);
    cdpar[cent] = prv;
    used[cent] = 1;

    for (auto& i : adj[cent]) {
        if (!used[i]) cd(i, cent);
    }
}

unordered_map<int, vector<ll>> arr[MAXN];
ll ans = 0;

void solve() {
    for (int v = 1; v <= n; v++) {
        {
            auto& res = arr[v][0];
            res.resize(1, 1);
        }
        for (int p = v; cdpar[p] != 0; p = cdpar[p]) {
            int w = dist(v, cdpar[p]);

            auto& res = arr[cdpar[p]][p];
            if (sz(res) <= w) res.resize(w + 1);

            res[w]++;
        }
    }

    for (int p = 1; p <= n; p++) {
        auto& arrp = arr[p][0];

        sort(all(cdchd[p]), [&](int p1, int p2) {
            return sz(arr[p][p1]) < sz(arr[p][p2]);
        });

        for (int v : cdchd[p]) {
            auto& arrv = arr[p][v];

            auto res = multiply(arrp, arrv);
            for (auto& pri : prime) {
                if (sz(res) <= pri) break;
                ans += res[pri];
            }

            if (sz(arrp) < sz(arrv))
                arrp.resize(sz(arrv));
            for (int i = 0; i < sz(arrv); i++) {
                arrp[i] += arrv[i];
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

    getPrime();

    input();

    dfs(1, 0);
    build_sparse_table();

    cd(1, 0);

    solve();

    cout << (double)ans / ((ll)n * (n - 1) / 2);
}
