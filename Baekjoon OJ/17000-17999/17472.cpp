#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

vector<int> ds(7, -1);

int find(int x) {
    if (ds[x] < 0) return x;
    return ds[x] = find(ds[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    ds[U] = V;
}

struct Edge {
    int w, u, v;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};

int n, m;
int arr[111][111];

int label[111][111], cnt;
vector<pii> p[7];

vector<Edge> edge;

void dfs(int y, int x) {
    label[y][x] = cnt;
    p[cnt].push_back({ y, x });
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if (!arr[ny][nx] || label[ny][nx]) continue;
        dfs(ny, nx);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!arr[i][j] || label[i][j]) continue;
            cnt++;
            dfs(i, j);
        }
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = i + 1; j <= cnt; j++) {
            for (auto& u : p[i]) {
                for (auto& v : p[j]) {
                    if (u.fr != v.fr && u.sc != v.sc) continue;

                    if (u.fr == v.fr) {
                        int bit = 0;
                        for (int k = min(u.sc, v.sc) + 1; k < max(u.sc, v.sc); k++) {
                            if (arr[u.fr][k]) { bit = 1; break; }
                        }
                        if (bit) continue;
                    }
                    else {
                        int bit = 0;
                        for (int k = min(u.fr, v.fr) + 1; k < max(u.fr, v.fr); k++) {
                            if (arr[k][u.sc]) { bit = 1; break; }
                        }
                        if (bit) continue;
                    }

                    int w = max(abs(u.fr - v.fr), abs(u.sc - v.sc)) - 1;
                    if (w >= 2) edge.push_back({ w, i, j });
                }
            }
        }
    }

    sort(edge.begin(), edge.end());

    int ans = 0;
    for (auto& e : edge) {
        if (find(e.u) == find(e.v)) continue;
        ans += e.w;
        merge(e.u, e.v);
    }

    set<int> s;
    for (int i = 1; i <= cnt; i++) {
        s.insert(find(i));
    }

    cout << (s.size() >= 2 ? -1 : ans);

    return 0;
}