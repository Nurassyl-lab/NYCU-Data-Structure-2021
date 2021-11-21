#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct e{
	int a;
	int b;
	int front;
	int rear;
};

struct check{
	int a;
};

int main(){
/*	vector<e> v(5);
	vector<vector<e>> vec(5);
	cout<<"Size of vector: "<<v.size()<<endl;
	for(int i = 0; i < v.size(); i++){
		cout<<i+1<<") a value: "<<v[i].a<<", b value: "<<v[i].b<<endl; 
	}

	for(int i = 0; i < v.size(); i++){
		for(int j = 0; j < 20; j++)
			vec[i].push_back(e{12, 13});
	}
	e a = {12, 12, -1, -1};

	vec[0].push_back(a);
	cout<<"vector 0: "<<vec[0][0].a<<endl;
	int arr[] = {[0 ... 4]= -1};
	cout<<"arr "<<arr[2]<<endl;*/

/*	cout<<endl;
	vector<vector<int>> vec(2);
	for(int i = 0; i < 10; i++){
		vec[0].push_back(i);
		vec[1].push_back(i * 2);
		cout<<"i = "<<i<<endl;
	}
	int size = vec[0].size();
	cout<<"size of a 1 vector "<<size<<", last element of a vector is "<<vec[0][size - 1]<<endl;
	vec[0].erase(vec[0].begin() + (size - 1));
	cout<<vec[0].size()<<endl;


	string s= "HEllo my data";
	cout<<s.find("data")<<" and "<<s.find("govno")<<endl;
	if(s.find("mmy") != string::npos){
		cout<<"Found"<<endl;
	}
	int o = 0;
	do{
		cout<<o<<endl;
		//if(o == 500) break;
		o++;
	}while(o < 1000);
	cout<<"end!"<<endl;


	vector<vector<int>> a(2);
	a[0].push_back(1);
	a[0].push_back(2);
	a[0].push_back(3);

	a[1].push_back(2);

	cout<<"1st size is "<<a[0].size()<<endl;
	cout<<"2nd size is "<<a[1].size()<<endl;
*/
	vector<vector<check>> v(5);
	
	cout<<"sizes before"<<endl;
	for(int i = 0; i < 5; i++){
		cout<<i+1<<". size is "<<v[0].size()<<endl;
	}

	v[0].push_back(check{1});

	cout<<"sizes after"<<endl;
	for(int i = 0; i < 5; i++){
		cout<<i+1<<". size is "<<v[i].size()<<endl;
	}

	cout<<"value us "<<v[0][0].a;
}









