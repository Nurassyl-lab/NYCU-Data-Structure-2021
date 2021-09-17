#include <iostream>
#include <stdio.h>
using namespace std;

int main(){
    int a = 1;

    cout<<"Case (a)"<<endl;
    for (int i = 0; i < 5; i++){
        a = 1;
        for (int j = 0; j < 5; j++){
            if((i - j) >=  0){cout<<a<<" ";}
            a++;
        }
        cout<<endl;
    }
    
    cout<<endl;
    cout<<"Case (b)"<<endl;
    
    for (int i = 0; i < 5; i++){
        a = 1;
        for (int j = 0; j < 5; j++){
            if((i - j) > 0){
                cout<<"  ";
            }
            else{
                //printf("%-2d", a);
		cout<<a<<" ";
		a++;
            }
        }
        cout<<endl;
    }
    

    cout<<endl;
    cout<<"Case (c)"<<endl;
    a = 0;
    for (int i = 0; i < 5; i++){
	a = i + 1;
        for (int j = 0; j < 5; j++){
            	cout<<a<<" ";
		a++;
            }
	cout<<endl;
        }
    return 0;

}
