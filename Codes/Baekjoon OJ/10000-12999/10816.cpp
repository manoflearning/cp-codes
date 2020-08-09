#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> card;
int sam;
vector<int> ccount;

int bsearch(int left, int right);

int main() {
	//input
	scanf("%d", &n);
	card.resize(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &card[i]);
	scanf("%d", &m);
	//
	sort(card.begin(), card.end());
	
	ccount.resize(n);

	int count = 1;
	for (int i = 1; i < n; i++) {
		if (card[i - 1] == card[i]) count++;
		else {
			for (int l = i - 1; l >= 0 && ccount[l] == 0; l--)
				ccount[l] = count;
			count = 1;
		}
	}
	for (int l = n - 1; ccount[l] == 0; l--)
		ccount[l] = count;
	//
	for (int test = 0; test < m; test++) {
		scanf("%d", &sam);

		int flag = bsearch(0, n - 1);
		
		if (flag == -1) printf("0");
		else printf("%d", ccount[flag]);

		printf(" ");
	}

	return 0;
}

int bsearch(int left, int right) {
	//base case
	if (left > right) return -1;
	//
	int flag = (left + right) / 2;

	if (card[flag] == sam) return flag;
	if (card[flag] < sam) return bsearch(flag + 1, right);
	if (card[flag] > sam) return bsearch(left, flag - 1);
}

/*
���� �ع�		: �̺� Ž��
���� ���		:
������ ������	:
���� ����		: 1. �迭�� ������ ��� ����
				  2. �ð� �ʰ� (���� ī���� ������ �� �� �־��� ��� O(n * m)�� �ð����⵵)
*/