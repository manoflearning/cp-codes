#include <iostream>
using namespace std;

int deque[20001];
int front = 10000, back = 10000;

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		string cmd;
		cin >> cmd;

		if (cmd == "push_front") {
			scanf("%d", &deque[front - 1]);
			front--;
		}
		else if (cmd == "push_back") {
			scanf("%d", &deque[back]);
			back++;
		}
		else if (cmd == "pop_front") {
			if (front == back) printf("-1\n");
			else {
				printf("%d\n", deque[front]);
				front++;
			}
		}
		else if (cmd == "pop_back") {
			if (front == back) printf("-1\n");
			else {
				printf("%d\n", deque[back - 1]);
				back--;
			}
		}
		else if (cmd == "size") {
			printf("%d\n", back - front);
		}
		else if (cmd == "empty") {
			if (front == back) printf("1\n");
			else printf("0\n");
		}
		else if (cmd == "front") {
			if (front == back) printf("-1\n");
			else printf("%d\n", deque[front]);
		}
		else if (cmd == "back") {
			if (front == back) printf("-1\n");
			else printf("%d\n", deque[back - 1]);
		}
	}

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
���� �ع�		: ���� ����
���� ���		:
������ ������		:
���� ����		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////