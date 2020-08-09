#include <iostream>
using namespace std;

const int MAX = 100;

int pic[MAX + 1], history[MAX + 1];
bool recommand[MAX + 1];
int Count;

int main() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int sam;
		cin >> sam;

		if (!recommand[sam]) {
			if (Count == n) {
				int min = 1001, flag;
				for (int l = 1; l <= MAX; l++) {
					if (recommand[l]) {
						if (pic[l] == min && history[l] < history[flag]) flag = l;
						else if (pic[l] < min) min = pic[l], flag = l;
					}
				}

				pic[flag] = 0, recommand[flag] = false;
				Count--;
			}

			history[sam] = i;

			pic[sam]++, recommand[sam] = true;
			Count++;
		}
		else pic[sam]++;
	}

	for (int i = 1; i <= MAX; i++)
		if (recommand[i]) cout << i << ' ';

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 배열의 활용, 구현
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 추천 받은 횟수가 가장 적은 학생이 두 명 이상일 경우를 고려하지 않음
				  2. 
*///////////////////////////////////////////////////////////////////////