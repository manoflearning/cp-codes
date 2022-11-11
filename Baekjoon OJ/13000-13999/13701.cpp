#include <bits/stdc++.h>
using namespace std;

bitset<33554432> bs;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (1) {
		int x; cin >> x;
		if (cin.eof()) break;

		if (bs[x]) continue;
		
		cout << x << ' ';
		bs[x] = 1;
	}

	return 0;
}