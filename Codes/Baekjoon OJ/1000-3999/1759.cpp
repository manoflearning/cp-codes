#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 15;

char mo[5] = { 'a','e','i','o','u' };

int l, c;
char alp[MAX];
vector<char> pw;
bool isMo[MAX];

void print(int flag, int moCnt);

int main() {
	cin >> l >> c;

	for (int i = 0; i < c; i++)
		cin >> alp[i];

	sort(alp, alp + c);

	for (int i = 0; i < c; i++) {
		if (find(mo, mo + 5, alp[i]) - mo != 5)
			isMo[i] = true;
	}

	print(-1, 0);

	return 0;
}

void print(int flag, int moCnt) {
	if (pw.size() == l) {
		//한 개 이상의 모음과 두 개 이상의 자음
		if (1 <= moCnt && 2 <= l - moCnt) {
			for (int i = 0; i < pw.size(); i++)
				cout << pw[i];
			cout << '\n';
		}

		return;
	}

	for (int i = flag + 1; i < c; i++) {
		pw.push_back(alp[i]);
		
		if (isMo[i]) print(i, moCnt + 1);
		else print(i, moCnt);
		
		pw.pop_back();
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
접근 방식		: 주어진 문자 오름차순 정렬 -> 각 순서의 문자를 정하고, 모음의 개수를 함수의 인자로 전달 -> 문자의 개수가 l일 때, 모음과 자음의 개수가 조건에 맞으면 출력
결정적 깨달음		:
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////