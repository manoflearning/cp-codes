#include <bits/stdc++.h>
using namespace std;

const int MAXV = 505;

int c, d, v;
int A[MAXV], B[MAXV];
vector<int> adj[MAXV];
bool visited[MAXV];
pair<string, string> arr[MAXV];

void init() {
    for (int i = 0; i < MAXV; i++) {
        adj[i].clear();
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
	for (int i = 1; i <= v; i++) {
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

    int tc; cin >> tc;
    while (tc--) {
        init();

        cin >> c >> d >> v;
        for (int i = 1; i <= v; i++) {
            cin >> arr[i].first >> arr[i].second;
        }

        for (int i = 1; i <= v; i++) {
            if (arr[i].first[0] != 'C') continue;
            for (int j = 1; j <= v; j++) {
                if (arr[j].first[0] != 'D') continue;
                if (arr[i].first == arr[j].second || arr[i].second == arr[j].first) {
                    adj[i].push_back(j);
                }
            }
        }

        cout << v - bipartiteMatch() << '\n';
    }
}