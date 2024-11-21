#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

const int MAXN = 101010;
int n, m;

vector<int> ans;
vector<pii> e;

void input() {
    cin >> n >> m;
    e.clear();
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v});
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();
        ans.resize(n);
        iota(all(ans), 1);

        int res = 0;
        for (auto &[u, v] : e) {
            if (u<v) res++;
        }

        if (res < (m + 1) / 2) {
            reverse(all(ans));
        }

        for(auto &u:ans) cout << u << ' ';
        cout << '\n';
    }
}
