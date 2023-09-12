#include <bits/stdc++.h>
using namespace std;

const int MAXN = 252525;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
}seg;

int n, a[MAXN];
vector<int> t1[MAXN], t2[MAXN];
int in1[MAXN], out1[MAXN], in2[MAXN], out2[MAXN];
vector<int> ord;

void input() {
    cin >> n;
    for (int v = 1; v <= n; v++) cin >> a[v];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t1[u].push_back(v);
        t1[v].push_back(u);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t2[u].push_back(v);
        t2[v].push_back(u);
    }
}

int cnt = 0;
void dfs1(int v, int prv) {
    in1[v] = ++cnt;
    for (auto& i : t1[v]) if (i != prv) dfs1(i, v);
    out1[v] = cnt;
    ord.push_back(v);
}

void dfs2(int v, int prv) {
    in2[v] = ++cnt;
    for (auto& i : t2[v]) if (i != prv) dfs2(i, v);
    out2[v] = cnt;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs1(1, -1);
    cnt = 0;
    dfs2(1, -1);
}