/*
문제 해법		: 완전 탐색
접근 방식		: 
결정적 깨달음	: 
오답 원인		: 1. 
				  2.
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int n, m;
vector< vector<int> > city;
//치킨집의 수
int chiCount;
//치킨 거리의 최솟값
int ans = INT_MAX;

//폐업할 치킨집 결정
void chooseChicken(int count = 0, int f1 = 0, int f2 = -1);
//폐업할 치킨집이 결정된 도시의 치킨 거리 계산
void calMin();
//하나의 집을 기준으로 치킨 거리 계산
int findNearChicken(int y, int x);

int main() {
	scanf("%d %d", &n, &m);

	city.resize(n, vector<int>(n));

	for (int i = 0; i < n; i++)
		for (int l = 0; l < n; l++) {
			cin >> city[i][l];

			if (city[i][l] == 2) chiCount++;
		}

	chooseChicken();

	printf("%d", ans);

	return 0;
}

//폐업할 치킨집 결정
void chooseChicken(int count, int f1, int f2) {
	if (count == chiCount - m) {
		calMin();
	}
	
	for(int l = f2 + 1; l < n; l++)
		if (city[f1][l] == 2) {
			city[f1][l] = 0;
			chooseChicken(count + 1, f1, l);
			city[f1][l] = 2;
		}
	for (int i = f1 + 1; i < n; i++)
		for (int l = 0; l < n; l++) {
			if (city[i][l] == 2) {
				city[i][l] = 0;
				chooseChicken(count + 1, i, l);
				city[i][l] = 2;
			}
		}
}

//폐업할 치킨집이 결정된 도시의 치킨 거리 계산
void calMin() {
	int Sans = 0;
	for (int i = 0; i < n; i++)
		for (int l = 0; l < n; l++) {
			if (city[i][l] == 1) 
				Sans += findNearChicken(i, l);
		}

	ans = min(ans, Sans);
}
//하나의 집을 기준으로 치킨 거리 계산
int findNearChicken(int y, int x) {
	int dista = INT_MAX;
	for (int i = 0; i < n; i++)
		for (int l = 0; l < n; l++) {
			if (city[i][l] == 2)
				dista = min(dista, abs(i - y) + abs(l - x));
		}

	return dista;
}



