#include <iostream>
#include <stack>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(2);

	int n;
	cin >> n;

	string num;
	cin >> num;

	double converse[26];
	for (int i = 0; i < n; i++)
		cin >> converse[i];

	stack<double> calculate;

	for (int i = 0; i < num.size(); i++) {
		if ('A' <= num[i] && num[i] <= 'Z')
			calculate.push(converse[num[i] - 'A']);
		else {
			if (num[i] == '+') {
				double b = calculate.top();
				calculate.pop();
				double a = calculate.top();
				calculate.pop();

				calculate.push(a + b);
			}
			else if (num[i] == '-') {
				double b = calculate.top();
				calculate.pop();
				double a = calculate.top();
				calculate.pop();

				calculate.push(a - b);
			}
			else if (num[i] == '*') {
				double b = calculate.top();
				calculate.pop();
				double a = calculate.top();
				calculate.pop();

				calculate.push(a * b);
			}
			else if (num[i] == '/') {
				double b = calculate.top();
				calculate.pop();
				double a = calculate.top();
				calculate.pop();

				calculate.push(a / b);
			}
		}
	}
	
	cout << calculate.top();

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 스택을 활용한 후위 표기식 계산
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////