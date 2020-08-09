#include <iostream>
#define ll long long
using namespace std;

ll GCD(ll a, ll b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	ll A, B;
	cin >> A >> B;

	ll gcd = GCD(A, B);

	string s(gcd, '1');
	cout << s << endl;

	return 0;
}

ll GCD(ll a, ll b) {
	if (b == 0) return a;
	else return GCD(b, a % b);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 수학
결정적 깨달음		: 정답은 입력으로 주어지는 두 수의 최대공약수만큼의 자리수를 가진 1로 이루어진 수이다.
시간복잡도		:
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////