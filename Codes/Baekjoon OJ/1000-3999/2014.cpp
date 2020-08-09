#include <iostream>
#include <queue>
#include <climits>
#define ll long long
using namespace std;

struct bb {
	int x;
	int fg;
};

struct cmp {
	bool operator() (bb a, bb b) {
		return a.x > b.x;
	}
};

int k, n;
int arr[100];
priority_queue<bb, vector<bb>, cmp> pq;

int main() {
	cin >> k >> n;

	for (int i = 0; i < k; i++) {
		cin >> arr[i];
		pq.push({ arr[i], i });
	}
		
	for (int i = 1; i < n; i++) {
		for (int l = pq.top().fg; l < k; l++) {
			if ((ll)pq.top().x * arr[l] > INT_MAX) break;

			pq.push({ pq.top().x * arr[l], l });
		}
		
		pq.pop();
	}

	cout << pq.top().x;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 우선순위 큐
접근 방식		: 우선순위 큐에서 pop되는 숫자들은 무조건 오름차순 순으로 출력된다. 거기다 모든 경우의 수를 고려한다.
결정적 깨달음		:  
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////