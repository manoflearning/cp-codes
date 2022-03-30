#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int MAX = 1e5;

int N;
ll A[MAX + 5];

ll find_max(int L, int R);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> A[i];

	cout << find_max(1, N);
	
	return 0;
}

ll find_max(int L, int R) {
	//base case
	if (L == R) return A[L] * A[L];
	if (L > R) return 0;

	int mid = (L + R) / 2;
	//�ִ��� ������ ���� �κй迭�� mid��° �迭 ���Ҹ� �����ϴ� �ʴ� ��� ���
	ll ret = max(find_max(L, mid - 1), find_max(mid + 1, R));

	//�ִ��� ������ ���� �κй迭�� mid��° �迭 ���Ҹ� �����ϴ� ��� ���
	ll sum = A[mid], mul = A[mid];
	int mL = mid, mR = mid;

	ret = max(ret, sum * mul);
	while (!(L == mL && mR == R)) {
		if (L == mL || (mR != R && A[mL - 1] <= A[mR + 1])) {
			mR++;
			sum += A[mR];
			mul = min(mul, A[mR]);
		}
		else {
			mL--;
			sum += A[mL];
			mul = min(mul, A[mL]);
		}

		ret = max(ret, sum * mul);
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ��������
������ ������		: 
�ð����⵵		: �� ���� �Լ� ȣ�⿡�� O(R - L). �Լ��� (R - L)�� 2��� �۾����� ���� �Լ� ȣ���� 2��� �þ. �Լ��� (R - L)�� �ּ� 1��. ���� O(nlgn).
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////