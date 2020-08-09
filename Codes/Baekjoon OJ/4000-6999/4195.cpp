#include <iostream>
#include <map>
#include <cstring>
using namespace std;

const int MAX = 1e5;

map<string, int> mp;
int p[MAX + 1];

int find(int x);
void merge(int a, int b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;

	while (T--) {
		mp.clear();
		memset(p, -1, sizeof(p));

		int n; cin >> n;

		int flag = 1;

		for (int i = 0; i < n; i++) {
			string s0, s1;
			cin >> s0 >> s1;

			map<string, int>::iterator it0 = mp.find(s0);
			map<string, int>::iterator it1 = mp.find(s1);

			if (it0 == mp.end()) {
				mp.insert({ s0, flag });
				flag++; 
				it0 = mp.find(s0);
			}
			if (it1 == mp.end()) {
				mp.insert({ s1, flag });
				flag++;
				it1 = mp.find(s1);
			}

			merge(it0->second, it1->second);

			cout << -p[find(it0->second)] << '\n';
		}
	}

	return 0;
}

int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[B] += p[A];
	p[A] = B;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 유니온 파인드, map
접근 방식		: map의 O(logn)시간 탐색 기능을 활용하여 이름 저장. 이름과 일대일 대응되는 숫자로 집합 만들기. 유니온 파인드를 사용하여 집합을 합치고, 집합의 크기를 구함.
결정적 깨달음		:
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////