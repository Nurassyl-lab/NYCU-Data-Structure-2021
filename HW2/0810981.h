#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>//TA said that we are allowed to use <string> library
#include <algorithm>

#define MAX 1000000

using namespace std;

struct element{
	char t;

	bool isEmpty(int rear, int front){
		if(rear == front) return true;
		return false;
	}

	bool isFull(int rear, int front){
		if(rear - front == MAX) return true;
		else if(rear - front > MAX){
			cout<<"Error! Something is wrong and you queue exceeds limit."<<endl;
			exit(0);
		}
		return false;
	}

	void addQ(vector<element> &v, element a, int &rear, int front){
		if(v[0].isFull(rear, front)){
			cout<<"Error! Cannot add to a queue, because queue is FULL!";
			exit(0);
		}
		v.push_back(a);
		rear+=1;
	}
	void delQ(vector<element> &v, int &rear, int front, int &front2, int size){
		if(v[0].isEmpty(rear, front)){
			cout<<"Error! Element cannot be deleted fron the queue, because queue is empty!"<<endl;
			exit(0);
		}
		v.erase(v.begin() + (size - 1));
		rear -= 1;
		front2 += 1;
	}

};

//write to a file
void write(string s, vector<vector<element>> v, int front[][1], int rear[][1]){
	ofstream File;
	File.open(s);
	if(!File){
		cout<<"Error! No output File."<<endl;
		exit(0);
	}

	File<<"Queuing\n";
	for(int i = 0; i < v.size(); i++){
		int processor = i + 1;
		File<<processor;
		File<<" ";
		if((rear[i][0] - front[i][0]) > 0){
			for(int j = (front[i][0] + 1); j < rear[i][0] + 1; j++){
				File<<v[i][j].t;
			}
		}
		File<<"\n";
	}	

	File<<"Executed\n";	
	for(int i = 0; i < v.size(); i++){
		int processor = i + 1;
		File<<processor;
		File<<" ";
		for(int j = 0; j <= front[i][0]; j++){
			File<<v[i][j].t;
		}
		File<<"\n";
	}
	File.close();
}
