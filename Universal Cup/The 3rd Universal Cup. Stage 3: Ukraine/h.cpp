#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998244353;
const ll w = 3;

const int N = 202020;

typedef vector<ll> poly;

ll pw(ll a, ll b){
    ll ret = 1;
    while(b){
        if(b & 1) ret = ret * a % MOD;
        b >>= 1; a = a * a % MOD;
    }
    return ret;
}

void ntt(poly &f, bool inv = 0){
    int n = f.size(), j = 0;
    vector<ll> root(n >> 1);
    for(int i=1; i<n; i++){
        int bit = (n >> 1);
        while(j >= bit){
            j -= bit; bit >>= 1;
        }
        j += bit;
        if(i < j) swap(f[i], f[j]);
    }
    ll ang = pw(w, (MOD - 1) / n); if(inv) ang = pw(ang, MOD - 2);
    root[0] = 1; for(int i=1; i<(n >> 1); i++) root[i] = root[i-1] * ang % MOD;
    for(int i=2; i<=n; i<<=1){
        int step = n / i;
        for(int j=0; j<n; j+=i){
            for(int k=0; k<(i >> 1); k++){
                ll u = f[j | k], v = f[j | k | i >> 1] * root[step * k] % MOD;
                f[j | k] = (u + v) % MOD;
                f[j | k | i >> 1] = (u - v) % MOD;
                if(f[j | k | i >> 1] < 0) f[j | k | i >> 1] += MOD;
            }
        }
    }
    ll t = pw(n, MOD - 2);
    if(inv) for(int i=0; i<n; i++) f[i] = f[i] * t % MOD;
}

vector<ll> multiply(poly &_a, poly &_b){
    vector<ll> a(all(_a)), b(all(_b));
    int n = 2;
    while(n < a.size() + b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a); ntt(b);
    for(int i=0; i<n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, 1);
    return a;
}

int n;
string s;
vector<int> t[N];
ll dp[N][3];
set<pii> st;

void input() {
    cin >> n;
    
    cin >> s;
    s = "F" + s;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
        st.insert({ u, v });
    }
}

void dfs(int v, int prv) {
    if ((sz(t[v]) == 1 && prv != -1) || sz(t[v]) == 0) {
        dp[v][0] = (s[v] == 'S' && st.count({ v, prv }));
        dp[v][1] = 1;
        dp[v][2] = (s[v] == 'F' && st.count({ prv, v }));
        return;
    }

    int cnt = 0;
    vector<vector<ll>> arr;
    for (auto& i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);
        if (st.count({ v, i }))
            arr.push_back({ 0, dp[i][1], dp[i][2] });
        else 
            arr.push_back({ dp[i][0], dp[i][1], 0 });
        cnt++;
    }
    if (sz(arr) == 1) {
        arr.push_back({ 0, 1, 0 });
        cnt++;
    }

    while (sz(arr) > 1) {
        vector<vector<ll>> tmp;
        for (int i = 0; i < sz(arr); i += 2) {
            if (i + 1 < sz(arr)) {
                int siz = sz(arr[i]) + sz(arr[i + 1]) - 1;
                tmp.push_back(multiply(arr[i], arr[i + 1]));
                tmp.back().resize(siz);
            }
            else tmp.push_back(arr[i]);
        }
        arr = tmp;
    }

    auto& acc = arr[0];

    int mid = sz(acc) / 2;
    if (s[v] == 'S') {
        dp[v][1] = acc[mid] + acc[mid + 1];
    }
    if (s[v] == 'F') {
        dp[v][1] = acc[mid - 1] + acc[mid];
    }

    if (st.count({ v, prv })) {
        if (s[v] == 'S') {
            dp[v][0] = acc[mid - 1] + acc[mid];
        }
        if (s[v] == 'F') {
            dp[v][0] = acc[mid - 2] + acc[mid - 1];
        }
    }
    if (st.count({ prv, v })) {
        if (s[v] == 'S') {
            dp[v][2] = acc[mid + 1] + acc[mid + 2];
        }
        if (s[v] == 'F') {
            dp[v][2] = acc[mid] + acc[mid + 1];
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

    dfs(1, -1);

    cout << (dp[1][1] % MOD + MOD) % MOD;
}