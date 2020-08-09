#include <iostream>
#include <algorithm>

int main() {
	int nine_dwarf[9];
	
	for(int i=0; i<9; i++)
		std::cin>>nine_dwarf[i];
		
	std::sort(nine_dwarf, nine_dwarf+9);
	
	for(int i=0; i<8; i++)
		for(int l=i+1; l<9; l++) {
			int sum = 0;
			
			for(int k=0; k<9; k++)
				if(k!=i && k!=l)
					sum+=nine_dwarf[k];
			
			if(sum==100) {
				for(int k=0; k<9; k++)
					if(k!=i && k!=l)
						std::cout<<nine_dwarf[k]<<'\n';
						
				i=8, l=9;
			}
		}
	
	return 0;
}
