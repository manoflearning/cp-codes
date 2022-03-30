#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

ll N, k;

ll bSearch(ll L, ll R);
ll f(ll x); //f(x)�� x���� �۰ų� ���� �迭 A�� ������ ����

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> k;

	cout << bSearch(1, N * N) << '\n';

	return 0;
}

ll bSearch(ll L, ll R) {
	while (L < R) {
		ll mid = (L + R) / 2;

		if (k <= f(mid)) R = mid;
		else L = mid + 1;
	}
	return L;
}

ll f(ll x) {
	ll ret = 0;
	for (int i = 1; i <= N; i++) {
		ret += min(N, x / i);
	}
	return ret;
}