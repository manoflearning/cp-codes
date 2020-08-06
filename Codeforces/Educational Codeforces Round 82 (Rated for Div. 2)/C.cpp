#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

char s[201];
vector<int> graph[26];
vector<int> visited(26);
vector<char> ans;

bool find(int x, int f);
bool dfs(int x, int last);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;

	for (int test = 0; test < t; test++) {
		//reset
		for (int i = 0; i < 26; i++) {
			graph[i].clear();
			visited[i] = false;
		}
		ans.clear();
		//입력 및 중복 없는 무향 그래프 구현
		cin >> s;

		int len = strlen(s);

		if (len == 1) {
			cout << "YES\n";
			for (int i = 0; i < 26; i++) {
				char x = i + 'a';
				cout << x;
			}
			cout << '\n';
		}
		else {
			for (int i = 0; i < len - 1; i++) {
				if (!find(s[i] - 'a', s[i + 1] - 'a')) {
					graph[s[i] - 'a'].push_back(s[i + 1] - 'a');
					graph[s[i + 1] - 'a'].push_back(s[i] - 'a');
				}
			}
			//무향 그래프에서 하나의 노드와만 연결된 노드 찾기
			int flag;
			bool NO = true;
			for (int i = 0; i < 26; i++) {
				if (graph[i].size() == 1) {
					flag = i;
					NO = false;
				}
			}
			//
			if (NO) cout << "NO\n";
			else {
				if (dfs(flag, -1)) {
					cout << "YES\n";
					for (int i = 0; i < ans.size(); i++)
						cout << ans[i];
					for (int i = 0; i < 26; i++)
						if (!visited[i]) {
							char x = i + 'a';
							cout << x;
						}
					cout << '\n';
				}
				else cout << "NO\n";
			}
		}
	}

	return 0;
}

bool find(int x, int f) {
	for (int i = 0; i < graph[x].size(); i++)
		if (graph[x][i] == f) return true;
	return false;
}

bool dfs(int x, int last) {
	//base case
	if (graph[x].size() > 2) return false;
	if (visited[x]) return false;

	visited[x] = true;
	ans.push_back(x + 'a');
	
	bool YES = true;
	for (int i = 0; i < graph[x].size(); i++) {
		if (graph[x][i] == last) continue;
		YES = dfs(graph[x][i], x);
	}
	return YES;
}