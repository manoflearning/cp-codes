#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int n;
int R[25], cnt[25];

void init() {
    for (int i = 1; i <= 24; i++)
        R[i] = cnt[i] = 0;
}

void input() {
    for (int i = 1; i <= 24; i++) cin >> R[i];
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x + 1]++;
    }
}

struct wv { int w, v; };
vector<wv> adj[100];
int psum[100];

void bsinit() {
    for (int i = 0; i <= 25; i++) {
        adj[i].clear();
        psum[i] = INF;
    }
}

void graphModeling(int mid) {
    // R[i] <= psum[i] - psum[i - 8]
    for (int i = 1; i <= 24; i++) {
        if (i <= 8) {
            // psum[i] + mid - psum[i - 8 + 24] >= R[i]
            // iff psum[i - 8 + 24] - psum[i] <= -R[i] + mid
            adj[i].push_back({ -R[i] + mid, i - 8 + 24 });
        }
        if (i >= 9) {
            // psum[i - 8] - psum[i] <= -R[i]
            adj[i].push_back({ -R[i], i - 8 });
        }
    }
    
    // psum[i] - psum[i - 1] <= cnt[i]
    for (int i = 1; i <= 24; i++)
        adj[i - 1].push_back({ cnt[i], i });
    
    // psum[i] <= psum[i + 1]
    // iff psum[i] - psum[i + 1] <= 0
    for (int i = 0; i < 24; i++)
        adj[i + 1].push_back({ 0, i });
    
    // psum[24] - psum[0] = mid
    // iff psum[24] - psum[0] <= mid
    // and psum[0] - psum[24] <= -mid
    adj[0].push_back({ mid, 24 });
    adj[24].push_back({ -mid, 0 });
    
    // source vertex to all vertices
    for (int i = 0; i <= 24; i++) {
        adj[25].push_back({ 0, i });
    }
}

int bellmanFord() {
    psum[25] = 0;
    for (int i = 0; i < 26; i++) {
        int update = 0;
        for (int v = 0; v <= 25; v++) {
            if (psum[v] == INF) continue;
            for (auto& i : adj[v]) {
                if (psum[i.v] > psum[v] + i.w) {
                    psum[i.v] = psum[v] + i.w;
                    update = 1;
                }
            }
        }
        if (!update) break;
        if (i == 25) return 0;
    }
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        int l = 0, r = n + 1;
        while (l < r) {
            bsinit();

            int mid = (l + r) >> 1;
            graphModeling(mid);
            
            if (bellmanFord()) r = mid;
            else l = mid + 1;
        }

        bsinit();
        graphModeling(l);
        
        if (l < n + 1) cout << l << '\n';
        else cout << "No Solution\n";
    }
}