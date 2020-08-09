#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 402000;

int N, arr[MAX + 5], last;
bool visited1[MAX + 5], visited2[MAX + 5];

bool sequencing(bool visited[]);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	//좌측 수열
	if (!sequencing(visited1)) {
		cout << "No";
		return 0;
	}
	
	//우측 수열
	memcpy(visited2, visited1, sizeof(visited1));
	visited1[last] = false;
	
	sequencing(visited1);
	sequencing(visited2);
	
	//
	bool Yes1 = true, Yes2 = true;
	for (int i = 0; i < N; i++) {
		if (!visited1[i]) Yes1 = false;
		if (!visited2[i]) Yes2 = false;
	}
		
	if (Yes1 || Yes2) cout << "Yes";
	else cout << "No";
	
	return 0;
}

bool sequencing(bool visited[]) {
	int d = -1, flag = 0;

	//등차 결정
	visited[0] = true;

	for (int i = 1; i < N; i++) {
		if (!visited[i]) {
			d = arr[i] - arr[0];
			flag = i;
			visited[i] = true;
			break;
		}
	}

	//등차가 0일 경우
	if (d == 0) return false;
	//등차가 -1일 경우
	if (d == -1) return true;

	//
	for (int i = flag + 1; i < N; i++) {
		if (!visited[i] && arr[i] - arr[flag] == d) {
			flag = i;
			visited[i] = true;
		}
	}

	last = flag;

	return true;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
접근 방식		:
결정적 깨달음		: O(nlgn)
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////