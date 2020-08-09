#include <iostream>
#define ll long long
using namespace std;

ll A, C;

ll f(int x); //f(x) := A^x mod C

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int B;
	cin >> A >> B >> C;

	cout << f(B) << '\n';

	return 0;
}

ll f(int x) {
	if (x == 1) return A % C;
	ll prv = f(x >> 1);
	return (prv * prv % C) * (x % 2 ? A : 1) % C;
}