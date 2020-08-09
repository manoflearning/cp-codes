#include <iostream>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	int win_a = 0, win_b = 0;
	for (int test = 0; test < t; test++) {
		int a, b;
		scanf("%d %d", &a, &b);

		if (a > b) win_a++;
		else if (a < b) win_b++;
	}
	
	printf("%d %d", win_a, win_b);

	return 0;
}
/*
문제 해법		: 
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////