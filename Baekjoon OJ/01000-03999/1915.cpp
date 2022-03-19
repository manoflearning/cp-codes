#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1e3;

int N, M;
bool arr[MAX + 5][MAX + 5];
int dpW[MAX + 5][MAX + 5], dpH[MAX + 5][MAX + 5], dpA[MAX + 5][MAX + 5];

void scan();
void find_WnH();
int find_area();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	scan();

	find_WnH();
	
	int ans = find_area();
	cout << ans;

	return 0;
}

void scan() {
	cin >> N >> M;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			char n;  cin >> n;
			
			if (n == '1') {
				dpA[y][x] = 1;
				arr[y][x] = true;
			}
		}
	}
}

void find_WnH() {
	//가로 구하기
	for (int y = 1; y <= N; y++) {
		int len = 0;
		for (int x = 1; x <= M; x++) {
			if (arr[y][x]) {
				len++;
				dpW[y][x] = len;
			}
			else len = 0;
		}
	}

	//세로 구하기
	for (int x = 1; x <= M; x++) {
		int len = 0;
		for (int y = 1; y <= N; y++) {
			if (arr[y][x]) {
				len++;
				dpH[y][x] = len;
			}
			else len = 0;
		}
	}
}

int find_area() {
	int ret = 0;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			if (arr[y][x]) {
				dpA[y][x] = max(dpA[y][x], min({ dpW[y][x - 1], dpH[y - 1][x], dpA[y - 1][x - 1] }) + 1);
				ret = max(ret, dpA[y][x]);
			}
		}
	}

	return ret * ret;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 다이나믹 프로그래밍
결정적 깨달음		:
시간복잡도		: O(NM)
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////