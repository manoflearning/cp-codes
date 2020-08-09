#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char possible[1001];
	char hospital[1001];

	scanf("%s %s", possible, hospital);

	if (strlen(possible) >= strlen(hospital)) printf("go");
	else printf("no");

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