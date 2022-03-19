#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int arr[20];
	for (int i = 0; i < 20; i++)
		arr[i] = i + 1;

	for (int i = 0; i < 10; i++) {
		int start, end;
		scanf("%d %d", &start, &end);

		start--, end--;

		for (int l = start; l <= (start + end) / 2; l++)
			swap(arr[l], arr[start + end - l]);
	}

	for (int i = 0; i < 20; i++)
		printf("%d ", arr[i]);

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