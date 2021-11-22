#include <iostream>

using namespace std;

int sum(int a, int b){
	if(b == 0)return;
	else return a + b;
}

int main(){
	int a = 5;
	int b = 0;
	cout<<sum(a,b)<<endl;
}
