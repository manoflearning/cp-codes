#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll, int>

const ll INF = 1e18;

int n, m;
int st, en;
vector<pli> adj[101010];
vector<ll> dist1(101010, INF), dist2(101010, INF);

void dijkstra(vector<ll>& dist, int bit) {
    priority_queue<pli> pq;
    dist[st] = 0;
    pq.push({ -dist[st], st });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        w *= -1;

        if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            auto [d, u] = i;
            if (bit && u == en) continue;
            if (dist[u] > d + w) {
                // cout << "fuck ";
                dist[u] = d + w;
                pq.push({ -dist[u], u });
            }
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    cin >> st >> en;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }

    dijkstra(dist1, 0);
    dijkstra(dist2, 1);

    vector<int> ans;
    for (int v = 1; v <= n; v++) {
        if (dist1[v] == dist1[en] * 2 && dist1[v] < dist2[v]) {
            ans.push_back(v);
        }
    }

    for (auto& i : ans) cout << i << ' ';

    if (ans.empty()) {
        cout << '*';
    }
}
