// BOJ 2150 AC Code
// https://www.acmicpc.net/problem/2150

// Kosaraju's algorithm
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXV = 10101;

int n, m;
vector<int> adj[MAXV], radj[MAXV];

int in[MAXV], out[MAXV], num, p[2 * MAXV];
int vi[MAXV], cnt;
vector<vector<int>> scc;

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		radj[v].push_back(u);
	}
}

void dfs(int v) {
	in[v] = ++num;

	for (auto& i : radj[v]) {
		if (!in[i]) dfs(i);
	}
	
	out[v] = ++num;
	p[num] = v;
}

void ordering() {
	for (int v = 1; v <= n; v++) {
		if (!in[v]) dfs(v);
	}
}

void flood(int v) {
	scc[cnt].push_back(v);
	vi[v] = cnt;
	for (auto& i : adj[v]) {
		if (!vi[i]) flood(i);
	}
}

void kosaraju() {
	ordering();

	for (int v = 2 * n; v >= 1; v--) {
		if (!p[v]) continue;
		if (vi[p[v]]) continue;

		cnt++;
		scc.resize(cnt + 1);
		flood(p[v]);
	}
}

void print() {
	for (auto& i : scc)
		sort(i.begin(), i.end());

	sort(scc.begin(), scc.end());

	cout << sz(scc) - 1 << '\n';
	for (int i = 1; i < sz(scc); i++) {
		auto& arr = scc[i];
		for (auto& j : arr) cout << j << ' ';
		cout << -1 << '\n';
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	kosaraju();

	print();

	return 0;
}


// Tarjan's strongly connected components algorithm
/*#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 101010;

int n, m, label[MAXV], labelCnt;
int SCCnum[MAXV], SCCcnt, finished[MAXV];
vector<int> adj[MAXV];
stack<int> stk;
vector<vector<int>> SCC;

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
}

int dfs(int v) {
	label[v] = labelCnt++;
	stk.push(v);

	int ret = label[v];
	for (int next : adj[v]) {
		// Unvisited node.
		if (label[next] == -1) ret = min(ret, dfs(next));
		// Visited but not yet classified as SCC. In other words, edge { v, next } is back edge.
		else if (!finished[next]) ret = min(ret, label[next]);
	}
	
	// If there is no edge to the ancestor node among itself and its descendants, find scc.
	if (ret == label[v]) {
		vector<int> vSCC;
		while (1) {
			int t = stk.top();
			stk.pop();

			vSCC.push_back(t);
			SCCnum[t] = SCCcnt;
			finished[t] = 1;

			if (t == v) break;
		}

		SCC.push_back(vSCC);
		SCCcnt++;
	}

	return ret;
}

void getSCC() {
	memset(label, -1, sizeof(label));

	for (int v = 1; v <= n; v++)
		if (label[v] == -1) dfs(v);
}

void print() {
	for (int i = 0; i < (int)SCC.size(); i++) 
		sort(SCC[i].begin(), SCC[i].end());

	sort(SCC.begin(), SCC.end());

	cout << (int)SCC.size() << '\n';

	for (int i = 0; i < (int)SCC.size(); i++) {
		for (auto& j : SCC[i]) cout << j << ' ';
		cout << -1 << '\n';
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();

	getSCC();

	print();

	return 0;
}*/