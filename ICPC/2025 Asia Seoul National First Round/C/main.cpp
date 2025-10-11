#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int V = 28;
const int N = (V - 1) * V * V + (V - 1) * V + (V - 1);

struct Node {
    int x, y, z;

    int hash() const {
        return x * V * V + y * V + z;
    }
};

Node st, en;

int n, dist[N];
vector<int> cc;

void coor_comp() {
    cc.push_back(-1);
    cc.push_back(1);
    cc.push_back(2);
    cc.push_back(3);
    for (int i = 0; i < 4; i++) {
        cc.push_back(st.x + i);
        cc.push_back(st.y + i);
        cc.push_back(st.z + i);
        cc.push_back(en.x + i);
        cc.push_back(en.y + i);
        cc.push_back(en.z + i);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    st.x = lower_bound(all(cc), st.x) - cc.begin();
    st.y = lower_bound(all(cc), st.y) - cc.begin();
    st.z = lower_bound(all(cc), st.z) - cc.begin();
    en.x = lower_bound(all(cc), en.x) - cc.begin();
    en.y = lower_bound(all(cc), en.y) - cc.begin();
    en.z = lower_bound(all(cc), en.z) - cc.begin();

    n = sz(cc) - 1;
}

void move_next(int x, int y, int z, vector<int> ord, int v, queue<int> &qu) {
    int cnt = 0;
    for (int nx = x + 1; nx <= n; nx++) {
        if (nx == y || nx == z) cnt++;

        if (cnt == 1 && nx != y && nx != z) {
            vector<int> xyz = {nx, y, z};
            Node nxt{xyz[ord[0]], xyz[ord[1]], xyz[ord[2]]};
            if (dist[nxt.hash()] != -1) continue;

            qu.push(nxt.hash());
            dist[nxt.hash()] = dist[v] + 1;
        }
    }
    cnt = 0;
    for (int nx = x - 1; nx >= 1; nx--) {
        if (nx == y || nx == z) cnt++;

        if (cnt == 1 && nx != y && nx != z) {
            vector<int> xyz = {nx, y, z};
            Node nxt{xyz[ord[0]], xyz[ord[1]], xyz[ord[2]]};
            if (dist[nxt.hash()] != -1) continue;

            qu.push(nxt.hash());
            dist[nxt.hash()] = dist[v] + 1;
        }
    }
}

void bfs() {
    memset(dist, -1, sizeof(dist));
    
    queue<int> qu;
    qu.push(st.hash());
    dist[st.hash()] = 0;

    while (!qu.empty()) {
        int v = qu.front();
        qu.pop();

        Node now{v / (V * V), (v % (V * V)) / V, v % V};
        // cout << now.x << ' ' << now.y << ' ' << now.z << ' ' << dist[now.hash()] << '\n';
        move_next(now.x, now.y, now.z, {0, 1, 2}, v, qu);
        move_next(now.y, now.x, now.z, {1, 0, 2}, v, qu);
        move_next(now.z, now.x, now.y, {1, 2, 0}, v, qu);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> st.x >> st.y >> st.z;
    cin >> en.x >> en.y >> en.z;

    coor_comp();

    bfs();

    cout << dist[en.hash()];
}
