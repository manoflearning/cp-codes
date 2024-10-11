#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int D = 33;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

ll dexp1[33], dexp2[33];

int siz[33];
int cdpar[33];
int cddep[33];
vector<int> cdchd[33], cdbydep[33];
int cdsiz[33];
bool used[33];

vector<int> arr[33];

void cdinit() {
    memset(siz, 0, sizeof(siz));
    memset(cdpar, 0, sizeof(cdpar));
    memset(cddep, 0, sizeof(cddep));
    for (int i = 0; i < 33; i++) {
        cdchd[i].clear();
        cdbydep[i].clear();
        arr[i].clear();
    }
    memset(cdsiz, 0, sizeof(cdsiz));
    memset(used, 0, sizeof(used));
}

int get_size(int v, int prv, const vector<vector<int>>& adj) {
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (used[i] || i == prv) continue;
        siz[v] += get_size(i, v, adj);
    }
    return siz[v];
}
int get_cent(int v, int prv, int mxsiz, const vector<vector<int>>& adj) {
    for (auto& i : adj[v]) {
        if (used[i] || i == prv) continue;
        if (siz[i] > mxsiz / 2) return get_cent(i, v, mxsiz, adj);
    }
    return v;
}

void cd(int v, int prv, const vector<vector<int>>& adj) {
    int mxsiz = get_size(v, prv, adj);
    int cent = get_cent(v, prv, mxsiz, adj);

    cdpar[cent] = prv;
    cdchd[prv].push_back(cent);
    cddep[cent] = 1 + cddep[prv];
    cdbydep[cddep[cent]].push_back(cent);
    cdsiz[cent] = mxsiz;
    used[cent] = 1;

    for (auto& i : adj[cent]) {
        if (!used[i]) cd(i, cent, adj);
    }
}

set<tuple<ll, ll>> ans;

void hashing() {
    cdinit();

    int s; cin >> s;
    vector<vector<int>> adj(s);
    for (int i = 0; i < s - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cd(0, s, adj);

    for (int d = 30; d >= 1; d--) {
        if (cdbydep[d].empty()) continue;
        
        for (auto& v : cdbydep[d]) {
            sort(all(cdchd[v]), [&](int p1, int p2) {
                return arr[p1] < arr[p2];
            });

            for (auto& u : cdchd[v]) {
                for (auto& i : arr[u]) {
                    arr[v].push_back(i);
                }
            }

            arr[v].push_back(cdsiz[v]);
        }
    }

    ll res1 = 0, res2 = 0;
    for (int i = 0; i < sz(arr[cdbydep[1][0]]); i++) {
        res1 = (res1 + arr[cdbydep[1][0]][i] * dexp1[i]) % MOD1;
        res2 = (res2 + arr[cdbydep[1][0]][i] * dexp2[i]) % MOD2;
    }
    cout << res1 << ' ' << res2 << '\n';

    ans.insert({ res1, res2 });
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    dexp1[0] = dexp2[0] = 1;
    for (int i = 1; i < 33; i++) {
        dexp1[i] = D * dexp1[i - 1] % MOD1;
        dexp2[i] = D * dexp2[i - 1] % MOD2;
    }

    int n; cin >> n;

    for (int i = 0; i < n; i++) hashing();

    cout << sz(ans);
}
