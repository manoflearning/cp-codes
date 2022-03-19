#include <iostream>

int intersection_point_count(int n);

int main(void) {
	int n;
	
	std::cin>>n;
	
	std::cout<<intersection_point_count(n);
	
	return 0;
}

//교차점 구하기 방식 1 
int intersection_point_count(int n) {
	int o_count=0;
	
	for(int i=1; i<=n-3; i++) {
		o_count += i * (n-2-i);
	}
	
	return o_count * n / 4;
}