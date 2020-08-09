/*
문제 해법		: 완전 탐색
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 오버플로우
				  2. 기저조건의 확인법이 잘못됨.
*/
/*
#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int n;
int W[10][10];
vector<int> path;
vector<bool> visited(10, false);

int shortestPath();

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int l = 0; l < n; l++) {
			scanf("%d", &W[i][l]);
		}

	path.push_back(0);
	printf("%d", shortestPath());

	return 0;
}

int shortestPath() {
	//기저조건 : 모든 도시를 방문함
	if (path.size() == n)
		if (W[path.back()][0] != 0) return W[path.back()][0];
		else return 1000000000;
	//
	int ret = 1000000000;
	for (int i = 1; i < n; i++) {
		if (!visited[i] && W[path.back()][i] != 0) {
			int sam = W[path.back()][i];

			visited[i] = true;
			path.push_back(i);

			sam += shortestPath();

			visited[i] = false;
			path.pop_back();

			ret = min(ret, sam);
		}
	}

	return ret;
}
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n;
int W[10][10];
vector<bool> everBeen(10, false);

int tsp(int lastCity);

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		for (int l = 0; l < n; l++) {
			scanf("%d", &W[i][l]);
		}

	everBeen[0] = true;
	int res = tsp(0);

	printf("%d", res);

	return 0;
}

int tsp(int lastCity) {
	int res = 1000000000;
	bool truism = true;
	//방문하지 않은 도시를 방문하기
	for (int i = 1; i < n; i++) {
		if (everBeen[i] == false) {
			truism = false; //방문을 하지 않은 도시가 하나 이상 있음

			if (W[lastCity][i] != 0) {
				everBeen[i] = true;

				int sam = tsp(i);
				sam += W[lastCity][i];

				everBeen[i] = false;

				res = min(res, sam);
			}
		}
	}
	//기저조건 : 모든 도시를 방문함
	if (truism)
		if (W[lastCity][0] != 0) return W[lastCity][0];
		else return 1000000000;
	//
	return res;
}
