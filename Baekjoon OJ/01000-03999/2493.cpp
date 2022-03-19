#include <iostream>
#include <stack>
using namespace std;

int tower[500000];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &tower[i]);

	stack<int> tallTower;
	for (int i = 0; i < n; i++) {
		while (true) {
			if (tallTower.empty()) {
				printf("0 ");
				tallTower.push(i);
				break;
			}
			else if (tower[tallTower.top()] < tower[i]) tallTower.pop();
			else {
				printf("%d ", tallTower.top() + 1);
				tallTower.push(i);
				break;
			}
		}
	}

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 스택의 활용. 히스토그램의 스택을 활용한 풀이와 비슷한 접근 방식. 만약 스택의 탑이 비교 대상인 탑보다 같거나 크다면 출력, 작다면 pop연산.
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////