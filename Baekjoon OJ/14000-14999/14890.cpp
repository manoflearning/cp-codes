#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 100;

int N, LEN;
//arr2는 입력으로 주어지는 배열(arr1)의 행과 열을 바꾼 것.
int arr1[MAX + 5][MAX + 5], arr2[MAX + 5][MAX + 5];

void scan();
bool canGo(int arr[]);
int cal_len(int f, bool R, vector<bool>& ramp, int arr[]);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	//입력
	scan();

	//지나갈 수 있는 길의 개수 세기
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (canGo(arr1[i])) ans++;
		if (canGo(arr2[i])) ans++;
	}

	//출력
	cout << ans << endl;

	return 0;
}

void scan() {
	cin >> N >> LEN;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> arr1[y][x];
			arr2[x][y] = arr1[y][x];
		}
	}
}

bool canGo(int arr[]) {
	vector<bool> ramp(N + 1);
	for (int i = 2; i <= N; i++) {
		int h = fabs(arr[i - 1] - arr[i]);

		if (h >= 2) return false;
		else if (h == 1) {
			if (arr[i - 1] < arr[i]) {
				int len = cal_len(i - 1, false, ramp, arr);

				if (len >= LEN) {
					for (int l = i - 1; l > (i - 1) - LEN; l--)
						ramp[l] = true;
				}
				else return false;
			}
			else {
				int len = cal_len(i, true, ramp, arr);

				if (len >= LEN) {
					for (int l = i; l < i + LEN; l++)
						ramp[l] = true;
				}
				else return false;
			}
		}
	}

	return true;
}

int cal_len(int f, bool R, vector<bool>& ramp, int arr[]) {
	if (ramp[f]) return 0;
	
	if (R) {
		for (int i = f + 1; i <= N; i++) {
			if (arr[f] != arr[i] || ramp[i]) return i - f;
		}
		return N - f + 1;
	}
	else {
		for (int i = f - 1; i >= 1; i--) {
			if (arr[f] != arr[i] || ramp[i]) return f - i;
		}
		return f;
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 구현
결정적 깨달음		: 
시간복잡도		: O(N^3)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////