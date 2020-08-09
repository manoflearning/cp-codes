#include <iostream>

#define gauss(x) (x)*(x+1)/2

int exactly_three(int K);

int main() {
	int N;
	
	std::cin>>N;
	
	for(int i=0; i<N; i++) {
		int K;
		std::cin>>K;
		
		std::cout<<exactly_three(K)<<'\n';
	}
	
	return 0;
}

int exactly_three(int K) {
	int mn=2;
	
	for(int i=1; ; i++)
		if(gauss(i)>=K) {
			mn = i-1;
			break;
		}

	for(int i=1; i<=mn; i++)
		for(int l=1; l<=mn; l++)
			for(int j=1; j<=mn; j++) {
				if(gauss(i) + gauss(l) + gauss(j) == K)
					return 1;
			}
			
	return 0;
}
