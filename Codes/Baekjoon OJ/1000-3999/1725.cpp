#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int n;
int histo[MAX];
int leftHisto[MAX], rightHisto[MAX];

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &histo[i]);

	for (int i = 0; i < n; i++)
		leftHisto[i] = -1, rightHisto[i] = n;

	stack<int> height;

	for (int i = 0; i < n; i++) {
		while (true) {
			if (height.empty()) break;
			else if (histo[i] > histo[height.top()]) {
				leftHisto[i] = height.top();
				break;
			}
			else if (histo[i] <= histo[height.top()]) {
				rightHisto[height.top()] = i;
				height.pop();
			}
		}
		
		height.push(i);
	}

	int ans = 0;
	for (int i = 0; i < n; i++)
		ans = max(ans, (rightHisto[i] - leftHisto[i] - 1) * histo[i]);

	printf("%d", ans);

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 스택의 활용
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////