#include <iostream>
using namespace std;

int main() {
	int v;
	scanf("%d", &v);

	int vote_a = 0, vote_b = 0;
	for (int i = 0; i < v; i++) {
		char vote;
		scanf(" %c", &vote);

		if (vote == 'A') vote_a++;
		else vote_b++;
	}

	if (vote_a > vote_b) printf("A");
	else if (vote_a < vote_b) printf("B");
	else printf("Tie");
	
	return 0;
}
/*
���� �ع�		: 
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////