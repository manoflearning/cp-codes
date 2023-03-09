#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

const int MAX = 1010101;

int n, m;
vector<int> adj[MAX];

vector<vector<pii>> bcc;
set<pii> aEdge;

int dfsn[MAX], dCnt;
stack<pii> stk;
int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt;

	int childCnt = 0;
	for (int next : adj[now]) {
		if (next == prv) continue;

		// If an edge { now, next } has not yet been visited, puts an edge on the stack.
		if (dfsn[now] > dfsn[next]) stk.push({ now, next });
		
		// Back edge
		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		// Tree edge
		else {
			childCnt++;
			int tmp = dfs(next, now);
			ret = min(ret, tmp);

			if (tmp > dfsn[now])
				aEdge.insert({ min(now, next), max(now, next) });

			// If next cannot go to ancestor node of now, find BCC
			if (tmp >= dfsn[now]) {
				vector<pii> nowBCC;
				while (true) {
					pii t = stk.top();
					stk.pop();
					nowBCC.push_back(t);
					if (t == make_pair(now, next)) break;
				}
				bcc.push_back(nowBCC);
			}
		}
	}
	
	return ret;
}

int ans = -1;

void getBCC() {
	memset(dfsn, -1, sizeof(dfsn));
	for (int v = 1; v <= n; v++)
		if (dfsn[v] == -1) { dfs(v, -1); ans++; }
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
        int u, v;
        cin >> u >> v;
        u++, v++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    getBCC();

    cout << ans + aEdge.size();
}