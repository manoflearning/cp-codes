//앳코더 D번
/*#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };
const long double PI = 3.141592653589793238462643383279502884197;

const int MAX = 2 * 1e5;

int N, pCnt, psum[MAX + 5][3], invpsum[MAX + 5], dp[MAX + 5];
string X;

int f(int val);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	memset(dp, -1, sizeof(dp));

	cin >> N >> X;

	for (auto& c : X)
		if (c == '1') pCnt++;

	psum[N - 1][0] = (X[N - 1] - '0') % (pCnt - 1);
	psum[N - 1][1] = (X[N - 1] - '0') % pCnt;
	psum[N - 1][2] = (X[N - 1] - '0') % (pCnt + 1);

	for (int i = N - 2; i >= 0; i--) {
		psum[i][0] = (2 * psum[i + 1][0] + X[i] - '0') % (pCnt - 1);
		psum[i][1] = (2 * psum[i + 1][1] + X[i] - '0') % pCnt;
		psum[i][2] = (2 * psum[i + 1][2] + X[i] - '0') % (pCnt + 1);
	}

	

	for (int i = 0; i < N; i++) {
		int cnt = pCnt, val = 0;

		if (X[i] == '0') {
			cnt++;
			val = psum[0][2];
		}
		if (X[i] == '1') cnt--;
	}

	return 0;
}

int f(int val) {
	int& ret = dp[val];
	if (ret != -1) return ret;
	if (val == 0) return ret = 0;

	return ret = f(val % __builtin_popcount(val)) + 1;
}*/

//코포 D번
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };
const long double PI = 3.141592653589793238462643383279502884197;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n; cin >> n;

	vector<int> a(n);
	for (int& i : a) cin >> i;

	vector<int> b;
	for (int i = 0; i < a.size(); i += 2) b.push_back(a[i]);
	for (int i = 1; i < a.size(); i += 2) b.push_back(a[i]);

	ll ans = -1, sum = 0;
	for (int i = 0; i < (n + 1) / 2; i++) sum += b[i];
	
	ans = max(ans, sum);
	for (int L = 1; L != 0; L = (L + 1) % b.size()) {
		int R = (L + (n + 1) / 2 - 1) % b.size();
		if (R == b.size()) break;

		sum -= b[L - 1];
		sum += b[R];
		
		ans = max(ans, sum);
	}

	cout << ans;

	return 0;
}