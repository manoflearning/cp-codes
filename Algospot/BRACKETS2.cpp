#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

const string open("([{"), close(")]}");
string word;

bool wellMatched();

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		cin >> word;
		
		if (wellMatched()) printf("YES\n");
		else printf("NO\n");
	}
	
	return 0;
}

bool wellMatched() {
	stack<char> remain;

	for (int i = 0; i < word.length(); i++) {
		if (open.find(word[i]) != -1) remain.push(word[i]);
		else {
			if (remain.empty()) return false;
			else if (open.find(remain.top()) != close.find(word[i])) return false;
			
			remain.pop();
		}
	}

	return remain.empty();
}
/*
문제 해법		: 스택을 활용한 문제, string 자료형을 처음 써봄. string의 find 함수를 활용해 비교 과정을 단순하게 함.
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. string 자료형은 scanf로 입력 받아서는 안됨!!
				  2. 
*/
//////////////////////////////////////////////////////////////////////
