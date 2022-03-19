#include <iostream>
#include <cmath>

const double C = 299792458.0;

int main() {
	double A, B;

	scanf("%lf %lf", &A, &B);

	printf("%.2lf", (A + B) / (1 + A * B / pow(C, 2)));

	return 0;
}

/*
문제 해법		: 상대성이론
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 
				  2.
*/