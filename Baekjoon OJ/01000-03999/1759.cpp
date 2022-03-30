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
		//�� �� �̻��� ������ �� �� �̻��� ����
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
���� �ع�		: ��Ʈ��ŷ
���� ���		: �־��� ���� �������� ���� -> �� ������ ���ڸ� ���ϰ�, ������ ������ �Լ��� ���ڷ� ���� -> ������ ������ l�� ��, ������ ������ ������ ���ǿ� ������ ���
������ ������		:
���� ����		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////