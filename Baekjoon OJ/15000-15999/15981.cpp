#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    int n; cin >> n;

    if (n == 3) {
        cout << n - 1 << '\n';
        for (int i = 2; i <= n; i++) {
            cout << 2 << ' ' << 1 << ' ' << i << '\n';
        }
    }
    else {
        cout << n - 2 << '\n';
        for (int i = 2; i <= n - 1; i++) {
            cout << 2 << ' ' << 1 << ' ' << i << '\n';
        }
    }
	
	return 0;
}