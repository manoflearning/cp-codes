#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

// FFT
typedef complex<double> base;

void fft(vector<base> &a, bool inv) {
	int n = a.size(), j = 0;
	vector<base> roots(n / 2);
	for (int i = 1; i < n; i++){
		int bit = (n >> 1);
		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++){
		roots[i] = base(cos(ang * i), sin(ang * i));
	}
	for (int i = 2; i <= n; i <<= 1){
		int step = n / i;
		for (int j = 0; j < n; j += i){
			for (int k = 0; k < i / 2; k++) {
				base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (inv) for (int i = 0; i < n; i++) a[i] /= n;
}

void multiply(const vector<ll> &v, const vector<ll> &w, vector<ll>& res) {
	vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
	int n = 2; while (n < v.size() + w.size()) n <<= 1;
	fv.resize(n); fw.resize(n);
	fft(fv, 0); fft(fw, 0);
	for (int i = 0; i < n; i++) fv[i] *= fw[i];
	fft(fv, 1);

	if (sz(res) < n) res.resize(n);
	for (int i = 0; i < n; i++) res[i] += (ll)round(fv[i].real());
}

// sieve of eratosthenes
const int MAX = 50505;

bool isPrime[MAX + 1];
vector<int> prime(1, 2);

void getPrime() {
	fill(isPrime + 2, isPrime + MAX + 1, 1);

	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAX; i++) {
		if (isPrime[i]) prime.push_back(i);
		for (ll j = i * i; j <= MAX; j += i * 2)
			isPrime[j] = 0;
	}
}

// input & data
int n;
vector<int> adj[MAX];
vector<ll> ans(MAX);

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

// centroid decomposition
int used[MAX], siz[MAX], dep[MAX], cdtree[MAX];

int getSize(int now, int prv) {
	siz[now] = 1;
	for (auto i : adj[now]) {
		if (used[i] || prv == i) continue;
		siz[now] += getSize(i, now);
	}
	return siz[now];
}

int getCent(int now, int prv, int cnt) {
	for (auto& i : adj[now]) {
		if (used[i] || i == prv) continue;
		if (siz[i] > cnt / 2) return getCent(i, now, cnt);
	}
	return now;
}

void dfs(int v, int prv, int d, vector<ll>& res) {
    if (sz(res) <= d) res.resize(d + 1);
    res[d]++;

    for (int i : adj[v]) {
        if (used[i] || i == prv) continue;
        dfs(i, v, d + 1, res);
    }
}

void cd(int now, int prv) {
	int cnt = getSize(now, prv);
	int cent = getCent(now, prv, cnt);
    
	cdtree[now] = prv;
	used[cent] = 1;

    vector<vector<ll>> arr;
    for (auto i : adj[cent]) {
        if (!used[i]) {
            arr.resize(sz(arr) + 1);
            dfs(i, cent, 1, arr.back());

            cd(i, cent);
        }
    }

    if (arr.empty()) return;

    vector<ll> psum(sz(arr[0]));
    for (int i = 1; i < sz(arr[0]); i++) { 
        psum[i] += arr[0][i];
        ans[i] += arr[0][i];
    }

    for (int i = 1; i < sz(arr); i++) {
        multiply(psum, arr[i], ans);

        if (sz(psum) < sz(arr[i])) psum.resize(sz(arr[i]));
        for (int j = 1; j < sz(arr[i]); j++) {
            psum[j] += arr[i][j];
            ans[j] += arr[i][j];
        }
    }
}

// main
int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    getPrime();

	input();

    cd(1, -1);

    ll pri = 0, all = 0;
    for (int i = 0; i < min(MAX, sz(ans)); i++) {
        all += ans[i];
        if (isPrime[i]) pri += ans[i];
    }

    cout << fixed;
    cout.precision(10);

    cout << (double)pri / all;

	return 0;
}