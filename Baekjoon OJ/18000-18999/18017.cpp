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
���� �ع�		: ��뼺�̷�
���� ���		:
������ ������	:
���� ����		: 1. 
				  2.
*/