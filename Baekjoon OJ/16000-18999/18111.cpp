#include <iostream>
using namespace std;

const int MAX = 500;
const int INF = 1e9;

int R, C, B;
int arr[MAX + 5][MAX + 5];

int timer(int h);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> R >> C >> B;

	for (int y = 1; y <= R; y++) {
		for (int x = 1; x <= C; x++) {
			cin >> arr[y][x];
		}
	}

	int anst = INF, ansh = 0;
	for (int i = 256; i >= 0; i--) {
		int t = timer(i);
		if (anst > t) {
			anst = t;
			ansh = i;
		}
	}

	cout << anst << ' ' << ansh << '\n';

	return 0;
}

int timer(int h) {
	int ret = 0, lb = B;

	for (int y = 1; y <= R; y++) {
		for (int x = 1; x <= C; x++) {
			if (arr[y][x] > h) {
				ret += 2 * (arr[y][x] - h);
				lb += arr[y][x] - h;
			}
			else if (arr[y][x] < h) {
				ret += h - arr[y][x];
				lb -= h - arr[y][x];
			}
		}
	}

	if (lb >= 0) return ret;
	else return INF;
}
/*//////////////////////////////////////////////////////////////////
���� �ع�		: ����, ����Ž��
������ ������		:
�ð����⵵		: O(NM)
���� ����		: 1.
				  2.
*///////////////////////////////////////////////////////////////////