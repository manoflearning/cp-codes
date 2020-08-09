#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 26;

vector<int> adj[MAXV + 5], indeg(MAXV + 5), node;
bool exist[MAXV + 5], isCycle, isMany;
string word[100], res;

void topological_sort();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int M;  cin >> M;

	for (int i = 0; i < M; i++) {
		cin >> word[i];
		for (int l = 0; l < word[i].size(); l++) {
			int v = word[i][l] - 'a';
			if (exist[v]) continue;
			exist[v] = true;
			node.push_back(v);
		}
	}

	for (int i = 0; i < M; i++) {
		for (int l = i + 1; l < M; l++) {
			string ustr = word[i], vstr = word[l];
			
			int len = min(ustr.size(), vstr.size());
			for (int j = 0; j < len; j++) {
				if (ustr[j] == vstr[j]) {
					if (j == len - 1 && ustr.size() > vstr.size()) isCycle = true;
					continue;
				}

				int u = ustr[j] - 'a', v = vstr[j] - 'a';

				bool already = false;
				for(int next : adj[u])
					if (next == v) {
						already = true;
						break;
					}

				if (!already) {
					adj[u].push_back(v);
					indeg[v]++;
				}
				
				break;
			}
		}
	}

	//위상 정렬
	topological_sort();

	if (isCycle) cout << "!";
	else if (isMany) cout << "?";
	else cout << res;

	return 0;
}

void topological_sort() {
	queue<int> q;

	for (int v : node)
		if (indeg[v] == 0) q.push(v);

	for (int i : node) {
		if (q.empty()) {
			isCycle = true;
			break;
		}
		if (q.size() > 1) isMany = true;

		int v = q.front();
		q.pop();

		res.push_back(v + 'a');

		for (int next : adj[v]) {
			indeg[next]--;
			if (indeg[next] == 0) q.push(next);
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 위상 정렬
결정적 깨달음		:
시간복잡도		: O(|V| + |E|)
오답 원인		: 1. 2 / ab / a와 같은 케이스를 처리하지 못함. 
				  2.
*/////////////////////////////////////////////////////////////////////