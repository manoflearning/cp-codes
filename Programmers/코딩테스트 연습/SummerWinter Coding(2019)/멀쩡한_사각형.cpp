using namespace std;

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

long long solution(int w, int h) {
    long long W = w, H = h;
    
    return W * H - (W + H - gcd(W, H));
}