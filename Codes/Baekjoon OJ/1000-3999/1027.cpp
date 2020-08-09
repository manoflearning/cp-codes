#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> building;
vector<int> can_see;

int main() {
	scanf("%d", &n);

	building.resize(n);
	can_see.resize(n);

	for (int i = 0; i < n; i++)
		scanf("%d", &building[i]);

	for (int i = 0; i < n; i++) {
		for (int l = i + 1; l < n; l++) {
			bool check = true;

			for (int flag = i + 1; flag < l; flag++) {
				double len = ((double)building[i] * ((double)l - flag) + (double)building[l] * (flag - i)) / ((double)l - i);

				if (building[flag] >= len) {
					check = false;
					break;
				}
			}

			if (check) can_see[i]++, can_see[l]++;
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++)
		ans = max(ans, can_see[i]);

	printf("%d", ans);

	return 0;
}
/*
문제 해법		: 
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 
				  2.
*/
///////////////////////////////////////////////////////////////////////
//help code to solve a problem