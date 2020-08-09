#include <iostream>
#include <queue>
#define ll long long
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		priority_queue<ll, vector<ll>, greater<ll>> pq;

		int K; cin >> K;

		for (int i = 0; i < K; i++) {
			int x; cin >> x;
			pq.push(x);
		}

		ll ans = 0;
		for (int i = 0; i < K - 1; i++) {
			ll sum = pq.top();
			pq.pop();
			sum += pq.top();
			pq.pop();

			pq.push(sum);
			ans += sum;
		}

		cout << ans << '\n';
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: �켱���� ť
������ ������		:
�ð����⵵		: O(KlgK)
���� ����		: 1. int�� �����÷ο�
				  2.
*/////////////////////////////////////////////////////////////////////