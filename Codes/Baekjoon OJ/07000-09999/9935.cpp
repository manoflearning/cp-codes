#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 1000000;

string word, bomb;
char stack[MAX + 1];
int top = 0;

int main() {
	cin >> word >> bomb;

	for (int i = 0; i < word.length(); i++) {
		stack[top] = word[i], top++;

		bool check = true;
		if (top - bomb.length() < 0) check = false;
		else {
			for (int i = top - bomb.length(); i < top; i++)
				if (stack[i] != bomb[i - top + bomb.length()]) {
					check = false;
					break;
				}
		}

		if (check) top -= bomb.length();
	}

	if (top == 0) printf("FRULA");
	for (int i = 0; i < top; i++)
		printf("%c", stack[i]);

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 직접 구현한 스택을 활용(라이브러리에서 제공되는 스택은 랜덤 엑세스 자료구조가 아니기 때문!). 만약 폭발 문자열의 마지막 문자를 만나면, 문자열 점검 -> 삭제.
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////