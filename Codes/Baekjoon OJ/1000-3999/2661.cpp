#include <iostream>
using namespace std;

int N;
string s;
bool first = true;

void making();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i = 1; i <= 3; i++) {
		s.push_back(i + '0');
		making();
		s.pop_back();
	}

	return 0;
}

void making() {
	if (!first) return;
	if (s.size() >= N) {
		if (first) {
			cout << s;
			first = false;
			return;
		}
	}
	//
	bool can[4] = { true, true, true, true };
	
	can[s.back() - '0'] = false;
	for (int i = (s.size() % 2 == 1) ? 0 : 1; i < s.size() - 1; i += 2) {
		int mid = (i + s.size() - 1) / 2;
		
		bool check = true;
		for (int l = i; l <= mid - 1; l++) {
			if (s[l] != s[l + (mid - i + 1)]) {
				check = false;
				break;
			}
		}
		if (check) can[s[mid] - '0'] = false;
	}

	for (int i = 1; i <= 3; i++) {
		if (can[i]) {
			s.push_back(i + '0');
			making();
			s.pop_back();
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
결정적 깨달음		: 
시간복잡도		: 
오답 원인		: 1. 그리디로 풀려 했으나 큰 수부터 가능한 가장 작은 수를 고를 경우 원하는 자릿수의 수를 만들지 못할 수도 있음
				  2. 
*/////////////////////////////////////////////////////////////////////