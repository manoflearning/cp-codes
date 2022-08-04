#include <iostream>
#include <stack>
using namespace std;

string num;

int main() {
	cin >> num;

	stack<int> memo;
	for (int i = 0; i < num.length(); i++) {
		if ('0' <= num[i] && num[i] <= '9') memo.push(num[i] - '0');
		else {
			if (num[i] == '+') {
				int tmp2 = memo.top();
				memo.pop();
				int tmp1 = memo.top();
				memo.pop();

				memo.push(tmp1 + tmp2);
			}
			else if (num[i] == '-') {
				int tmp2 = memo.top();
				memo.pop();
				int tmp1 = memo.top();
				memo.pop();

				memo.push(tmp1 - tmp2);
			}
			else if (num[i] == '*') {
				int tmp2 = memo.top();
				memo.pop();
				int tmp1 = memo.top();
				memo.pop();

				memo.push(tmp1 * tmp2);
			}
			else if (num[i] == '/') {
				int tmp2 = memo.top();
				memo.pop();
				int tmp1 = memo.top();
				memo.pop();

				memo.push(tmp1 / tmp2);
			}
		}
	}

	printf("%d", memo.top());

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
���� �ع�		: ������ Ȱ��
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////