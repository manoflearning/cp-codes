#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int MOD = 998244353;

const int N = 202020;

int n;
bool is_start[N];
vector<pii> e;

vector<int> adj[N];
int ind[N];

void input() {
    cin >> n;
    
    string s; cin >> s;
    for (int i = 0; i < n; i++)
        if (s[i] == 'S') is_start[i + 1] = 1;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        ind[v]++;
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


}

// dag => dp?
