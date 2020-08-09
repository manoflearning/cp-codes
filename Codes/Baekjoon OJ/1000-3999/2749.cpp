#include <iostream>
#include <vector>
#define ll long long
#define vvl vector<vector<ll>>
using namespace std;

const int MOD = 1e6;

vvl arr;

vvl F(ll x); //F(x)는 x번째 피보나치 수
vvl mul(vvl& a, vvl& b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	arr.resize(2, vector<ll>(2));
	arr[0][0] = arr[0][1] = arr[1][0] = 1;
	arr[1][1] = 0;

	ll N; cin >> N;

	if (N <= 2) {
		if (N == 0) cout << 0 << '\n';
		else cout << 1 << '\n';
		return 0;
	}

	vvl ans = F(N - 2);
	cout << (ans[0][0] + ans[1][0]) % MOD << '\n';

	return 0;
}

vvl F(ll x) {
	if (x == 1) return arr;
	vvl prv = F(x >> 1);
	vvl ret = mul(prv, prv);
	if (x & 1) ret = mul(ret, arr);
	return ret;
}

vvl mul(vvl& a, vvl& b) {
	vvl ret(2, vector<ll>(2));
	for (int i = 0; i < 2; i++) {
		for (int l = 0; l < 2; l++) {
			for (int k = 0; k < 2; k++) {
				ret[i][l] = (ret[i][l] + a[i][k] * b[k][l]) % MOD;
			}
		}
	}
	return ret;
}