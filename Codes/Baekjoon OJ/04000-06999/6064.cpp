#include <stdio.h>

int calendar_calculation(int M, int N, int x, int y) {
	int i;
	
	for(i=x; ; i+=M) {
		if(N==y) {
			if(i%N==0) return i;
		}
		else {
			if(i%N==y) return i;
		}
		
		if(i>M*N) return -1;
	}
}

int main (void) {
	int T;
	int M, N, x, y;
	int i;
	
	scanf("%d", &T);
	
	for(i=0; i<T; i++) {
		scanf("%d %d %d %d", &M, &N, &x, &y);
		
		printf("%d\n", calendar_calculation(M, N, x, y));
	}
	
	return 0;
}