#include <iostream>
using namespace std;

int main() {
	int tri[3];

	for (int i = 0; i < 3; i++)
		scanf("%d", &tri[i]);

	if (tri[0] + tri[1] + tri[2] != 180) printf("Error");
	else if (tri[0] == tri[1] && tri[1] == tri[2]) printf("Equilateral");
	else if (tri[0] == tri[1] || tri[1] == tri[2] || tri[0] == tri[2]) printf("Isosceles");
	else printf("Scalene");

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