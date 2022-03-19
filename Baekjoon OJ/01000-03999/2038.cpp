#include <iostream>
#define ll long long
using namespace std;

ll f[(int)1e7];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	ll n; cin >> n;

	if (n == 1) {
		cout << 1;
		return 0;
	}

	ll sum = 1;
	f[1] = 1;

	for (ll i = 2; ; i++) {
		f[i] = 1 + f[i - f[f[i - 1]]];

		sum += f[i];
		
		if (sum >= n) {
			cout << i;
			break;
		}
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 골롱 수열
결정적 깨달음		: x > 1일 때, 점화식은 f(n) = 1 + f(n - f(f(n - 1))) (출처: https://stackoverflow.com/questions/12786087/golombs-sequence)
시간복잡도		: 알 수 없음
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////