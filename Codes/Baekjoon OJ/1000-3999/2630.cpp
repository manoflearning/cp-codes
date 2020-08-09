#include <iostream>
using namespace std;

const int MAX = 128;

int paper[MAX][MAX];
int count01[2];

void paper_counter(int start_y, int start_x, int size);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int n;
	cin >> n;

	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			cin >> paper[y][x];
		}

	paper_counter(0, 0, n);

	cout << count01[0] << '\n' << count01[1];

	return 0;
}

void paper_counter(int start_y, int start_x, int size) {
	bool check = true;
	for (int y = start_y; y < start_y + size; y++) {
		for (int x = start_x; x < start_x + size; x++) {
			if (paper[y][x] != paper[start_y][start_x]) {
				check = false;
				
				y = start_y + size, x = start_x + size;
				break;
			}
		}
	}

	if (check) count01[paper[start_y][start_x]]++;
	else {
		paper_counter(start_y, start_x, size / 2);
		paper_counter(start_y + size / 2, start_x, size / 2);
		paper_counter(start_y, start_x + size / 2, size / 2);
		paper_counter(start_y + size / 2, start_x + size / 2, size / 2);
	}
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 분할정복 알고리즘의 활용. 주어진 종이를 자르지 않아도 된다면 개수 세기, 잘라야 한다면 4분할해서 재귀.
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////