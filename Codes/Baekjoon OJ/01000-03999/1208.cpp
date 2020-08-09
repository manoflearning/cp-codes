#include <iostream>
#include <vector>
#include <set>
using namespace std;
#define ll long long

const int MAX = 20 * 1e5;

int N, S;
int mid;
vector<int> arr;
ll u[2 * MAX + 5], v[2 * MAX + 5];

void pick(int x, int sum);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> S;

	arr.resize(N);
	for (int& i : arr) cin >> i;

	if (N == 1) {
		cout << (S == arr[0] ? 1 : 0);
		return 0;
	}

	mid = (0 + N - 1) / 2;
	
	pick(0, 0);
	pick(mid + 1, 0);

	ll cnt = (S == 0 ? -1 : 0);
	for (int L = -MAX; L <= MAX; L++) {
		int R = S - L;
		if (R < -MAX || MAX < R) continue;
		cnt += u[L + MAX] * v[R + MAX];
	}

	cout << cnt;

	return 0;
}

void pick(int x, int sum) {
	if (x == mid || x == N - 1) {
		if (x == mid) {
			u[sum + MAX]++;
			u[sum + arr[x] + MAX]++;
		}
		else {
			v[sum + MAX]++;
			v[sum + arr[x] + MAX]++;
		}
		return;
	}

	pick(x + 1, sum);
	pick(x + 1, sum + arr[x]);
}