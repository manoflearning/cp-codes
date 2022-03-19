#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> arr;
bool dp[1005][505][505]/*, visited[1005][505][505]*/;

//[0, x] 범위의 임의의 cnt개의 수들의 합을 S라 할 때, (S mod N == left)를 만족하는 경우가 있는가?
//bool f(int x, int cnt, int left);
void print(int x, int cnt, int left);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	arr.resize(2 * N - 1);
	for (int& i : arr) cin >> i;

	/*for (int i = N - 1; i < 2 * N - 1; i++) {
		if (f(i, N, 0)) {
			print(i, N, 0);
			return 0;
		}
	}*/

	//base case
	for (int x = 0; x < arr.size(); x++) {
		for (int i = 0; i <= x; i++) {
			dp[x][1][arr[i]] = true;

			if (1 == N && arr[i] == 0) {
				print(x, 1, arr[i]);
				return 0;
			}
		}
	}
	
	for (int x = 1; x < arr.size(); x++) {
		for (int cnt = 2; cnt <= N; cnt++) {
			for (int left = 0; left < N; left++) {
				int nleft = (left - arr[x] + N) % N;
				dp[x][cnt][left] = dp[x - 1][cnt - 1][nleft] || dp[x - 1][cnt][left];

				if (cnt == N && left == 0 && dp[x][cnt][left]) {
					print(x, cnt, left);
					return 0;
				}
			}
		}
	}

	cout << -1 << '\n';

	return 0;
}

/*bool f(int x, int cnt, int left) {
	if (cnt == 0) return left == 0;
	if (x < 0 || x + 1 < cnt) return false;

	bool& ret = dp[x][cnt][left];
	if (visited[x][cnt][left]) return ret;
	visited[x][cnt][left] = true;

	int nleft = (left - arr[x] + N) % N;
	return ret = f(x - 1, cnt - 1, nleft) || f(x - 1, cnt, left);
}*/

void print(int x, int cnt, int left) {
	int nleft = (left - arr[x] + N) % N;

	if (cnt == 1) {
		if (left == arr[x]) cout << arr[x] << ' ';
		else print(x - 1, cnt, left);
	}
	else if (dp[x - 1][cnt - 1][nleft]) {
		cout << arr[x] << ' ';
		print(x - 1, cnt - 1, nleft);
	}
	else print(x - 1, cnt, left);
}