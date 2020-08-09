#include <iostream>
#include <vector>
using namespace std;

const int MAX = 300000;

int n, l;
vector<int> set(MAX + 1, -1);
int active[MAX + 1];
bool visited[MAX + 1];

int find(int x);
void merge(int a, int b);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//
	cin >> n >> l;

	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		
		if (!visited[a]) {
			active[find(b)]++;
			cout << "LADICA\n";
		}
		else if (!visited[b]) {
			active[find(a)]++;
			cout << "LADICA\n";
		}
		else if (-set[find(a)] > active[find(a)]) {
			active[find(a)]++;
			cout << "LADICA\n";
		}
		else if (-set[find(b)] > active[find(b)]) {
			active[find(b)]++;
			cout << "LADICA\n";
		}
		else cout << "SMECE\n";

		merge(a, b);
		visited[a] = true, visited[b] = true;
	}

	return 0;
}

int find(int x) {
	if (set[x] < 0) return x;
	set[x] = find(set[x]);
	return set[x];
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A != B) {
		set[B] += set[A];
		active[B] += active[A], active[A] = 0;
		set[A] = B;
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 유니온 파인드
접근 방식		: 
결정적 깨달음		: 1. 집합의 크기와, 2. 집합에서 술병이 들어있는 서랍의 개수를 저장해야 함.
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////