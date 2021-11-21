#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
	vector<int> v;
	v.push_back(8);
	v.push_back(1);
	v.push_back(92);
	v.push_back(32);
	v.push_back(93);

	for(int i = 0; i < v.size(); i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
	cout<<"vec size "<<v.size()<<endl; 
	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;

	v.erase(v.begin()+0);
	cout<<"vec size "<<v.size()<<endl; 
	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}
