#include <iostream>
#define ll long long
using namespace std;

const ll r = 31, M = 1234567891;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;
	string s; cin >> s;

	ll ans = 0;
	for (ll i = 0, x = 1; i < N; i++, x *= r) {
		x %= M;
		
		ans += (s[i] - 'a' + 1) * x;
		ans %= M;
	}
	
	cout << ans << '\n';

	return 0;
}
/*//////////////////////////////////////////////////////////////////
문제 해법		: 
결정적 깨달음		:
시간복잡도		: O(n)
오답 원인		: 1.
				  2.
*///////////////////////////////////////////////////////////////////