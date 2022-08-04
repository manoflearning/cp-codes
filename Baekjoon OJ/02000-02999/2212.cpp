#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	vector<int> sen;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		sen.push_back(x);
	}

	sort(sen.begin(), sen.end());

	vector<int> len;
	for (int i = 1; i < sen.size(); i++) {
		len.push_back(sen[i] - sen[i - 1]);
	}

	sort(len.begin(), len.end());
	
	k = min(n - 1, k - 1);
	
	while (k--) {
		len.pop_back();
	}

	int ans = 0;
	for (int i = 0; i < len.size(); i++)
		ans += len[i];

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: �׸���
���� ���		:
������ ������		:
���� ����		: 1. k�� n - 1���� Ŭ ��츦 �������� ����
				  2.
*/////////////////////////////////////////////////////////////////////