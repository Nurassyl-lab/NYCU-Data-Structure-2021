#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <compare>
using namespace std;

#define MAX 697958

int main(){
	string s = "1 2 c asd 3 4";
	int col = 0;
	char c;
	int num;
	int i = 0;
	//FILE*file = fopen("sample.in", "r");
	//istringstream ss(s);
	ifstream File;
	File.open("sample.in");
	int t = 0;
	/*while(fscanf(file, "%d", &t)){
	//	int t;
	//	fscanf(file, "%d", &t);
					
			//t = stoi(string(1,c));
		col++;
		//cout<<"col = "<<col<<endl;		
	//	if(feof(file)){
	//		break;
	//	}
	//	i++;
		//num = t;
		cout<<"t = "<<t<<endl;

	}*/
	string p;
	col = 0;
	while(getline(File, p)){
		istringstream ss(p);
		col++;
		while(ss >> num){
			cout<<num<<endl;
		}
		/*
		do{
			if(isdigit(ss)){
				cout<<"digit"<<endl;
			}
			if(!ss.eof()){
				ss >> t;
				cout<<t<<" t was"<<endl;
			}
	
		}while(ss.good());*/
	}
	cout<<"col = "<<col<<endl;
	cout<<"num = "<<t;


	int a = 8;
       	int b = 7;
	int r;
	cout<<endl;
	if(a < b) r = -1;
	if(a == b) r = 0;
	if(a > b) r = 1;
	cout<<"r = "<< r<<endl;
	switch(r){
		case -1: 
			cout<<"a is cmaller"<<endl;
			break;
		case 0:
			cout<<"a nad b are equal"<<endl;
			break;
		case 1:
			cout<<"a is bigger"<<endl;
			break;
	}
	int ar[2][2] = { };
	cout<<"arr = "<<ar[0][0]<<endl;

}
