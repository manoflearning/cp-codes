#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <stack>
#include <queue>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXV = 50 * 50;

int N, en;
map<string, int> mp;
vector<int> adj[MAXV + 5];

//scc
int label[MAXV + 5], lCnt;
stack<int> stk;
bool finished[MAXV + 5];
vector<vector<int>> SCC;
int sNum[MAXV + 5], sCnt;

//scc 그래프
vector<int> sAdj[MAXV + 5];
int indeg[MAXV + 5];
ll dist[MAXV + 5];

void scan(int cnt);
void multiCheck(map<string, int>::iterator& it, string s);
int DFS(int v);
void topological_sort();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(label, -1, sizeof(label));
	fill(dist, dist + MAXV + 5, sizeof(dist));

	//입력 및 그래프 형성
	int cnt; cin >> cnt; 
	scan(cnt);

	//scc 찾기: dfs 스패닝 트리
	for (int v = 1; v <= N; v++)
		if (label[v] == -1) DFS(v);

	//scc 그래프 형성
	for (int v = 1; v <= N; v++) {
		int sV = sNum[v];
		for (int next : adj[v]) {
			int sNext = sNum[next];
			if (sV == sNext) continue;
			sAdj[sV].push_back(sNext);
			indeg[sNext]++;
		}
	}

	//위상 정렬
	topological_sort();
	
	//출력
	cout << dist[en] << '\n';
	
	return 0;
}

void scan(int cnt) {
	N = 1;

	for (int i = 0; i < cnt; i++) {
		string s; cin >> s;
		map<string, int>::iterator v = mp.find(s);

		multiCheck(v, s);

		int x; cin >> x;
		while (x--) {
			cin >> s;
			map<string, int>::iterator u = mp.find(s);
			multiCheck(u, s);
			adj[u->second].push_back(v->second);
		}
	}
	
	string s; cin >> s;
	map<string, int>::iterator it = mp.find(s);
	multiCheck(it, s);
	en = it->second;
	
	N--;
}

void multiCheck(map<string, int>::iterator& it, string s) {
	if (it == mp.end()) {
		mp.insert({ s, N++ });
		it = mp.find(s);
	}
}

int DFS(int v) {
	label[v] = lCnt++;
	stk.push(v);

	int ret = label[v];
	for (int next : adj[v]) {
		if (label[next] == -1) ret = min(ret, DFS(next));
		else if (!finished[next]) ret = min(ret, label[next]);
	}

	if (ret == label[v]) {
		vector<int> vSCC;
		while (true) {
			int t = stk.top();
			stk.pop();

			vSCC.push_back(t);
			sNum[t] = sCnt;
			finished[t] = true;

			if (t == v) break;
		}

		SCC.push_back(vSCC);
		sCnt++;
	}

	return ret;
}

void topological_sort() {
	queue<int> q;

	for (int v = 1; v <= N; v++)
		dist[v] = 1;
	
	for (int sV = 0; sV < sCnt; sV++) {
		if (indeg[sV] == 0) {
			for (int v : SCC[sV]) q.push(v);
		}
	}

	while (!q.empty()) {
		int n = q.front();
		q.pop();
		
		for (int next : adj[n]) {
			if (sNum[n] == sNum[next]) continue;
			
			dist[next] += dist[n];

			int sV = sNum[n], sNext = sNum[next];
			if (--indeg[sNext] == 0) {
				for (int v : SCC[sNext]) q.push(v);
			}
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: scc + 위상 정렬
결정적 깨달음		: 큐를 SCC 단위로 돌리는 것이 아니라, 원래 그래프의 정점 단위로 돌린다. 돌리는 순서는 SCC 단위로 한다.
시간복잡도		: O(|V| + |E|)
오답 원인		: 1. 답이 지수적으로 증가할 수 있기 때문에, int형 범위를 넘어갈 수 있음
				  2.
*/////////////////////////////////////////////////////////////////////