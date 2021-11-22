#include "0810981.h"

int main(int argc, char* argv[]) {
	ifstream inFile;
	ofstream outFile;

	inFile.open(argv[1]);
	outFile.open(argv[2]);
	
	string s;
	int a, b;

	MaxHeap myheap;

	while(getline(inFile, s)){
		istringstream ss(s);
		ss>>a;
		switch(a){
			case 0:
				ss>>b;
				myheap.push(b);
				break;
			case 1:
				myheap.DELETE();
				break;
			default:
				myheap.print(a, outFile);
				break;
		}
	}
}
