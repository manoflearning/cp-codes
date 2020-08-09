#include <iostream>
using namespace std;

int main() {
	int s, k, h;
	scanf("%d %d %d", &s, &k, &h);

	if (s + k + h >= 100) printf("OK");
	else {
		if (s < k && s < h) printf("Soongsil");
		else if (k < s && k < h) printf("Korea");
		else printf("Hanyang");
	}

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