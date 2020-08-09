#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXV = 1e5;

int N, label[MAXV + 5], labelCnt = 1;
int SCCnum[MAXV + 5], SCCcnt = 1, indeg[MAXV + 5];
vector<int> adj[MAXV + 5];
stack<int> S;
bool finished[MAXV + 5];

int DFS(int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		labelCnt = SCCcnt = 1;
		memset(label, 0, sizeof(label));
		memset(SCCnum, 0, sizeof(SCCnum));
		memset(finished, 0, sizeof(finished));
		memset(indeg, 0, sizeof(indeg));
		for (int i = 0; i < MAXV + 5; i++)
			adj[i].clear();

		//�׽�Ʈ���̽� ����
		int M;
		cin >> N >> M;

		for (int i = 0; i < M; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
		}

		//dfs ���д� Ʈ��
		for (int v = 1; v <= N; v++)
			if (label[v] == 0) DFS(v);
		
		//�� SCC�� �������� �ϰ�, SCC���� �����ϴ� ������ �������� �� �׷����� indegree ���� ����
		for (int v = 1; v <= N; v++) {
			for (int next : adj[v]) {
				if (SCCnum[v] == SCCnum[next]) continue;
				indeg[SCCnum[next]]++;
				//cout << v << ' ' << next << ' ' << SCCnum[next] << '\n';
			}
		}
		
		int ans = 0;
		for (int v = 1; v <= SCCcnt - 1; v++)
			if (indeg[v] == 0) ans++;
		cout << ans << '\n';
	}

	return 0;
}

int DFS(int v) {
	//�󺧸�. ���� �湮�� �����ϼ��� ���ڰ� ����.
	label[v] = labelCnt++;
	S.push(v);

	int ret = label[v];
	for (int next : adj[v]) {
		if (label[next] == 0) ret = min(ret, DFS(next));
		else if (!finished[next]) ret = min(ret, label[next]);
	}

	if (ret == label[v]) {
		while (true) {
			int t = S.top();
			S.pop();

			SCCnum[t] = SCCcnt;
			finished[t] = true;

			if (t == v) break;
		}

		SCCcnt++;
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ���� ���� ���
������ ������		: indegree�� 0�� SCC�� ������ ����.
�ð����⵵		: O(|V| + |E|)
���� ����		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////