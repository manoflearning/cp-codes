#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 111;
const int MAXM = 111;
const int MAXW = 111;

int n, m, q;
ll a[MAXN];
struct Edge {
    int u, v;
    ll w;
};
vector<Edge> e;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v, (ll)sqrt(a[u] + a[v])});
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    
}
