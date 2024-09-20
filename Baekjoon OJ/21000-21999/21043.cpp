#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 50505;

struct UF {
    vector<int> uf;
    void build() {
        uf.resize(MAXN, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] = V;
    }
}uf;

int n;
vector<pii> a(MAXN);
vector<int> deg(MAXN);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].fr >> a[i].sc;
        deg[a[i].fr]++;
        deg[a[i].sc]++;
    }

    uf.build();

    for (int i = 1; i <= n; i++) {
        uf.merge(a[i].fr, a[i].sc);
    }

    int ans = 0;

    set<int> st;
    for (int i = 1; i <= n; i++) {
        st.insert(uf.find(a[i].fr));
        st.insert(uf.find(a[i].sc));
    }
    ans += sz(st);

    map<int, int> mp;
    for (int v = 1; v <= 50'000; v++) {
        if (deg[v] & 1) mp[uf.find(v)]++;
    }
    
    for (auto& [_, cnt] : mp) {
        int res = (cnt - 1) / 2;
        ans += res;
    }
    cout << ans;
}