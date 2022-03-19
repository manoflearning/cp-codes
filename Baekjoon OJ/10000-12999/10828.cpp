#include <iostream>
#include <cstring>
#include <vector>

std::vector<int> stack;
int size=-1;

void push();
void pop();
void size_();
void empty();
void top();

int main() {
	int n;
	std::cin>>n;
	
	for(int i=0; i<n; i++) {
		char command[6];
		std::cin>>command;
		
		if(strcmp(command, "push") == 0)
			push();
		else if(strcmp(command, "pop") == 0)
			pop();
		else if(strcmp(command, "size") == 0)
			size_();
		else if(strcmp(command, "empty") == 0)
			empty();
		else if(strcmp(command, "top") == 0)
			top();
	}
	
	return 0;
}

void push() {
	stack.resize(size+2);
	for(int i=size; i>=0; i--)
		stack[i+1] = stack[i];
	size++;
	
	std::cin>>stack[0];
}
void pop() {
	if(size==-1)
		std::cout<<"-1"<<'\n';
	else {
		std::cout<<stack[0]<<'\n';
		
		for(int i=1; i<=size; i++)
			stack[i-1] = stack[i];
		size--;
	}
}
void size_() {
	std::cout<<size+1<<'\n';
}
void empty() {
	if(size==-1)
		std::cout<<'1'<<'\n';
	else
		std::cout<<'0'<<'\n';
}
void top() {
	if(size==-1)
		std::cout<<"-1"<<'\n';
	else
		std::cout<<stack[0]<<'\n';
}

