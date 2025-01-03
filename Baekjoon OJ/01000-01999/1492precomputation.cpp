#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 1e9;
const int sq = 2e6;
const int MOD = 1e9 + 7;

ll sum[55][MAX / sq + 1];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	for (int i = 1; i <= MAX; i++) {
		ll x = i;
		for (int j = 1; j <= 50; j++) {
			sum[j][i / sq] = (sum[j][i / sq] + x) % MOD;
			x = (x * i) % MOD;
		}
    }

	cout << "{ \n";
	for (int i = 1; i <= 50; i++) {
		cout << "{ ";
		for (int j = 0; j <= MAX / sq; j++) {
			cout << sum[i][j];
			if (j != MAX / sq) cout << ", ";
		}
		cout << " }";
		if (i != 50) cout << ", \n";
	}
	cout << "\n}";
	

	return 0;
}