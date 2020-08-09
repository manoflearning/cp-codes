#include <iostream>
#include <list>
#include <cstring>
using namespace std;

list<char> word;

int main() {
	char arr[100001];
	scanf("%s", arr);

	int len = strlen(arr);
	for (int i = 0; i < len; i++)
		word.push_back(arr[i]);

	int n;
	scanf("%d", &n);

	list<char>::iterator it = word.end();
	for (int test = 0; test < n; test++) {
		char com;
		scanf(" %c", &com);

		if (com == 'L') {
			if (it != word.begin()) it--;
		}
		else if (com == 'D') {
			if (it != word.end()) it++;
		}
		else if (com == 'B') {
			if (it != word.begin()) {
				it = word.erase(--it);
				len--;
			}
		}
		else {
			char sam;
			scanf(" %c", &sam);

			word.insert(it, sam);
			len++;
		}
	}

	it = word.begin();
	for (int i = 0; i < len; i++) {
		printf("%c", *it);
		it++;
	}

	return 0;
}
/*
문제 해법		: 연결 리스트의 활용
접근 방식		: 순서를 유지한채 삽입과 삭제가 매우 빈번히 일어나는 문제임. 따라서 연결 리스트를 사용.
결정적 깨달음		: 
오답 원인		: 1. 커서를 판단하는 기준이 잘못됨 (실제로 커서를 두 문자 사이에 두는 것이 아니라, 규칙을 통해 비슷한 환경을 재현해내는 것이기 때문)
				  2. 
*/
//////////////////////////////////////////////////////////////////////