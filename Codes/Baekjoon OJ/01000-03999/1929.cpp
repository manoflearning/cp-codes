#include <stdio.h>

void find_sosu(int M, int N) {
	int arr[2000001];
	int i, l;
	
	for(i=2; i<=N; i++)
		arr[i]=1;
		
	for(i=2; i*i<=N; i++)
		if(arr[i])
			for(l=2*i; l<=N; l+=i)
				arr[l]=0;
		
	for(i=M; i<=N; i++)
		if(arr[i])
			printf("%d\n", i);
}

int main (void) {
	int M, N;
	
	scanf("%d %d", &M, &N);
	
	find_sosu(M, N);
	
	return 0;
}
