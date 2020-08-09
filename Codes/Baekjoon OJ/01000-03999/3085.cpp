#include <iostream>

int maximum_number_candies(char board[][50], int N);
int swapcheck(char board[][50], int i, int l, int N);
int justcheck(char board[][50], int N);
void swappointer(char &n, char &m);

int main() {
	int N;
	std::cin>>N;
	
	char board[50][50];
	for(int i=0; i<N; i++)
	for(int l=0; l<N; l++)
		std::cin>>board[i][l];
		
	std::cout<<maximum_number_candies(board, N);
	
	return 0;
}

int maximum_number_candies(char board[][50], int N) {
	int max=0;
	
	for(int i=0; i<N; i++)
	for(int l=0; l<N; l++) {
		int tmp;
		tmp = swapcheck(board, i, l, N);
		
		if(tmp>max)
			max = tmp;
	}
	
	return max;
}

int swapcheck(char board[][50], int y, int x, int N) {
	int countx=0, county=0;
	
	//가로줄 체크
	if(y!=N-1)
	if(board[y][x]!=board[y+1][x]) {
		swappointer(board[y][x], board[y+1][x]);
		countx = justcheck(board, N);
		swappointer(board[y][x], board[y+1][x]);
	}
	//세로줄 체크
	if(x!=N-1)
	if(board[y][x]!=board[y][x+1]) {
		swappointer(board[y][x], board[y][x+1]);
		county = justcheck(board, N);
		swappointer(board[y][x], board[y][x+1]);
	}
	
	return (countx>county)?countx:county;
}

int justcheck(char board[][50], int N) {
	int max=1;
	
	for(int i=0; i<N; i++) {
		int count;
		//가로 체크
		count=1;
		for(int l=0; l<N-1; l++) {
			if(board[i][l]==board[i][l+1]) count++;
			else {
				if(count>max) max=count;
				count=1;
			}
			if(count>max) max=count;
		}
		//세로 체크
		count=1;
		for(int l=0; l<N-1; l++) {
			if(board[l][i]==board[l+1][i]) count++;
			else {
				if(count>max) max=count;
				count=1;
			}
			if(count>max) max=count;
		}
	}
	
	return max;
}

void swappointer(char &n, char &m) {
	char tmp=n;
	n=m;
	m=tmp;
}