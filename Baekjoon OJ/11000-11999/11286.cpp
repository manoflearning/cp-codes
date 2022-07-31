#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

struct cmp {
	bool operator() (int a, int b) {
		if (fabs(a) != fabs(b)) return fabs(a) > fabs(b);
		return a > b;
	}
};

priority_queue<int, vector<int>, cmp> pq;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	while (N--) {
		int x; cin >> x;
		
		if (x == 0) {
			if (pq.empty()) cout << 0 << '\n';
			else {
				cout << pq.top() << '\n';
				pq.pop();
			}
		}
		else pq.push(x);
	}

	return 0;
}
/*//////////////////////////////////////////////////////////////////
문제 해법		: 우선순위 큐, 수학
결정적 깨달음		: 
시간복잡도		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////