#include <stdio.h>
#include <math.h>

int generator(int N) {
	int i, l, j;
	int m;
	int fN, gen, flag=0;
	
	for(m=1; N>pow(10, m); m++) {}
	gen=N;
	
	for(i=N-1; i>=0; i--) {
		fN=0;
		fN+=i;
		for(l=1; l<=m; l++)
			fN+=i%(int)pow(10, l)/(int)pow(10, l-1); //불필요한 연산 
		
		if(fN==N && i<gen)
			gen=i, flag++;
	}
	
	if(flag>0) return gen;
	else return 0;
}

int main (void) {
	int N;
	
	scanf("%d", &N);
	
	printf("%d", generator(N));
	
	return 0;
}