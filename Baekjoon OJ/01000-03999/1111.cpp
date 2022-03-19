#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
		
	if (n == 1) printf("A");
	else if (n == 2) {
		if (arr[0] == arr[1]) printf("%d", arr[0]);
		else printf("A");
	}
	else {
		if (arr[1] - arr[0] == 0) {
			bool check = true;
			for(int i=2; i<n; i++)
				if (arr[i] != arr[0]) {
					check = false;
					break;
				}

			if (check) printf("%d", arr[0]);
			else printf("B");
		}
		else {
			if ((arr[2] - arr[1]) % (arr[1] - arr[0] != 0)) printf("B");
			else {
				int a = (arr[2] - arr[1]) / (arr[1] - arr[0]);
				int b = arr[1] - arr[0] * a;

				bool check = true;
				for (int i = 2; i < n; i++)
					if (arr[i] != arr[i - 1] * a + b) {
						check = false;
						break;
					}

				if (check) printf("%d", arr[n - 1] * a + b);
				else printf("B");
			}
		}
	}

	return 0;
}
/*
문제 해법		: 
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 0으로 /나 %하면 런타임에러!!
				  2.
*/
///////////////////////////////////////////////////////////////////////
/*
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	vector<int> arr(n);

	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	vector<int> ans;

	for (int a = -200; a <= 200; a++) {
		for (int b = -200; b <= 200; b++) {
			bool check = true;

			for (int flag = 1; flag < n; flag++) {
				if (arr[flag] != arr[flag - 1] * a + b) {
					check = false;
					break;
				}
			}

			if (check) {
				int sam = arr[n - 1] * a + b;

				bool overlap = false;
				for(int i=ans.size() - 1; i>=0; i--)
					if (ans[i] == sam) {
						overlap = true;
						break;
					}

				if (!overlap) ans.push_back(sam);
			}
		}
	}

	if (ans.size() == 0) printf("B");
	else if (ans.size() >= 2) printf("A");
	else printf("%d", ans[0]);

	return 0;
}
*/
/*
문제 해법		: 완전 탐색(가능한 모든 a와 b를 탐색)
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 
				  2.
*/
///////////////////////////////////////////////////////////////////////
//도움용 코드
/*
#include <iostream>
using namespace std;

int x, a, b;

int main() {
	scanf("%d %d %d", &x, &a, &b);

	for (int i = 0; i < 5; i++) {
		printf("%d ", x);

		x = x * a + b;
	}

	return 0;
}
*/