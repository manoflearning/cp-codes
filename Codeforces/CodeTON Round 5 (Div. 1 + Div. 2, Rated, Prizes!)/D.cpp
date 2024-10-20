#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

struct wv { ll w; int v; };

int n, m;
vector<wv> adj[101];
vector<ll> upper(101, INF);

int bellmanFord() {
    upper[1] = 0;
    int update = 1;
    for (int i = 0; i <= n; i++) {
        update = 0;
        for (int now = 1; now <= n; now++) {
            if (upper[now] == INF) continue;
            for (auto& e : adj[now]) {
                int next = e.v;
                if (upper[next] > upper[now] + e.w) {
                    upper[next] = upper[now] + e.w;
                    update = 1;
                }
            }
        }
        if (!update) break;
    }
    return !update;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }

    if (bellmanFord() && upper[n] != INF) {
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);
        sort(arr.begin(), arr.end(), [&](int p1, int p2) {
            return upper[p1] < upper[p2];
        });

        vector<pair<string, ll>> ans;

        string s(n, '0');
        int idx = 0;
        ll prvT = 0;
        while (idx < n) {
            while (idx + 1 < n && upper[arr[idx]] == upper[arr[idx + 1]]) {
                s[arr[idx++] - 1] = '1';
            }
            s[arr[idx++] - 1] = '1';
            if (s[n - 1] == '1') break;
            ll nowT = upper[arr[idx]];
            ans.push_back({ s, nowT - prvT });
            prvT = nowT;
        }

        cout << upper[n] << ' ' << ans.size() << '\n';
        for (auto& i : ans) {
            cout << i.first << ' ' << i.second << '\n';
        }
    }
    else cout << "inf";
}