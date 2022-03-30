/*
���� �ع�		: ��� ȣ���� �̿��� ���Ʈ ���� 
���� ���		: 
������ ������	: 
���� ����		: 
*/
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int k;
vector<int> picked;
vector<int> set;

void Pick(int toPick, int min);
void PrintPick();

int main()
{
	while(1)
	{
		scanf("%d", &k);
		
		if(k==0) break;
		
		set.resize(k);
		for(int i=0; i<k; i++)
			scanf("%d", &set[i]);
			
		Pick(6, 0);
		printf("\n");
	}
	
	return 0;
}

void Pick(int toPick, int min)
{
	if(toPick == 0) { PrintPick(); return ; }
	
	for(int i=min; i<k; i++)
	{
		picked.push_back(set[i]);
		Pick(toPick-1, i+1);
		picked.pop_back();
	}
}

void PrintPick()
{
	for(int i=0; i<6; i++)
		printf("%d ", picked[i]);
	printf("\n");
}