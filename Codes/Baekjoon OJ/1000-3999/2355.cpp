#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	long long a, b;
	scanf("%lld %lld", &a, &b);

	if (a > b) swap(a, b);
	
	/* long long 형으로도 오버플로우!!
	long long n = b - a;
	long long ans = a * (n + 1) + n * (n + 1) / 2;
	*/
	long long ans = (a + b) * (b - a + 1) / 2;
	printf("%lld", ans);

	return 0;
}