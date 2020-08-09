#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 100;

int N, LEN;
//arr2�� �Է����� �־����� �迭(arr1)�� ��� ���� �ٲ� ��.
int arr1[MAX + 5][MAX + 5], arr2[MAX + 5][MAX + 5];

void scan();
bool canGo(int arr[]);
int cal_len(int f, bool R, vector<bool>& ramp, int arr[]);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	//�Է�
	scan();

	//������ �� �ִ� ���� ���� ����
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (canGo(arr1[i])) ans++;
		if (canGo(arr2[i])) ans++;
	}

	//���
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
���� �ع�		: ����
������ ������		: 
�ð����⵵		: O(N^3)
���� ����		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////