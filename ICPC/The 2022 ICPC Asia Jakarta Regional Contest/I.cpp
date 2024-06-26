#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 101010;

int n;
vector<int> t[MAXN], newt[MAXN];
struct Edge { int u, v; };
vector<Edge> e(MAXN);
int r = -1;
set<pii> s;

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
        e[i + 1] = { u, v };
    }
}

bool isPossible() {
    for (int v = 1; v <= n; v++) {
        if (sz(t[v]) == n - 1) return false;
    }
    return true;
}

int dep[MAXN];

void dfs(int v, int prv) {
    dep[v] = dep[prv] + 1;
    for (auto& i : t[v]) {
        if (i != prv) dfs(i, v);
    }
}

void add(int u, int v) {
    if (u > v) swap(u, v);
    s.insert({ u, v });
}
bool isExist(int u, int v) {
    if (u > v) swap(u, v);
    return s.count({ u, v });
}

vector<int> arr1, arr2;
void lastDfs1(int v, int prv) {
    arr1.push_back(v);
    for (auto& i : newt[v]) {
        if (i != prv) lastDfs1(i, v);
    }
}
void lastDfs2(int v, int prv) {
    arr2.push_back(v);
    for (auto& i : newt[v]) {
        if (i != prv) lastDfs2(i, v);
    }
}

void solve() {
    vector<int> ord(MAXN);
    for (int i = 0; i < sz(t[r]); i++) {
        ord[t[r][i]] = i;
    }

    for (int i = 1; i <= n - 1; i++) {
        add(e[i].u, e[i].v);
    }

    for (int i = 1; i <= n - 1; i++) {
        auto [u, v] = e[i];

        if (dep[u] > dep[v]) swap(u, v);

        int ans1 = -1, ans2 = -1;
        if (u == r) {
            if (ord[v] + 1 < sz(t[r])) {
                ans1 = v, ans2 = t[r][ord[v] + 1];
            }
            else {
                lastDfs1(u, -1);
                lastDfs2(v, -1);

                for (auto& p : arr1) if (ans1 == -1) {
                    for (auto& q : arr2) if (ans1 == -1) {
                        if (!isExist(p, q)) {
                            ans1 = p, ans2 = q;
                        }
                    }
                }
            }
        }
        else ans1 = r, ans2 = v;

        newt[ans1].push_back(ans2);
        newt[ans2].push_back(ans1);
        add(ans1, ans2);
        
        cout << ans1 << ' ' << ans2 << '\n';
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

    if (!isPossible()) {
        cout << -1;
        return 0;
    }

    r = e[n - 1].u;
    // r = 1;

    dfs(r, 0);

    solve();
}