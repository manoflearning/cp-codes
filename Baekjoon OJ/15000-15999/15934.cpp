#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int dy[] = { 0, 1, 0, -1 };
const int dx[] = { 1, 0, -1, 0 };
const int INF = 1e9 + 7;

int r, c;
ll d, w;
int a[55][55];
vector<ll> zs;
map<int, vector<pii>> mp;

int A[51 * 51], B[51 * 51];
set<int> adj[51 * 51];
bool visited[51 * 51];

set<int> st;

void input() {
    cin >> r >> c >> d >> w;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> a[i][j];
            zs.push_back(a[i][j]);
            mp[a[i][j]].push_back({ i, j });
        }
    }
}

bool dfs(int a) {
	visited[a] = 1;
	for (int b : adj[a]) {
		if (B[b] == -1 || (!visited[B[b]] && dfs(B[b]))) {
			A[a] = b;
			B[b] = a;
			return 1;
		}
	}
	return 0;
}
int bipartiteMatch() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	int ret = 0;
	for (auto i : st) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) ret++;
	}
	return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    zs.push_back(0);
    zs.push_back(INF);

    sort(all(zs));
    zs.erase(unique(all(zs)), zs.end());

    int cnte = 0, cnto = 0;

    ll ans = 1e18;
    for (int i = sz(zs) - 1; i >= 1; i--) {
        for (auto& [y, x] : mp[zs[i]]) {
            if ((y + x) & 1) cnto++;
            else {
                cnte++;
                st.insert((y-1) * 51 + (x-1));
            }

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 1 || r < ny || nx < 1 || c < nx) continue;
                if (a[ny][nx] < zs[i]) continue;

                if ((y + x) & 1) adj[(ny-1) * 51 + (nx-1)].insert((y-1) * 51 + (x-1));
                else adj[(y-1) * 51 + (x-1)].insert((ny-1) * 51 + (nx-1));
            }
        }

        if (cnte != cnto) continue;
        if (bipartiteMatch() != cnte) continue;

        ans = min(ans, zs[i - 1] * w + cnte * d);
    }

    cout << ans;
}
