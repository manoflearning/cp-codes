#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

ll L, P, V;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	for (int test = 1; ; test++) {
		cin >> L >> P >> V;

		if (L == 0) break;

		ll ans = (V / P) * L + min((V % P), L);
		cout << "Case " << test << ": " << ans << '\n';
	}

	return 0;
}