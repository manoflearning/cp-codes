#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int MAX = 100000, MAXD = 18;

int n, flag;
vector<int> tree[MAX + 1];
int dp[MAX + 1][MAXD + 1];
//dp[a][b]�� ��� a�� ������ b�� ��, a�� ��Ʈ�� �ϴ� ����Ʈ���� �ּ� ���.

int dfs(int node, int last, int color);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dp, -1, sizeof(dp));

	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	//flag���� ���� �����ϸ� ��.
	for (flag = 1; (1 << (flag - 1)) < MAX; flag++);
	
	int ans = 1e9;
	for (int i = 1; i <= flag; i++) {
		ans = min(ans, dfs(1, 0, i));
	}

	cout << ans;

	return 0;
}

int dfs(int node, int last, int color) {
	int& ret = dp[node][color];
	if (ret != -1) return ret;

	ret = color;
	
	for (int i = 0; i < tree[node].size(); i++) {
		if (tree[node][i] == last) continue;

		int mn = 1e9;
		for (int l = 1; l <= flag; l++) {
			if (l == color) continue;
			mn = min(mn, dfs(tree[node][i], node, l));
		}
		ret += mn;
	}
	
	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: Ʈ�� dp
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////