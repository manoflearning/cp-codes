#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

const int MAXV = 1e3;

int N, M, V = 1;
map<vector<string>, int> mp;
map<int, vector<string>> rev_mp;
int adj[MAXV + 5][MAXV + 5], indeg[MAXV + 5], outdeg[MAXV + 5];
vector<int> res;

void scan();
void multi_check(map<vector<string>, int>::iterator& it, vector<string>& s);
void DFS(int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	//해싱, 그래프 구현
	scan();

	//오일러 경로 찾기
	for (int v = 1; v <= V; v++) {
		if (outdeg[v] == indeg[v] + 1) {
			DFS(v);
			break;
		}
	}

	//오일러 회로 찾기
	if (res.empty()) DFS(1);

	//출력
	map<int, vector<string>>::iterator it;
	for (int i = res.size() - 1; i >= 1; i--) {
		it = rev_mp.find(res[i]);
		cout << it->second[0] << ' ';
	}
	it = rev_mp.find(res[0]);
	for (int i = 0; i < it->second.size(); i++)
		cout << it->second[i] << ' ';

	return 0;
}

void scan() {
	for (int i = 0; i < N - M + 1; i++) {
		vector<string> s1, s2;
		string x;

		cin >> x; s1.push_back(x);
		for (int l = 1; l < M - 1; l++) {
			cin >> x;
			s1.push_back(x);
			s2.push_back(x);
		}
		cin >> x; s2.push_back(x);

		map<vector<string>, int>::iterator u = mp.find(s1);
		map<vector<string>, int>::iterator v = mp.find(s2);
		multi_check(u, s1);
		multi_check(v, s2);
		
		adj[u->second][v->second]++;
		indeg[v->second]++, outdeg[u->second]++;
	}
	V--;
}

void multi_check(map<vector<string>, int>::iterator& it, vector<string>& s) {
	if (it == mp.end()) {
		mp.insert({ s, V });
		rev_mp.insert({ V++, s });
		it = mp.find(s);
	}
}

void DFS(int v) {
	for (int next = 1; next <= V; next++) {
		if (adj[v][next]) {
			adj[v][next]--;
			DFS(next);
		}
	}
	res.push_back(v);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 오일러 경로
결정적 깨달음		: 
시간복잡도		: O(|V|^2)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////