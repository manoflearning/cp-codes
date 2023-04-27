#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int M, N;
	cin >> M >> N;
	for (int i = max(M, 2); i <= N; i++) {
		int isPrime = 1;
		for (int j = 2; j <= sqrt(i); j++) {
			if (i % j == 0) { isPrime = 0; break; }
		}
		if (isPrime) cout << i << '\n';
	}
}