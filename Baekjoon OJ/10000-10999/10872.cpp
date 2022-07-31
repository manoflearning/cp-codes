#include <stdio.h>

int i;

int factorial(int N) {
	/*if(N==1) return 1;
	return factorial(N-1)*N;*/
	//백준에서 시간초과
	
	int result=1;
	
	for(i=1; i<=N; i++)
		result*=i;
		
	return result;
}

int main (void) {
	int N;
	
	scanf("%d", &N);
	
	printf("%d", factorial(N));
	
	return 0;
}